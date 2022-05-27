#ifndef ACTIVEOBJECT_HPP
#define ACTIVEOBJECT_HPP

#include <iostream>
#include <stdexcept>
#include "safeQueue.hpp"
#include "data.hpp"
#include "util.hpp"

class activeObject
{
private:
    safeQueue *queue;
    void* func1(void* data, void* (*func)(void*));
    void func2(void* data, void (*func)(void*));
    
public:
    activeObject();
    ~activeObject();
};
#endif
