#include "../include/par.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
FILE *log_file;

void *ThrdFunc(void *arg)
{
    ThreadData *data = (ThreadData *)arg;

    clock_t start_time = clock();
    Sort(&data->head);
    clock_t end_time = clock();
    double duration = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // ListOut(data->head, 0, NODE_COUNT);
    pthread_mutex_lock(&mutex);
    fprintf(log_file, "Thread id: %d\n", data->id);
    fprintf(log_file, "Sort duration: %.2f seconds\n", duration);
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main()
{
    log_file = fopen(LOG_FILE, "w");

    printf("Generating list with %d nodes...\n", NODE_COUNT);
    Node *list = Gen(NODE_COUNT);
    Node *sublists[NUM_THREADS];

    clock_t start_time = clock();

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
        thread_data[i].head = sublists[i];
        thread_data[i].id = i;
        pthread_create(&threads[i], NULL, ThrdFunc, &thread_data[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    Node *merged = thread_data[0].head;
    Node *tail = merged;
    while (tail->next)
    {
        tail = tail->next;
    }

    for (int i = 1; i < NUM_THREADS; i++)
    {
        tail->next = sublists[i];
        sublists[i]->prev = tail;

        while (tail->next)
        {
            tail = tail->next;
        }
    }
    Sort(&merged);
    clock_t end_time = clock();

    double duration = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    fprintf(log_file, "Amount of nodes: %d\n", NODE_COUNT);
    fprintf(log_file, "Threads: %d\n", NUM_THREADS);
    fprintf(log_file, "Sort duration: %.2f seconds\n", duration);
    fclose(log_file);

    // ListOut(merged, 0, 10);
    // ListOut(merged, NODE_COUNT - 100, NODE_COUNT - 10);

    ListFree(merged);
    free();

    return EXIT_SUCCESS;
}
