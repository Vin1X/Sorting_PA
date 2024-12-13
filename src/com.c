#include "../include/com.h"

/**
 * This is a implementation of the merge sort in O(n log n)
 */
void Sort(Node **list_head)
{
    Node *head = *list_head;

    if (head && head->next)
    {
        Node *slow = head;
        Node *fast = head->next;

        // Find middle node
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        // Split mid node
        Node *mid = slow->next;
        slow->next = NULL;
        if (mid)
        {
            mid->last = NULL;
        }

        // Recursive call
        Sort(&head);
        Sort(&mid);

        // Merge both lists
        Node *merged = merge_lists(head, mid);

        *list_head = merged;
    }
}

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
    if (node)
    {
    }
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
        if ((index >= start_node && index <= end_node) || start_node >= NODE_COUNT || end_node > NODE_COUNT || start_node < 0 || start_node > end_node)
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

/**
 * This function merges/sorts 2 double linked lists and is part of the merge sort.
 * For ease we make a dummy as a placeholder.
 * We also ensure that the double linked list stays consistent.
 *
 * Parameters:
 *    Node *left Pointer to sorted/unsorted list
 *    Node *right Pointer to sorted/unsorted list
 *
 * Returns:
 *    Node* Pointer to the head of the merged list
 */
Node *merge_lists(Node *left, Node *right)
{
    Node dummy;             // Placeholder
    Node *current = &dummy; // Pointer to dummy node
    dummy.next = NULL;      // Make sure next node is empty

    while (left && right)
    {
        // Check which node has the smaller or equal value and attach it to the merged list
        if (left->data <= right->data)
        {
            current->next = left;
            left->last = current;
            left = left->next;
        }
        else
        {
            current->next = right;
            right->last = current;
            right = right->next;
        }
        current = current->next; // Point to next node
    }

    // Add remaining nodes to placeholder
    if (left)
    {
        current->next = left;
        left->last = current;
    }
    else if (right)
    {
        current->next = right;
        right->last = current;
    }
    return dummy.next;
}
