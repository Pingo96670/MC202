#include <stdlib.h>
#include "cache_prio-queue.h"

#define INITIAL_ARRAY_SIZE 4
#define PARENT(heap_pos) ((heap_pos-1)/2)
#define L_CHILD(heap_pos) (2*heap_pos+1)
#define R_CHILD(heap_pos) (2*heap_pos+2)
#define DUMMY_POS -1
#define NEXT_POS(heap_pos) prio_q->data_array[heap_pos]->positions[prio_q->data_array[heap_pos]->current_index]
#define IS_DONE(heap_pos) prio_q->data_array[heap_pos]->current_index==prio_q->data_array[heap_pos]->n_elements
#define POS_IN_HEAP(heap_pos) prio_q->cache_heap_pos_array[prio_q->data_array[heap_pos]->value]


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

// Function to initialize the cache as a priority queue
// Returns the initialized struct
prio_queue initialize_cache(int cache_size, int n_accesses, int n_distinct) {
    int i;
    prio_queue prio_q;

    prio_q=malloc(sizeof(struct priority_queue));
    prio_q->data_array=malloc(cache_size*sizeof(pos_array));
    prio_q->aux_cache_array=calloc(n_distinct, sizeof(int));
    prio_q->cache_heap_pos_array=malloc(n_distinct*sizeof(int));
    
    for (i=0; i<cache_size; i++) {
        prio_q->data_array[i]=initialize_array(INITIAL_ARRAY_SIZE, n_accesses, i);
    }

    for (i=0; i<n_distinct; i++) {
        prio_q->cache_heap_pos_array[i]=DUMMY_POS;
    }

    prio_q->n_elements=0;

    return prio_q;
}

// Function to send a value up the heap
// Alters the heap and the auxiliary array directly
void up_heap(prio_queue prio_q, int heap_pos) {
    if (heap_pos>0 && !(IS_DONE(PARENT(heap_pos))) && (IS_DONE(heap_pos) || NEXT_POS(PARENT(heap_pos))<NEXT_POS(heap_pos))) {
        swap_pos_array(&prio_q->data_array[heap_pos], &prio_q->data_array[PARENT(heap_pos)]);
        swap_int(&POS_IN_HEAP(heap_pos), &POS_IN_HEAP(PARENT(heap_pos)));
        up_heap(prio_q, PARENT(heap_pos));
    }
}

// Function to send a value down the heap
// Alters the heap and the auxiliary array directly
void down_heap(prio_queue prio_q, int heap_pos) {
    int highest_child;

    if (L_CHILD(heap_pos)<prio_q->n_elements) {
        highest_child=L_CHILD(heap_pos);

        if (R_CHILD(heap_pos)<prio_q->n_elements && !(IS_DONE(L_CHILD(heap_pos))) &&
            (IS_DONE(R_CHILD(heap_pos)) || NEXT_POS(L_CHILD(heap_pos))<NEXT_POS(R_CHILD(heap_pos))))
            highest_child = R_CHILD(heap_pos);
        if (IS_DONE(highest_child) || NEXT_POS(heap_pos)<NEXT_POS(highest_child)) {
            swap_pos_array(&prio_q->data_array[heap_pos], &prio_q->data_array[highest_child]);
            swap_int(&POS_IN_HEAP(heap_pos), &POS_IN_HEAP(highest_child));
            down_heap(prio_q, highest_child);
        }
    }
}

// Function to decrease the priority value of a certain heap position
// Alters the value directly
void increase_removal_priority(prio_queue cache, int current_num) {
    cache->data_array[cache->cache_heap_pos_array[current_num]]->current_index++;
    up_heap(cache, cache->cache_heap_pos_array[current_num]);
}

// Removes the value with max key from the cache
// Swaps the first and last items, then reduces n_elements by one
// If needed, down heaps the item which ended up in the first position
void pop_max(prio_queue cache) {
    cache->aux_cache_array[cache->data_array[0]->value]=0;
    swap_pos_array(&cache->data_array[0], &cache->data_array[cache->n_elements-1]);
    cache->cache_heap_pos_array[cache->data_array[0]->value]=0;
    cache->cache_heap_pos_array[cache->data_array[cache->n_elements-1]->value]=-1;
    cache->n_elements--;

    if (cache->data_array[0]->current_index!=cache->data_array[0]->n_elements) {
        down_heap(cache, 0);
    }
}