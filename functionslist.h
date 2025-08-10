#ifndef FUNCTIONS_LIST_H
#define FUNCTIONS_LIST_H

#include "functions.h"

#define FUNC_COUNT 8

void (*functions_list[FUNC_COUNT])(char*, char*) = {
    helloworld, // 0
    square, // 1
    cube, // 2
    helloworld, // 3
    pingpong, // 4
    prime, // 5
    fibonacci // 6
};

#endif