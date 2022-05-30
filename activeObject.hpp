#ifndef ACTIVEOBJECT_HPP
#define ACTIVEOBJECT_HPP

#include <iostream>
#include <stdexcept>
#include <pthread.h>
#include "safeQueue.hpp"
#include "data.hpp"

class activeObject
{

private:
    safeQueue *queue;
    pthread_t thread;
//    void *(*func1)(void *data);
//    void *(*func2)(void *data,void* object);

public:
    activeObject(void *(*first)(void *data), void *(*second)(void *data,void* object), int size);
    activeObject() = default;
    ~activeObject();
    safeQueue* getQueue();
    void *(*func1)(void *data);
    void *(*func2)(void *data,void* object);
    static void *run(void* activeObj);
};

#endif
