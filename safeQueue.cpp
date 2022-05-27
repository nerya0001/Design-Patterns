
#include "safeQueue.hpp"


using namespace std;


safeQueue::safeQueue(int size) {
    arr = new void*[size];
    capacity = size;
    front = 0;
    rear = 0;
    count = 0;
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cv, NULL);
}


safeQueue::~safeQueue() {
    delete[] arr;
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cv);
}


bool safeQueue::isFull() {
    return count == capacity;
}


bool safeQueue::isEmpty() {
    return count == 0;
}


void *safeQueue::deQ() {
    void *item;
    pthread_mutex_lock(&lock);
    while (isEmpty()) {
        pthread_cond_wait(&cv, &lock);
    }
    item = arr[front];
    front = (front + 1) % capacity;
    count--;
    pthread_cond_signal(&cv);
    pthread_mutex_unlock(&lock);
    return item;
}


void safeQueue::enQ(void *item) {
    pthread_mutex_lock(&lock);
    while (isFull()) {
        pthread_cond_wait(&cv, &lock);
    }
    arr[rear] = item;
    rear = (rear + 1) % capacity;
    count++;
    pthread_cond_signal(&cv);
    pthread_mutex_unlock(&lock);
}








