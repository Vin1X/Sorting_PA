#ifndef PAR_H
#define PAR_H

#include <time.h>
#include <pthread.h>
#include "com.h"

#define LOG_FILE "par.log"
#define NODE_COUNT 10000000
#define NUM_THREADS 4

typedef struct
{
    Node **head_ref;
    int thread_id;
    int num_threads;
} ThreadData;

int main();

#endif
