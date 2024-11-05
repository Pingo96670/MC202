#include "cache_array.h"


typedef struct priority_queue* prio_queue;
struct priority_queue {
    int n_elements;
    pos_array* data_array;  // Actual cache data
    int* aux_cache_array;   // Stores whether a number is in the cache or not
    int* cache_heap_pos_array;   // Stores the position in the heap of a value in the cache; if not present, assigns DUMMY_POS (default: -1)
};


// Function to swap two integers by reference
void swap_int(int* a, int* b);

// Function to swap two pos_array structs by reference
void swap_pos_array(pos_array* a, pos_array* b);

// Function to initialize the cache as a priority queue
// Returns the initialized struct
prio_queue initialize_cache(int cache_size, int n_accesses, int n_distinct);

// Function to send a value up the heap
void up_heap(prio_queue prio_q, int heap_pos);

// Function to send a value down the heap
void down_heap(prio_queue prio_q, int heap_pos);

// Function to increase the priority value of a certain heap position
void increase_removal_priority(prio_queue cache, int current_num);

// Removes the value with max key from the cache
//Alters the cache directly
void pop_max(prio_queue cache);