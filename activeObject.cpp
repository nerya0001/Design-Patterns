#include "activeObject.hpp"


activeObject::activeObject()
{
    queue = new safeQueue();
    while (true) {
        data *d = (data*)queue->deQ();
        state state = (state)d->getState();
        switch (state) {
            case state::begin:
                func2(func1(d, caesarCipher));
                break;
            case state::siphered:
                func2(func1(d, reverseCapitalization));
                break;
            case state::decapitalized:
                func2(func1(d, sendResult));
                break;
            default:
                break;
        } 
    }
}


activeObject::~activeObject()
{
    delete queue;
}


void* activeObject::func1(void* data, void* (*func)(void*))
{
    return func(data);
}


void activeObject::func2(void* data, void (*func)(void*))
{
    func(data);
}

