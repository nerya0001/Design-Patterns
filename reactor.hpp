#ifndef REACTOR_HPP
#define REACTOR_HPP

#include <iostream>
#include <poll.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <string>
#include <unistd.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <netdb.h> 
#include <ctype.h>
#include <stdexcept>
#include <poll.h>
#include <pthread.h>


class Reactor {
private:
    struct pollfd fds[100];
    void (*handlers[100])(void*,int);
    int numFds;
    pthread_t thread;


public:
    Reactor();
    ~Reactor(){}
    void installHandler(int fd, void (*handler)(void*, int));
    void removeHandler(int fd);
    static void* handleEvents(void* reac);
    

    //getter for thread
    pthread_t &getThread(){return this->thread;}
    int getNumFds() { return this->numFds; }
    struct pollfd* getFds() { return this->fds; }
    // void* (*getHandlers()){ return this->handlers; }
    
};

// extern Reactor* reactor;
#endif