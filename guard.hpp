#ifndef GUARD_HPP
#define GUARD_HPP

#include <iostream>
#include <stdexcept>
#include <pthread.h>

class guard
{
private:
    pthread_mutex_t &lock;

    guard(const guard &);
    guard &operator=(const guard &);

    void unlock()
    {
        pthread_mutex_unlock(&lock);
    }

    void lock()
    {
        pthread_mutex_lock(&lock);
    }

    void check_lock()
    {
        if (pthread_mutex_trylock(&lock) != 0)
        {
            throw std::runtime_error("lock failed");
        }
    }


public:
    guard(pthread_mutex_t &lock) : lock(lock)
    {
        check_lock();
    }

    ~guard()
    {
        unlock();
    }
};


   

#endif
