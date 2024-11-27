#ifndef PAR_H
#define PAR_H

#include <time.h>
#include <pthread.h>
#include "com.h"

#define LOG_FILE "par.log"
#define NODE_COUNT 10000000
#define THREAD_COUNT 4

FILE *log_file;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct
{
    Node *head;
    int id;
} ThreadData;

int main();
Node *merge_lists(Node *list1, Node *list2);

#endif
