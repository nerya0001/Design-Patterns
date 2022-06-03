
#include "reactor.hpp"

// Constructor
Reactor::Reactor()
{
    // Initialize the number of file descriptors to 0
    this->numFds = 0;
  
}

// installHandler - add a handler to the list of handlers to be called when a file descriptor is ready for I/O operations
void Reactor::installHandler(int fd, void (*handler)(void *, int))
{
    if (this->numFds == 100)
    {
        throw std::runtime_error("Too many file descriptors");
    }
    if (this->numFds == 0)
    {
        this->fds[0].fd = fd;
        this->fds[0].events = POLLIN;
        this->handlers[0] = handler;
        this->numFds++;
        std::cout << "Added handler for fd " << fd << std::endl;
        pthread_create(&thread, NULL, &handleEvents, &(*this));

    }
    else
    {
        for (int i = 0; i < this->numFds; i++)
        {
            if (this->fds[i].fd == fd)
            {
                throw std::runtime_error("File descriptor already installed");
            }
        }
        this->fds[this->numFds].fd = fd;
        this->fds[this->numFds].events = POLLIN;
        this->handlers[this->numFds] = handler;
        this->numFds++;
    }
}

void Reactor::removeHandler(int fd)
{
    for (int i = 0; i < this->numFds; i++)
    {
        if (this->fds[i].fd == fd)
        {
            for (int j = i; j < this->numFds - 1; j++)
            {
                this->fds[j] = this->fds[j + 1];
                this->handlers[j] = this->handlers[j + 1];
            }
            this->numFds--;
            return;
        }
    }
    throw std::runtime_error("File descriptor not installed");
}

void* Reactor::handleEvents(void *reac)
{
    Reactor *loopReactor = (Reactor *)reac;
    while (1)
    {
        int ret = poll(loopReactor->fds, loopReactor->numFds, -1);
        if (ret < 0)
        {
            throw std::runtime_error("Poll failed");
        }
        for (int i = 0; i < loopReactor->getNumFds(); i++)
        {
            if (loopReactor->fds[i].revents & POLLIN)
            {
                
                loopReactor->handlers[i](reac, loopReactor->fds[i].fd);
            }
        }
    }
    return NULL;
}

