#ifndef UTIL_HPP
#define UTIL_HPP

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdexcept>
#include "data.hpp"
#include "activeObject.hpp"


void* caesarCipher(void*);
void* reverseCapitalization(void*);
void* sendResult(void*);
void *moveToNext(void*,void*);

#endif
