#include <stdio.h>
#include <stdlib.h>
#include "cache_prio-queue.h"
#define NEXT_POS(num) prio_q->data_array[heap_pos_array[num]]->positions[prio_q->data_array[heap_pos_array[num]]->current_index]
#define IS_DONE(num) prio_q->data_array[heap_pos_array[num]]->current_index==prio_q->data_array[heap_pos_array[num]]->n_elements


// NOTES: Applying the priority queue data structure to the queue is probably the correct way, and is in the process of making


// Function to allocate memory to and initialize cache
// Returns the initialized cache as an int array
int* initialize_cache(int cache_size, int n_distinct) {
    int i, *cache;   

    cache=malloc(cache_size*sizeof(int));

    for (i=0; i<cache_size; i++) {
        cache[i]=n_distinct+1;
    }

    return cache;
}

// Function to check if an int n is in the cache
// Returns an integer as boolean
int is_in_cache(int* cache, int cache_size, int n) {
    int i;

    for (i=0; i<cache_size; i++) {
        if (cache[i]==n) {
            return 1;
        }
    }

    return 0;
}

// Function to insert a value to cache, removing the one with lowest priority
// Alters the cache directly
void insert_in_cache(int* cache, int cache_size, int n, int* heap_pos_array, prio_queue prio_q) {
    int least_priority_num, least_priority_num_pos, i;

    least_priority_num=cache[0];
    least_priority_num_pos=0;

    for (i=0; i<cache_size; i++) {
        if (IS_DONE(cache[i])) {
            least_priority_num_pos=i;
            break;
        }
        
        if (NEXT_POS(cache[i])>NEXT_POS(least_priority_num)) {
            least_priority_num=cache[i];
            least_priority_num_pos=i;
        }
    }

    cache[least_priority_num_pos]=n;
}


// Main function
int main() {
    int *cache, cache_size, n_distinct, n_accesses, *access_list, n_insertions=0, current_num, i, *heap_pos, last_free_cache_pos=0;
    prio_queue prio_q;

    scanf("%d %d %d", &cache_size, &n_distinct, &n_accesses);

    // Initializing variables
    cache=initialize_cache(cache_size, n_distinct);
    prio_q=initialize_priority_queue(n_distinct, n_accesses);
    access_list=malloc(n_accesses*sizeof(int));
    heap_pos=malloc(n_distinct*sizeof(int));

    for (i=0; i<n_distinct; i++) {
        heap_pos[i]=i;
    }

    // Storing the accesses
    for (i=0; i<n_accesses; i++) {
        scanf("%d", &access_list[i]);
    }

    // Position storage
    for (i=0; i<n_accesses; i++) {
        current_num=access_list[i];

        if (prio_q->data_array[heap_pos[current_num]]->positions[0]==n_accesses) {

            prio_q->data_array[heap_pos[current_num]]->positions[0]=i;
            up_heap(prio_q, heap_pos[current_num], current_num, heap_pos, n_distinct);
            prio_q->data_array[heap_pos[current_num]]->n_elements++; 

        } else {
            insert_pos_in_array(prio_q->data_array[heap_pos[current_num]], i);  // Does not change priority discriminant (positions[0])
        }
    }

    // Cache manipulation
    for (i=0; i<n_accesses; i++) {
        current_num=access_list[i];
        
        if (!is_in_cache(cache, cache_size, current_num)) {
            n_insertions++;

            if (last_free_cache_pos<cache_size) {
                cache[last_free_cache_pos]=current_num;
                last_free_cache_pos++;
            } else {
                insert_in_cache(cache, cache_size, current_num, heap_pos, prio_q);
            }
        }

        decrease_priority(prio_q, heap_pos[current_num], heap_pos);
    }

    // Final results
    printf("%d", n_insertions);


    // Freeing memory
    free(cache);
    free(access_list);
    free(heap_pos);

    for (i=0; i<n_distinct; i++) {
        free(prio_q->data_array[i]->positions);
    }

    free(prio_q->data_array);
    free(prio_q);

    return 0;
}