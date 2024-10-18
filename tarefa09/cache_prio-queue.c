#include <stdlib.h>
#include "cache_prio-queue.h"
#define INITIAL_ARRAY_SIZE 4

void swap(int* a, int* b) {
    int temp;

    temp=*a;
    *a=*b;
    *b=temp;
}

prio_queue initialize_priority_queue(int n_distinct) {
    int i;
    prio_queue prio_q;

    prio_q=malloc(sizeof(prio_q));
    prio_q->data_array=malloc(n_distinct*sizeof(pos_array));
    
    for (i=0; i<n_distinct; i++) {
        prio_q->data_array[i]->positions=initialize_array(INITIAL_ARRAY_SIZE);
    }

    prio_q->n_elements=0;
    prio_q->len=n_distinct;

    return prio_q;
}

void up_heap(prio_queue prio_q, int heap_pos) {
    
}

void insert(prio_queue prio_q, int n) {

}

void down_heap(prio_queue prio_q, int heap_pos) {}

int extract_max(prio_queue prio_q) {}

void edit_priority(prio_queue prio_q, int heap_pos, int new_value) {}