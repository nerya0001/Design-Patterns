#include "activeObject.hpp"

activeObject(void *(*first)(void *data), void (*second)(void *data))
{
    queue = new safeQueue();
    this->func1 = first;
    this->func2 = second;

    pthread_create(&thread, NULL, &activeObject::run, this->queue);
}

activeObject::~activeObject()
{
    delete queue;
}

void *activeObject::run(void *queue)
{
    safeQueue *q = (safeQueue *)queue;
    while (1)
    {
        data *d = (data *)q->deQ();
        void *result = this->func1(d);
        this->func2(result);
    }
}
