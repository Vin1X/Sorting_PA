#include "../include/com.h"

void Sort(Node **head_ref)
{
    Node *head = *head_ref;

    if (!head || !head->next)
    {
        return;
    }

    Node *slow = head;
    Node *fast = head->next;
    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node *mid = slow->next;
    slow->next = NULL;
    if (mid)
    {
        mid->last = NULL;
    }

    Sort(&head);
    Sort(&mid);

    Node dummy = {0, NULL, NULL};
    Node *tail = &dummy;

    Node *left = head;
    Node *right = mid;

    while (left && right)
    {
        if (left->data < right->data)
        {
            tail->next = left;
            left->last = tail;
            left = left->next;
        }
        else
        {
            tail->next = right;
            right->last = tail;
            right = right->next;
        }
        tail = tail->next;
    }

    tail->next = (left) ? left : right;
    if (tail->next)
    {
        tail->next->last = tail;
    }

    Node *sorted_head = dummy.next;
    if (sorted_head)
    {
        sorted_head->last = NULL;
    }
    *head_ref = sorted_head;
}

/**
 * This function generates nodes and allocates space
 *
 * Parameters:
 *  int count Amount of nodes which should be generated
 *
 * Returns:
 *  Node *head Starting address of list
 */
Node *Gen(int count)
{
    Node *head = NULL;
    Node *end = NULL;
    for (int i = 0; i < count; i++)
    {
        Node *node = Reserve();
        if (!head)
        {
            head = node;
            end = head;
        }
        else
        {
            end->next = node;
            node->last = end;
            end = node;
        }
    }
    return head;
}

Node *Reserve()
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = RandZ(1 + RandZ(2) % 9);
    node->next = NULL;
    node->last = NULL;
    return node;
}

void ListOut(Node *head, int start_node, int end_node)
{
    int index = 0;
    Node *current = head;
    while (current)
    {

        if ((index >= start_node && index <= end_node) || start_node >= NODE_COUNT || end_node > NODE_COUNT)
        {
            printf("Node %d: %d\n", index, current->data);
        }
        current = current->next;
        index++;
    }
}

void ListFree(Node *head)
{
    while (head)
    {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}
