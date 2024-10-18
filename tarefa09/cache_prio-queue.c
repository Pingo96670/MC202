#include <stdlib.h>
#include "cache_prio-queue.h"

void swap(int* a, int* b) {
    int temp;

    temp=*a;
    *a=*b;
    *b=temp;
}

prio_queue initialize_priority_queue(int n_distinct) {
    prio_queue prio_q;

    prio_q=malloc(sizeof(prio_q));
    prio_q->data_array=malloc(n_distinct*sizeof(pos_array));

    prio_q->n_elements=0;
    prio_q->len=n_distinct;

    return prio_q;
}

void up_heap(prio_queue prio_q, int k) {
    
}

void insert(prio_queue prio_q, int n) {

}

void down_heap(prio_queue prio_q, int k) {}

int extract_max(prio_queue prio_q) {}

void edit_priority(prio_queue prio_q, int k, int new_value) {}