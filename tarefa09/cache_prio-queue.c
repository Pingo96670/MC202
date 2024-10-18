#include <stdlib.h>
#include "cache_prio-queue.h"
#define INITIAL_ARRAY_SIZE 4
#define PARENT(heap_pos) ((heap_pos-1)/2)
#define L_CHILD(heap_pos) (2*heap_pos+1)
#define R_CHILD(heap_pos) (2*heap_pos+2)

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
    if (heap_pos>0 && prio_q->data_array[PARENT(heap_pos)]->positions[0]>prio_q->data_array[heap_pos]->positions[0]) {
        swap(&prio_q->data_array[heap_pos], &prio_q->data_array[PARENT(heap_pos)]);
        up_heap(prio_q, PARENT(heap_pos));
    }
}

void insert(prio_queue prio_q, int n) {

}

void down_heap(prio_queue prio_q, int heap_pos) {
    int highest_child;

    if (L_CHILD(heap_pos)<prio_q->n_elements) {
        highest_child=L_CHILD(heap_pos);

        if (R_CHILD(heap_pos)<prio_q->n_elements &&
            prio_q->data_array[L_CHILD(heap_pos)]->positions[0]>prio_q->data_array[R_CHILD(heap_pos)]->positions[0])
            highest_child = R_CHILD(heap_pos);
        if (prio_q->data_array[heap_pos]->positions[0]>prio_q->data_array[highest_child ]->positions[0]) {
            swap(&prio_q->data_array[heap_pos], &prio_q->data_array[highest_child]);
            down_heap(prio_q, highest_child);
        }
    }
}

int extract_max(prio_queue prio_q) {}

void edit_priority(prio_queue prio_q, int heap_pos, int new_value) {
    if (prio_q->data_array[heap_pos]->positions[0]==NULL || prio_q->data_array[heap_pos]->positions[0]>new_value) {
        prio_q->data_array[heap_pos]->positions[0]=new_value;
        up_heap(prio_q , heap_pos);
    } else {
        prio_q->data_array[heap_pos]->positions[0]=new_value;
        down_heap(prio_q, heap_pos);
    }
}