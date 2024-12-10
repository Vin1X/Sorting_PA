/* This file handles the sequential sorting */
#include "../include/seq.h"

int main()
{
    log_file = fopen(LOG_FILE, "w");

    printf("Generating list with %u nodes...\n", NODE_COUNT);
    Node *list = Gen(NODE_COUNT);

    clock_t start_time = clock();
    Sort(&list);
    clock_t end_time = clock();

    // Calculate duration
    double duration = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    fprintf(log_file, "Amount of nodes: %d\n", NODE_COUNT);
    fprintf(log_file, "Start time: %.2f seconds\n", start_time);
    fprintf(log_file, "End time: %.2f seconds\n", end_time);
    fprintf(log_file, "Sort duration: %.2f seconds\n", duration);
    fclose(log_file);

    // Debugging
    ListOut(list, 0, 10);

    // Deallocate
    ListFree(list);
    return EXIT_SUCCESS;
}
