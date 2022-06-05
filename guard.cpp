#include <iostream>
#include <stdexcept>
#include "guard.hpp"
/**
 *
       * The strtok() function uses a static buffer while parsing, so
         it's not thread safe. even with guard class it won't work.
 */

guard::~guard() noexcept
{
    pthread_mutex_unlock(&lock);
}

guard::guard(pthread_mutex_t &lock) : lock(lock)
{
    pthread_mutex_lock(&lock);
}
