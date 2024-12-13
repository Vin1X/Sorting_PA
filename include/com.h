#ifndef COM_H
#define COM_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rand_z.h"

#define NODE_COUNT 10000000

// Double linked list
typedef struct Node
{
    int data;
    struct Node *next;
    struct Node *last;
} Node;

void Sort(Node **list_head);
Node *Gen(int count);
Node *Reserve();
void ListOut(Node *start, int start_node, int end_node);
void ListFree(Node *head);
Node *merge_lists(Node *left, Node *right);

#endif
