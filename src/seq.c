#include "../include/seq.h"

int main()
{
    FILE *log_file = fopen(LOG_FILE, "w");

    printf("Generating list with %d nodes...\n", NODE_COUNT);
    Node *list = Gen(NODE_COUNT);

    clock_t start_time = clock();

    Sort(&list);

    clock_t end_time = clock();

    double duration = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    fprintf(log_file, "Amount of nodes: %d\n", NODE_COUNT);
    fprintf(log_file, "Sort duration: %.2f seconds\n", duration);
    fclose(log_file);

    ListOut(list, 0, NODE_COUNT);

    ListFree(list);

    return EXIT_SUCCESS;
}
