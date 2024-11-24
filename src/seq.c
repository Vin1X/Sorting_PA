#include "../include/seq.h"

#define NODE_COUNT 10000000

int main() {
    FILE* log_file = fopen(LOG_FILE, "w");

    printf("Generiere Liste mit %d Knoten...\n", NODE_COUNT);
    Node* list = Gen(NODE_COUNT);

    clock_t start_time = clock();

    Sort(&list);

    clock_t end_time = clock();

    double duration = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    fprintf(log_file, "Anzahl der Knoten: %d\n", NODE_COUNT);
    fprintf(log_file, "Sortierdauer: %.2f Sekunden\n", duration);
    fclose(log_file);

    ListOut(list, 0, NODE_COUNT);

    ListFree(list);

    return EXIT_SUCCESS;
}
