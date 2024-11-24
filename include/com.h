#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

void Sort(Node**);
Node* Gen(int);
Node* Reserve();
void ListOut(Node*, int, int);
void ListFree(Node*);