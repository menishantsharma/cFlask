#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "functions.h"

// 1. SQUARE
void square(char* arg, char* response) {
    int num = (arg != NULL && atoi(arg) != 0) ? atoi(arg) : 1;
    sprintf(response, "%d", num*num);
}

// 2. CUBE
void cube(char* arg, char* response) {
    int num = (arg != NULL && atoi(arg) != 0) ? atoi(arg) : 1;
    sprintf(response, "%d", num * num * num);
}

void helloworld(char* arg, char* response) {
    if(arg == NULL || strlen(arg) == 0) sprintf(response, "Hello");
    else sprintf(response, "Hello, %s", arg);
}

void pingpong(char* arg, char* response) {
    if(arg == NULL || strlen(arg) == 0) sprintf(response, "PingPong");
    else sprintf(response, "%s", arg);
}

void prime(char* arg, char* response) {
    long long int num = (arg!=NULL && atoi(arg)!=0) ? atoi(arg) : 0;
    int isPrime = 1;

    if(num < 2) isPrime = 0;
    else {
        for(long long int i=2; i*i<=num; i++) {
            if(num % i == 0) {
                isPrime = 0;
                break;
            }
        }
    }

    sprintf(response, isPrime ? "True" : "False");
}

void fibonacci(char* arg, char* response) {
    long long int k = (arg!=NULL && atoi(arg)!=0) ? atoi(arg) : 0;
    long long int prev = 0, cur = 1, fib;

    if(k==0 || k == 1) sprintf(response, "%lld", k);
    else {
        for(long long int i=2; i<=k; i++) {
            fib = prev+cur;
            prev = cur;
            cur = fib;
        }
        sprintf(response, "%lld", fib);
    }
}

