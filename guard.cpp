#include <iostream>
#include <stdexcept>
#include "guard.hpp"

guard::~guard() noexcept
{
    pthread_mutex_unlock(&lock);
}

guard::guard(pthread_mutex_t &lock) : lock(lock)
{
    pthread_mutex_lock(&lock);
}
