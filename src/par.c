#include "../include/par.h"

void *ThrdFunc(void *arg)
{
    ThreadData *data = (ThreadData *)arg;

    clock_t start_time = clock();
    Sort(&data->head);
    clock_t end_time = clock();

    // Calculate duration
    double duration = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Thread safe logging
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
    log_file = fopen(LOG_FILE, "w");

    printf("Generating list with %d nodes...\n", NODE_COUNT);
    Node *list = Gen(NODE_COUNT);
    Node *sublists[THREAD_COUNT];

    clock_t start_time = clock();
    int sublist_size = NODE_COUNT / THREAD_COUNT; // Inaccurate

    // Create threads
    pthread_t threads[THREAD_COUNT];
    ThreadData thread_data[THREAD_COUNT];

    // Fill sublists
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        sublists[i] = list;

        // Iterate through list inorder to reach end of sublist
        for (int j = 0; j < sublist_size - 1 && list; j++)
        {
            list = list->next;
        }
        if (list)
        {
            Node *next_list = list->next;

            // Split node and reassign list for next sublist
            if (next_list)
            {
                next_list->last = NULL;
            }
            list->next = NULL;
            list = next_list;
        }
    }

    // Start threads
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
    fprintf(log_file, "Total sort duration: %.2f seconds\n", duration);
    fclose(log_file);

    // Debugging
    ListOut(merged, NODE_COUNT - 100, NODE_COUNT);

    // Deallocate
    ListFree(merged);
    return EXIT_SUCCESS;
}
