#include "activeObject.hpp"
typedef void *(*THREADFUNCPTR)(void *);

activeObject::activeObject(void *(*first)(void *data), void *(*second)(void *data, void *object), int size) : func1(first), func2(second)
{
    this->queue = new safeQueue(size);
    pthread_create(&thread, NULL, (THREADFUNCPTR)&activeObject::run, &this->queue);
}

activeObject::activeObject::~activeObject()
{
    delete queue;
}

void *activeObject::run(void *queue)
{
    safeQueue *q = (safeQueue *)queue;
    while (true)
    {
        data *d = (data *)q->deQ();
        if (d != NULL)
        {
            void *result = this->func1(d);
            // make sure func2 is not null
            if (this->func2 != NULL)
            {
                this->func2(result, (void*)this);
            }
        }
    }
    return NULL;
}

safeQueue *activeObject::getQueue()
{
    return this->queue;
}
