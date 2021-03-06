#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>
#include <iostream>
#include <string>
#include "activeObject.hpp"
#include "safeQueue.hpp"
#include "data.hpp"
#include "util.hpp"

#define PORT "3490" // the port users will be connecting to

#define BACKLOG 10 // how many pending connections queue will hold

activeObject *object1;
activeObject *object2;
activeObject *object3;

void sigchld_handler(int s)
{
    int saved_errno = errno;

    while (waitpid(-1, NULL, WNOHANG) > 0)
        ;

    errno = saved_errno;
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
    {
        return &(((struct sockaddr_in *)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

void *myThread(void *new_fd)
{
    char clientMsg[1024] = {0};
    int numbytes;
    int clientSock = *(int *)new_fd;
    std::string text;

    while (1)
    {
        // Receive message from client
        if ((numbytes = recv(clientSock, clientMsg, 1024, 0)) == -1)
        {
            perror("recv");
            exit(1);
        }

        // check if client closed connection
        if (numbytes == 0)
        {
            // close connection
            close(clientSock);
            // print Connection closed
            std::cout << "Connection closed by the client" << std::endl;
            break;
        }

        text = clientMsg;

        // create the data object to be passed to the active object
        data *d = new data(text, clientSock);
        // push the data object into the queue
        object1->getQueue()->enQ(d);

        // zero out the clientMsg buffer
        memset(clientMsg, 0, 1024);
    }
    return NULL;
}

int main(void)
{
    int sockfd, new_fd; // listen on sock_fd, new connection on new_fd
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    struct sigaction sa;
    int yes = 1;
    char s[INET6_ADDRSTRLEN];
    int rv;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for (p = servinfo; p != NULL; p = p->ai_next)
    {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1)
        {
            perror("server: socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
        {
            perror("setsockopt");
            exit(1);
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1)
        {
            close(sockfd);
            perror("server: bind");
            continue;
        }

        break;
    }

    freeaddrinfo(servinfo); // all done with this structure

    if (p == NULL)
    {
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }

    if (listen(sockfd, BACKLOG) == -1)
    {
        perror("listen");
        exit(1);
    }

    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1)
    {
        perror("sigaction");
        exit(1);
    }

    printf("server: waiting for connections...\n");

    pthread_t tid[10];

    // create the active objects and give them the functions to run
    object1 = new activeObject(&caesarCipher, &moveToNext, 20);
    object2 = new activeObject(&reverseCapitalization, &moveToNext, 20);
    object3 = new activeObject(&sendResult, NULL, 20);

    int i = 0;
    while (1)
    {
        sin_size = sizeof their_addr;
        // accept a connection
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1)
        {
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family,
                  get_in_addr((struct sockaddr *)&their_addr),
                  s, sizeof s);
        printf("server: got connection from %s\n", s);

        // create a new thread to handle the client
        if (pthread_create(&tid[i++], NULL, &myThread, &new_fd) != 0)
        {
            printf("Failed to create thread\n");
        }
    }

    return 0;
}
