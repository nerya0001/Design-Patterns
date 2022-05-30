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

    // void unlock();

    // void lock();

    // void check_lock();

public:
    guard(pthread_mutex_t &lock);

    ~guard() noexcept;
};

#endif
