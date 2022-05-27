#ifndef UTIL_HPP
#define UTIL_HPP

#include <iostream>
#include <stdexcept>
#include "data.hpp"
#include "activeObject.hpp"
#include "safeQueue.hpp"

activeObject object1;
activeObject object2;
activeObject object3;

void* (*caesarCipher)(void*);
void* (*reverseCapitalization)(void*);
void* (*sendResult)(void*);
void (*moveToNext)(void*);

#endif
