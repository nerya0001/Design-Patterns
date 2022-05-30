#include <unistd.h>
#include "activeObject.hpp"


activeObject::activeObject(void *(*first)(void *data), void *(*second)(void *data, void *object), int size) : func1(
        first), func2(second) {
    std::cout<<"1\n";
    this->queue = new safeQueue(size);
    std::cout<<"2\n";
    pthread_create(&thread, NULL, &run, &(*this));
    std::cout<<"3\n";
}

activeObject::activeObject::~activeObject() {
    delete queue;
}

void *activeObject::run(void *activeObj) {
    while (true) {
        auto *object = (activeObject *) activeObj;
        data *d = (data *) object->getQueue()->deQ();
        if (d != NULL) {
            void *result = object->func1(d);
            // make sure func2 is not null
            if (object->func2 != NULL) {
                object->func2(result, (void *) object);
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
