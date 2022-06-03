
#include <iostream>
#include <string>
#include <ctype.h>
#include <assert.h>
#include "activeObject.hpp"
#include "safeQueue.hpp"
#include "data.hpp"
#include "util.hpp"

activeObject* ao1;
activeObject *object1;
activeObject *object2;
activeObject *object3;

int main() {
    // Create a safe queue
    safeQueue *queue = new safeQueue(10);

    // Create 5 data objects
    data *d1 = new data("HelLo 1", 1);
    data *d2 = new data("HelLo 2", 2);
    data *d3 = new data("HelLo 3", 3);
    data *d4 = new data("HelLo 4", 4);
    data *d5 = new data("HelLo 5", 5);
    
    
    assert(d1 != NULL);
    assert(d2 != NULL);
    assert(d3 != NULL);
    assert(d4 != NULL);
    assert(d5 != NULL);


    std::cout << "before:" << std::endl;

    // print the data objects
    printData(d1);
    printData(d2);
    printData(d3);
    printData(d4);
    printData(d5);

    // print new line
    std::cout << std::endl;
    // enQ the data objects into the queue
    queue->enQ(d1);
    queue->enQ(d2);
    queue->enQ(d3);
    queue->enQ(d4);
    queue->enQ(d5);

    //deQ the data objects from the queue
    data *a1 = (data*) queue->deQ();
    data *a2 = (data*) queue->deQ();
    data *a3 = (data*) queue->deQ();
    data *a4 = (data*) queue->deQ();
    data *a5 = (data*) queue->deQ();
  


    // // Create an active object
    ao1 = new activeObject(&caesarCipher, &printData, 5);

    // std::cout << "after:" << std::endl;
    // // enQ the data objects into the active object
    ao1->getQueue()->enQ(d1);
    ao1->getQueue()->enQ(d2);
    ao1->getQueue()->enQ(d3);
    ao1->getQueue()->enQ(d4);
    ao1->getQueue()->enQ(d5);

    // std::getchar();
    pthread_join(ao1->getThread(), NULL);

    return 0;
}