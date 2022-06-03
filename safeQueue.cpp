
#include "safeQueue.hpp"


using namespace std;


safeQueue::safeQueue(int size) : arr(size,
                                     nullptr){
//    arr = new void*[size];
    capacity = size;
    front =0; 
    rear = 0;
    count = 0;
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cv, NULL);
}


safeQueue::~safeQueue() {
//    delete[] arr;
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
    // we need to wait until there is something to dequeue
    while (isEmpty()) {
        pthread_cond_wait(&cv, &lock);
    }
    item = arr[front];
    front = (front + 1) % capacity;
    count--;
    // signal that there is now room in the queue
    pthread_cond_signal(&cv);
    pthread_mutex_unlock(&lock);
    return item;
}


void safeQueue::enQ(void *item) {
    pthread_mutex_lock(&lock);
    // we need to check if the queue is full before we enqueue
    while (isFull()) {
        pthread_cond_wait(&cv, &lock);
    }
    arr[rear] = item;
    rear = (rear + 1) % capacity;
    count++;
    // signal that there is now an item in the queue
    pthread_cond_signal(&cv);
    pthread_mutex_unlock(&lock);
}








