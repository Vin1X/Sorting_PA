#ifndef COM_H
#define COM_H

#include <stdio.h>
#include <stdlib.h>
#include "rand_z.h"

#define NODE_COUNT 1000

// Double linked list
typedef struct Node
{
    int data;
    struct Node *next;
    struct Node *last;
} Node;

void Sort(Node **head_ref);
Node *Gen(int count);
Node *Reserve();
void ListOut(Node *start, int start_node, int end_node);
void ListFree(Node *head);

#endif