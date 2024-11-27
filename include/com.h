#ifndef COM_H
#define COM_H

#include <stdio.h>
#include <stdlib.h>
#include "rand_z.h"

typedef struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

void Sort(Node **head_ref);
Node *Gen(int count);
Node *Reserve();
void ListOut(Node *start, int start_node, int end_node);
void ListFree(Node *head);

#endif