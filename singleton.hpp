#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <iostream>
#include <stdexcept>

class singleton
{
private:
    static singleton *instance;
    static pthread_mutex_t lock;
    static pthread_mutex_t lock_init;
    static pthread_cond_t cv;
    static bool initialized;
    singleton();
    singleton(const singleton &);
    singleton &operator=(const singleton &);    
public:
    static singleton *getInstance() {
        if (!initialized) {
            pthread_mutex_lock(&lock_init);
            if (!initialized) {
                instance = new singleton();
                initialized = true;
            }
            pthread_mutex_unlock(&lock_init);
        }
        return instance;
    }
};

#endif
