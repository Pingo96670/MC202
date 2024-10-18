#include <stdio.h>
#include <stdlib.h>

typedef struct array {
    int* positions;
    int n_elements;
} array;

typedef struct priority_queue* prio_queue;
typedef struct priority_queue {
    int len;
    int n;
    array* position_array;
};

// Array functions yet to be added

void swap(int* a, int* b) {}

prio_queue create_priority_queue(int len) {}

void up_heap(prio_queue prio_q, int k) {}

void insert(prio_queue prio_q, int n) {}

void down_heap(prio_queue prio_q, int k) {}

int extract_max(prio_queue prio_q) {}

void edit_priority(prio_queue prio_q, int k, int new_value) {}


int main() {
    int cache_size, range, n_accesses, *access_list, i;
    prio_queue prio_q;

    scanf("%d %d %d", &cache_size, &range, &n_accesses);

    access_list=malloc(n_accesses*sizeof(int));

    for (i=0; i<n_accesses; i++) {
        scanf("%d", &access_list[i]);
    }

    free(access_list);
    free(prio_q->position_array->positions);
    free(prio_q->position_array);

    return 0;
}