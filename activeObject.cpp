#include <unistd.h>
#include "activeObject.hpp"
#include "guard.hpp"


activeObject::activeObject(void *(*first)(void *data), void *(*second)(void *data), int size) : func1(
        first), func2(second) {
    this->queue = new safeQueue(size);
    pthread_create(&thread, NULL, &run, &(*this));
}

activeObject::activeObject::~activeObject() {
    delete queue;
}

void *activeObject::run(void *activeObj) {
    auto *object = (activeObject *) activeObj;
    while (true) {
        data *d = (data *) object->getQueue()->deQ();
        if (d != NULL) {
            void *result = object->func1(d);
            // make sure func2 is not null
            if (object->func2 != NULL) {
                object->func2(result);
            }
        }
    }
    return NULL;
}
//void *activeObject::run(void* activeObj) {
//    while (true) {
//        data *d = (data *) this->queue->deQ();
//        if (d != NULL) {
//            void *result = this->func1(d);
//            // make sure func2 is not null
//            if (this->func2 != NULL) {
//                this->func2(result, (void *) this);
//            }
//        }
//    }
//    return NULL;
//}

safeQueue *activeObject::getQueue() {
    return (this->queue);
}
