#include "../include/com.h"

void Sort(Node** head_ref) {
    Node* head = *head_ref;

    if (!head || !head->next) {
        return;
    }

    Node* slow = head;
    Node* fast = head->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node* mid = slow->next;
    slow->next = NULL;
    if (mid) {
        mid->prev = NULL;
    }

    Sort(&head);
    Sort(&mid);

    Node dummy = {0, NULL, NULL};
    Node* tail = &dummy;

    Node* left = head;
    Node* right = mid;

    while (left && right) {
        if (left->data < right->data) {
            tail->next = left;
            left->prev = tail;
            left = left->next;
        } else {
            tail->next = right;
            right->prev = tail;
            right = right->next;
        }
        tail = tail->next;
    }

    tail->next = (left) ? left : right;
    if (tail->next) {
        tail->next->prev = tail;
    }

    Node* sorted_head = dummy.next;
    if (sorted_head) {
        sorted_head->prev = NULL;
    }
    *head_ref = sorted_head;
}

Node* Gen(int count) {
    Node* head = NULL;
    Node* tail = NULL;
    for (int i = 0; i < count; i++) {
        Node* newNode = Reserve();
        if (!head) {
            head = newNode;
            tail = head;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    return head;
}

Node* Reserve() {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = rand();
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void ListOut(Node* start, int start_node, int end_node) {
    if (!start) {
        return; 

    int total_nodes = 0;
    Node* current = start;
    while (current) {
        total_nodes++;
        current = current->next;
    }

    if (start_node < 1 || start_node > total_nodes) {
        start_node = 1;
    }
    if (end_node < 1 || end_node > total_nodes) {
        end_node = total_nodes; 
    }

    current = start;
    int current_index = 1; 
    while (current && current_index <= end_node) {
        if (current_index >= start_node) {
            printf("Knoten %d: %d\n", current_index, current->data);
        }
        current = current->next;
        current_index++;
        }
    }
}

void ListFree(Node* head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}
