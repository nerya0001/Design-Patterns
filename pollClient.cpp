#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "reactor.hpp"


#include <arpa/inet.h>


#define PORT "9035"

void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in *) sa)->sin_addr);
    }

    return &(((struct sockaddr_in6 *) sa)->sin6_addr);
}

void *listenToServer(void *sockfd) {
    int newSock = *(int *) sockfd;
    char ServerMsg[1024];
    while (1) {
        if (recv(newSock, ServerMsg, sizeof(ServerMsg), 0) < 0) {
            printf("Error while receiving server's msg\n");
            return NULL;
        }

        ServerMsg[strlen(ServerMsg)] = '\0';
        printf("%s\n", ServerMsg);
        memset(ServerMsg, '\0', strlen(ServerMsg));
    }
}


int main(int argc, char *argv[]) {

    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];

    if (argc != 2) {
        fprintf(stderr, "usage: client hostname\n");
        exit(1);
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(argv[1], PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and connect to the first we can
    for (p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            perror("client: connect");
            close(sockfd);
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *) p->ai_addr),
              s, sizeof s);
    printf("client: connecting to %s\n", s);

    freeaddrinfo(servinfo); // all done with this structure

    char input[1024] = {0};
    pthread_t thread_id;

    int *clientSock = (int *) malloc(sizeof(int));
    *clientSock = sockfd;

    pthread_create(&thread_id, nullptr, listenToServer, (void *) clientSock);

    while (1) {
        if (!scanf("%[^\n]%*c", input)) {
            while (getchar() != '\n');
        }
        if (strncmp(input, "EXIT", 4) == 0) {
            printf("client disconnected\n");
            break;
        }
        if (send(sockfd, input, strlen(input) + 1, 0) == -1) {
            perror("sending unsuccessful\n");
        }
        bzero(input, 1024);
    }

    close(sockfd);

    return 0;
}