#ifndef SAFEQUEUE_HPP
#define SAFEQUEUE_HPP

#include <iostream>
#include <cstdlib>
#include <pthread.h>

class safeQueue {
private:
    void *arr;
    int capacity;
    int front;
    int rear;
    int count;
    pthread_mutex_t lock;
    pthread_cond_t cv;
public:
    safeQueue(int size);
    ~safeQueue();
    bool isFull();
    bool isEmpty();
    void *deQ();
    void enQ(void *item);
};

#endif
