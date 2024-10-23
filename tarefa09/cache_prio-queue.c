#include <stdlib.h>
#include "cache_prio-queue.h"
#define INITIAL_ARRAY_SIZE 4
#define PARENT(heap_pos) ((heap_pos-1)/2)
#define L_CHILD(heap_pos) (2*heap_pos+1)
#define R_CHILD(heap_pos) (2*heap_pos+2)
#define NEXT_POS(heap_pos) prio_q->data_array[heap_pos]->positions[prio_q->data_array[heap_pos]->current_index]
#define IS_DONE(heap_pos) prio_q->data_array[heap_pos]->current_index==prio_q->data_array[heap_pos_array[heap_pos]]->n_elements


// Function to swap two integers by reference
void swap_int(int* a, int* b) {
    int temp;

    temp=*a;
    *a=*b;
    *b=temp;
}

// Function to swap two pos_array structs by reference
void swap_pos_array(pos_array* a, pos_array* b) {
    pos_array temp;

    temp=*a;
    *a=*b;
    *b=temp;
}

// Function to initialize a priority queue
// Returns the initialized struct
prio_queue initialize_priority_queue(int n_distinct, int n_accesses) {
    int i;
    prio_queue prio_q;

    prio_q=malloc(sizeof(prio_q));
    prio_q->data_array=malloc(n_distinct*sizeof(pos_array));
    
    // Initializing the actual priority queue
    for (i=0; i<n_distinct; i++) {
        prio_q->data_array[i]=initialize_array(INITIAL_ARRAY_SIZE, n_accesses, i);
    }

    prio_q->n_elements=0;
    prio_q->len=n_distinct;

    return prio_q;
}

// Function to send a value orig_num up the heap
// Alters the heap and the auxiliary array directly
void up_heap(prio_queue prio_q, int heap_pos, int orig_num, int* heap_pos_array, int n_distinct) {
    if (heap_pos>0 && NEXT_POS(PARENT(heap_pos))>NEXT_POS(heap_pos)) {

        swap_pos_array(&prio_q->data_array[heap_pos], &prio_q->data_array[PARENT(heap_pos)]);
        swap_int(&heap_pos_array[orig_num], &heap_pos_array[prio_q->data_array[heap_pos]->value]);
        
        up_heap(prio_q, PARENT(heap_pos), orig_num, heap_pos_array, n_distinct);
    }
}

// Function to send a value orig_num down the heap
// Alters the heap and the auxiliary array directly
void down_heap(prio_queue prio_q, int heap_pos, int orig_heap_pos, int* heap_pos_array) {
    int highest_child;

    if (L_CHILD(heap_pos)<prio_q->n_elements) {
        highest_child=L_CHILD(heap_pos);

        if (R_CHILD(heap_pos)<prio_q->n_elements && NEXT_POS(L_CHILD(heap_pos))>NEXT_POS(R_CHILD(heap_pos)) && !(IS_DONE(L_CHILD(heap_pos)))) {
            highest_child = R_CHILD(heap_pos);
        }

        if (NEXT_POS(heap_pos)>NEXT_POS(highest_child)) {

            swap_pos_array(&prio_q->data_array[heap_pos], &prio_q->data_array[highest_child]);
            swap_int(&heap_pos_array[orig_heap_pos], &heap_pos_array[highest_child]);

            down_heap(prio_q, highest_child, orig_heap_pos, heap_pos_array);
        }
    }
}

// Function to decrease the priority value of a certain heap position
// Alters the value directly
void decrease_priority(prio_queue prio_q, int heap_pos, int* heap_pos_array) {
    prio_q->data_array[heap_pos]->current_index++;
    down_heap(prio_q, heap_pos, heap_pos, heap_pos_array);
}