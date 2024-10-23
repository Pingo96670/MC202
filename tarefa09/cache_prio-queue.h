#include "cache_array.h"


// Priority queue structure
    // Highest priority: lowest data_array[n][0] (appears first)
    // If empty, lowest priority
typedef struct priority_queue* prio_queue;
struct priority_queue {
    int len;
    int n_elements;
    pos_array* data_array;  // Actual priority queue
};


// Function to swap two integers by reference
void swap_int(int* a, int* b);

// Function to swap two pos_array structs by reference
void swap_pos_array(pos_array* a, pos_array* b);

// Function to initialize a priority queue
// Returns the initialized struct
prio_queue initialize_priority_queue(int len, int n_accesses);

// Function to send a value orig_num up the heap
void up_heap(prio_queue prio_q, int heap_pos, int orig_num, int* heap_pos_array, int n_distinct);

// Function to send a value orig_num down the heap
void down_heap(prio_queue prio_q, int heap_pos, int orig_heap_pos, int* heap_pos_array);

// Function to decrease the priority value of a certain heap position
void decrease_priority(prio_queue prio_q, int heap_pos, int* heap_pos_array);