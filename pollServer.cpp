/*
** pollserver.c -- a cheezy multiperson chat server
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>
#include <pthread.h>
#include "reactor.hpp"


#define PORT "9035"   // Port we're listening on

Reactor* reactor;

void *get_in_addr(struct sockaddr *sa) { 
     if (sa->sa_family == AF_INET) { 
         return &(((struct sockaddr_in *) sa)->sin_addr); 
     } 
  
     return &(((struct sockaddr_in6 *) sa)->sin6_addr); 
 } 
  

 int get_listener_socket() { 
     int listener;    
     int yes = 1;       
     int rv; 
  
     struct addrinfo hints, *ai, *p; 
  

     memset(&hints, 0, sizeof hints); 
     hints.ai_family = AF_UNSPEC; 
     hints.ai_socktype = SOCK_STREAM; 
     hints.ai_flags = AI_PASSIVE; 
     if ((rv = getaddrinfo(NULL, PORT, &hints, &ai)) != 0) { 
         fprintf(stderr, "selectserver: %s\n", gai_strerror(rv)); 
         exit(1); 
     } 
  
     for (p = ai; p != NULL; p = p->ai_next) { 
         listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol); 
         if (listener < 0) { 
             continue; 
         } 
  
   
         setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)); 
  
         if (bind(listener, p->ai_addr, p->ai_addrlen) < 0) { 
             close(listener); 
             continue; 
         } 
  
         break; 
     } 
  
     freeaddrinfo(ai); 
  
     if (p == NULL) { 
         return -1; 
     } 
  
     if (listen(listener, 10) == -1) { 
         return -1; 
     } 
  
     return listener; 
 }
 


// broadcast to all clients
void handleClients(void* reac, int fd)
{
    Reactor* handleReactor =(Reactor*)reac;
    char buf[1024];
    int nbytes = read(fd, buf, 1024);
    if (nbytes < 0)
    {
        throw std::runtime_error("Read failed");
    }
    if (nbytes == 0)
    {
        close(fd);
        handleReactor->removeHandler(fd);
        return;
    }
    for (int i = 0; i < handleReactor->getNumFds(); i++)
    {
        
        if (handleReactor->getFds()[i].fd != fd)
        {
           
            write(handleReactor->getFds()[i].fd, buf, nbytes);
        }
    }
}

void handleNewConnections(void* reac, int listener)
{
    Reactor* handleReactor =(Reactor*)reac;

    struct sockaddr_storage remoteaddr;
    char remoteIP[INET6_ADDRSTRLEN];
    socklen_t addrlen = sizeof(remoteaddr);

    int newClient = accept(listener, (struct sockaddr *)&remoteaddr, &addrlen);
    if (newClient < 0)
    {
        throw std::runtime_error("Accept failed");
    }
    handleReactor->installHandler(newClient, &handleClients);
    std::cout << "New connection from " << inet_ntop(remoteaddr.ss_family, get_in_addr((struct sockaddr *)&remoteaddr), remoteIP, INET6_ADDRSTRLEN) << std::endl;
}


int main() { 
    reactor = new Reactor();
    int listener = get_listener_socket(); 
    if (listener == -1) { 
        fprintf(stderr, "error getting listening socket\n"); 
        exit(1); 
    } 
    reactor->installHandler(listener, &handleNewConnections);
    std::cout << "pollserver: waiting for new connections...\n" << std::endl; 
    //join thread
    pthread_join(reactor->getThread(), NULL);
    close(listener); 

    return 0; 
}