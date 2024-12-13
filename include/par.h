#ifndef PAR_H
#define PAR_H

#include <pthread.h>
#include "com.h"

#define LOG_FILE "par.log" // File name
#define THREAD_COUNT 4

FILE *log_file;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Data for each thread
typedef struct
{
    Node *head;
    int id;
} ThreadData;

int main();

#endif
