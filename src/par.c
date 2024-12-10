/* This files handle the parallel sorting */
#include "../include/par.h"

/**
 * This function is being passed to each thread which processes a sublist
 *
 * Parameter:
 *  void *arg Being the sublist
 */
void *ThrdFunc(void *arg)
{
    ThreadData *data = (ThreadData *)arg;

    clock_t start_time = clock();
    Sort(&data->head);
    clock_t end_time = clock();

    double duration = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    pthread_mutex_lock(&mutex);
    fprintf(log_file, "Thread id: %d\n", data->id);
    fprintf(log_file, "Start time: %.2f seconds\n", start_time);
    fprintf(log_file, "End time: %.2f seconds\n", end_time);
    fprintf(log_file, "Sort duration: %.2f seconds\n", duration);
    pthread_mutex_unlock(&mutex);

    // Debugging
    // ListOut(data->head, 0, NODE_COUNT);

    pthread_exit(NULL);
}

int main()
{
    log_file = fopen(LOG_FILE, "w");

    printf("Generating list with %d nodes...\n", NODE_COUNT);
    Node *list = Gen(NODE_COUNT);
    Node *sublists[THREAD_COUNT];

    clock_t start_time = clock();

    // Fill sublists
    Node *head = list;
    int sublist_size = NODE_COUNT / THREAD_COUNT; // Inaccurate
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        // Assign head to head of sublist
        sublists[i] = head;

        // Iterate through list inorder to reach end of sublist
        for (int j = 0; j < sublist_size - 1 && head; j++)
        {
            head = head->next;
        }
        if (head)
        {
            // Save head for next sublist
            Node *next_list = head->next;

            // Split node and reassign head for next sublist
            if (next_list) // Incase we reach last node
            {
                next_list->last = NULL;
            }
            head->next = NULL;
            head = next_list;
        }
    }

    // Create threads
    pthread_t threads[THREAD_COUNT];
    ThreadData thread_data[THREAD_COUNT];
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        thread_data[i].head = sublists[i];
        thread_data[i].id = i;
        pthread_create(&threads[i], NULL, ThrdFunc, &thread_data[i]);
    }

    // Release threads
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // Merge sublists to list
    Node *merged = thread_data[0].head;
    for (int i = 1; i < THREAD_COUNT; i++)
    {
        merged = merge_lists(merged, thread_data[i].head);
    }

    // Calculate duration
    clock_t end_time = clock();
    double duration = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Logging
    fprintf(log_file, "Amount of nodes: %d\n", NODE_COUNT);
    fprintf(log_file, "Threads: %d\n", THREAD_COUNT);
    fprintf(log_file, "Total start time: %.2f seconds\n", start_time);
    fprintf(log_file, "Total end time: %.2f seconds\n", end_time);
    fprintf(log_file, "Total sort duration: %.2f seconds\n", duration);
    fclose(log_file);

    // Debugging
    ListOut(merged, NODE_COUNT - 100, NODE_COUNT);

    // Deallocate
    ListFree(merged);
    return EXIT_SUCCESS;
}

/**
 * This function merges/sorts 2 double linked lists.
 * For ease we make a dummy of type Node as a placeholder
 * and current with a pointer on the dummy Node.
 * We also ensure that the double linked list stays consistent.
 *
 * Parameters:
 *    Node *list1 Pointer to sorted/unsorted list
 *    Node *list2 Pointer to sorted/unsorted list
 *
 * Returns:
 *    Node* Pointer to the head of the merged list
 */
Node *merge_lists(Node *list1, Node *list2)
{
    Node dummy;             // Placeholder
    Node *current = &dummy; // Pointer to dummy node
    dummy.next = NULL;      // Make sure next node is empty

    // This runs until one or both lists are empty
    while (list1 && list2)
    {
        // Check which node has the smaller or equal value and attach it to the merged list
        if (list1->data <= list2->data)
        {
            current->next = list1; // Add node to placeholder
            list1->last = current; // Update last node to placeholder
            list1 = list1->next;   // Point to next node
        }
        else
        {
            current->next = list2; // Add node to placeholder
            list2->last = current; // Update last node to placeholder
            list2 = list2->next;   // Point to next node
        }
        current = current->next; // Point to next node
    }

    // Add remaining nodes to placeholder
    if (list1)
    {
        current->next = list1; // Add rest to the merged list
        list1->last = current; // Update remaining node to point to the merged list
    }
    else if (list2)
    {
        current->next = list2; // Add rest to the merged list
        list2->last = current; // Update remaining node to point to the merged list
    }

    return dummy.next; // Points to first node in sorted list
}
