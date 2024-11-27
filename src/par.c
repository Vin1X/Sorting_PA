#include "../include/par.h"

void *ParallelSort(void *arg)
{
    ThreadData *data = (ThreadData *)arg;
    Sort(data->head_ref);
    pthread_exit(NULL);
}

int main()
{
    FILE *log_file = fopen(LOG_FILE, "w");

    printf("Generating list with %d nodes...\n", NODE_COUNT);
    Node *list = Gen(NODE_COUNT);

    clock_t start_time = clock();

    Node *sublists[NUM_THREADS];
    int sublist_size = NODE_COUNT / NUM_THREADS;

    Node *current = list;
    for (int i = 0; i < NUM_THREADS; i++)
    {
        sublists[i] = current;
        for (int j = 0; j < sublist_size - 1 && current; j++)
        {
            current = current->next;
        }
        if (current)
        {
            Node *next = current->next;
            if (next)
                next->prev = NULL;
            current->next = NULL;
            current = next;
        }
    }

    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++)
    {
        thread_data[i].head_ref = &sublists[i];
        thread_data[i].thread_id = i;
        thread_data[i].num_threads = NUM_THREADS;
        pthread_create(&threads[i], NULL, ParallelSort, &thread_data[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    Node *merged = sublists[0];
    for (int i = 1; i < NUM_THREADS; i++)
    {
        Sort(&merged);
        merged = merged->next;
        Node *temp = merged;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = sublists[i];
        sublists[i]->prev = temp;
    }

    clock_t end_time = clock();

    double duration = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    fprintf(log_file, "Amount of nodes: %d\n", NODE_COUNT);
    fprintf(log_file, "Threads: %d\n", NUM_THREADS);
    fprintf(log_file, "Sort duration: %.2f seconds\n", duration);
    fclose(log_file);

    ListOut(merged, 0, 10);
    ListOut(merged, NODE_COUNT - 10, NODE_COUNT);

    ListFree(merged);

    return EXIT_SUCCESS;
}
