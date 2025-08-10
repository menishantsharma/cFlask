#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define FUNC_COUNT 8

// Path to index
#define ROOT 0
#define SQUARE 1
#define CUBE 2
#define HELLOWORLD 3
#define PINGPONG 4
#define ARITHMETIC_PRIME 5
#define ARITHMETIC_FIBONACCI 6

#define URL_ROOT "/"
#define URL_SQUARE "/square"
#define URL_CUBE "/cube"
#define URL_HELLOWORLD "/helloworld"
#define URL_PINGPONG "/pingpong"
#define URL_ARITHMETIC_PRIME "/arithmetic/prime"
#define URL_ARITHMETIC_FIBONACCI "/arithmetic/fibonacci"


// Function Prototypes

void square(char* arg, char* response);
void cube(char *arg, char* response);
void helloworld(char *arg, char* response);
void pingpong(char *arg, char* response);
void prime(char *arg, char* response);
void fibonacci(char *arg, char* response);

#endif