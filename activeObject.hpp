#ifndef ACTIVEOBJECT_HPP
#define ACTIVEOBJECT_HPP

#include <iostream>
#include <stdexcept>
#include <pthread.h>
#include "safeQueue.hpp"
#include "data.hpp"
#include "util.hpp"


class activeObject
{
private:
    safeQueue *queue;
    pthread_t thread;
    void* (*func1)(void* data);
    void (*func2)(void* data);
    
public:
    activeObject(void* (*first)(void* data), void (*second)(void* data));
    ~activeObject();
    void* run(void* queue);
};

#endif
