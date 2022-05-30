#ifndef REACTOR_HPP
#define REACTOR_HPP

#include <iostream>
#include <stdexcept>
#include <sys/epoll.h>
#include <pthread.h>


class Reactor {
private:
    int *fds;
    void *(*handlers[100])(void *data);
    pthread_t thread;


public:
    Reactor();
    ~Reactor();
    void registerHandler(int fd, void (*handler)(int));
    void removeHandler(int fd);
    void handleEvents();

};

#endif