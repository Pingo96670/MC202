#include <stdio.h>
#include <stdlib.h>
#include "cache_prio-queue.h"
#define INITIAL_ARRAY_SIZE 4


// Reads the input and stores them in the array aux_pos_array
void read_input (int* access_list, int n_accesses, pos_array* aux_pos_array, int n_distinct) {
    int i;

    for (i=0; i<n_accesses; i++) {
        scanf("%d", &access_list[i]);

        if (aux_pos_array[access_list[i]]->positions[0]==n_accesses) {
            aux_pos_array[access_list[i]]->positions[0]=i;
            aux_pos_array[access_list[i]]->n_elements++;
        } else {
            insert_pos_in_array(aux_pos_array[access_list[i]], i);
        }
    }

    debloat_array(aux_pos_array, n_distinct);
}

// Function to check if an int n is in the cache
// Returns an integer as boolean
int is_in_cache(prio_queue cache, int n) {
    return cache->aux_cache_array[n];
}

// Function to insert a value to cache, removing the one with lowest priority
// Alters the cache directly
void insert_in_cache(prio_queue cache, int n, pos_array* aux_pos_array) {
    cache->aux_cache_array[n]=1;
    cache->data_array[cache->n_elements]=aux_pos_array[n];
    cache->data_array[cache->n_elements]->current_index++;
    cache->n_elements++;
    cache->cache_heap_pos_array[n]=cache->n_elements-1;
    up_heap(cache, cache->n_elements-1);
}

// Frees up the cache's allocated memory
void free_cache(prio_queue cache, int cache_size) {

    free(cache->aux_cache_array);
    free(cache->cache_heap_pos_array);

    // cache->data_array is freed by free_aux_pos_array

    free(cache->data_array);
    free(cache);
}


// Main function
int main() {
    int cache_size, n_distinct, n_accesses, *access_list, n_insertions=0, current_num, i, free_cache_space=0;
    pos_array* aux_pos_array;   // Stores all pos_array structs, which are then called for insertion in cache
    prio_queue cache;

    scanf("%d %d %d", &cache_size, &n_distinct, &n_accesses);

    // Initializing variables
    access_list=malloc(n_accesses*sizeof(int));
    aux_pos_array=malloc(n_distinct*sizeof(pos_array));
    cache=initialize_cache(cache_size, n_accesses, n_distinct);
    for (i=0; i<n_distinct; i++) {
        aux_pos_array[i]=initialize_array(INITIAL_ARRAY_SIZE, n_accesses, i);
    }

    free_cache_space=cache_size;

    read_input(access_list, n_accesses, aux_pos_array, n_distinct);

    // Cache manipulation
    for (i=0; i<n_accesses; i++) {
        current_num=access_list[i];

        if (!is_in_cache(cache, current_num)) {
            n_insertions++;

            if (free_cache_space>0) {
                insert_in_cache(cache, current_num, aux_pos_array);
                free_cache_space--;
            } else {
                pop_max(cache);
                insert_in_cache(cache, current_num, aux_pos_array);
            }
        } else {
            increase_removal_priority(cache, current_num);
        }   
    }

    // Results
    printf("%d", n_insertions);

    // Freeing memory
    free(access_list);
    free_aux_pos_array(aux_pos_array, n_distinct);
    free_cache(cache, cache_size);

    return 0;
}