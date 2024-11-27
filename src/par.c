/* This files handle the parallel sorting */
#include "../include/par.h"

/**
 * This function is being passed to each thread which processes a sublist
 *
 * Parmeter:
 *  *arg being the sublist
 */
void *ThrdFunc(void *arg)
{
    ThreadData *data = (ThreadData *)arg;

    // Sort
    clock_t start_time = clock();
    Sort(&data->head);
    clock_t end_time = clock();

    // Calculate duration
    double duration = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Logging
    pthread_mutex_lock(&mutex);
    fprintf(log_file, "Thread id: %d\n", data->id);
    fprintf(log_file, "Sort duration: %.2f seconds\n", duration);
    pthread_mutex_unlock(&mutex);

    // Debugging
    // ListOut(data->head, 0, NODE_COUNT);

    pthread_exit(NULL);
}

int main()
{
    // Create file
    log_file = fopen(LOG_FILE, "w");

    // Create list
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
    fprintf(log_file, "Sort duration: %.2f seconds\n", duration);
    fclose(log_file);

    // Debugging
    ListOut(merged, NODE_COUNT - 100, NODE_COUNT);

    // Deallocate
    ListFree(merged);
    return EXIT_SUCCESS;
}

Node *merge_lists(Node *list1, Node *list2)
{
    Node dummy;
    Node *tail = &dummy;
    dummy.next = NULL;

    while (list1 && list2)
    {
        if (list1->data <= list2->data)
        {
            tail->next = list1;
            list1->last = tail;
            list1 = list1->next;
        }
        else
        {
            tail->next = list2;
            list2->last = tail;
            list2 = list2->next;
        }
        tail = tail->next;
    }

    if (list1)
    {
        tail->next = list1;
        list1->last = tail;
    }
    else if (list2)
    {
        tail->next = list2;
        list2->last = tail;
    }

    return dummy.next;
}
