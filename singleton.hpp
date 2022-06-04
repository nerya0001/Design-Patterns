#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <iostream>
#include <stdexcept>
#include <pthread.h>

template<typename T>
class singleton {
private:
    static T *instance;
    static pthread_mutex_t mutex;

    singleton() {}

    ~singleton() {}

    singleton(const singleton &);

    singleton &operator=(const singleton &);

public:
    static T *getInstance() {
        if (instance == NULL) {
            pthread_mutex_lock(&mutex);
            if (instance == NULL) {
                instance = new T();
            }
            pthread_mutex_unlock(&mutex);
        }
        return instance;
    }
};

template<typename T>
T *singleton<T>::instance = nullptr;
template<typename T>
pthread_mutex_t singleton<T>::mutex;
#endif
