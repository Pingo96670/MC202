#include <stdio.h>
#include <stdlib.h>
#include "cache_prio-queue.h"


// Priority tree
    // Highest priority: lowest data_array[n][0] (appears first)
    // If empty, lowest priority

// TODO
    // Correctly insert to tree (instead of organize_priority_queue)

void initialize_cache() {}

int is_in_cache() {}

void insert_in_cache() {}


int main() {
    int *cache, cache_size, range, n_accesses, *access_list, n_insertions=0, current_num, i, *heap_pos;
    prio_queue prio_q;

    scanf("%d %d %d", &cache_size, &range, &n_accesses);

    cache=malloc(cache_size*sizeof(int));
    prio_q=initialize_priority_queue(range);
    access_list=malloc(n_accesses*sizeof(int));
    heap_pos=malloc(range*sizeof(int));

    for (i=0; i<range; i++) {
        heap_pos[i]=i;
    }

    for (i=0; i<n_accesses; i++) {
        scanf("%d", &access_list[i]);
    }

    // Position storage
    for (i=0; i<n_accesses; i++) {
        current_num=access_list[i];

        if (prio_q->data_array[heap_pos[current_num]]->positions[0]==NULL) {
            edit_priority(prio_q, heap_pos[current_num], i);    // Edit prio_q->data_array[heap_pos[current_num]]->positions[0]
            prio_q->data_array[heap_pos[current_num]]->n_elements++; 
        } else {
            insert_in_array(prio_q->data_array[heap_pos[current_num]]->positions, i);  // Does not change priority discriminant (positions[0])
        }
    }


    for (i=0; i<n_accesses; i++) {
        current_num=access_list[i];

        if (!is_in_cache(current_num)) {
            n_insertions++;

            insert_in_cache();
        }

        decrease_priority(prio_q, heap_pos[current_num]);
    }

    printf("%d", n_insertions);

    free(access_list);
    free(prio_q->data_array[0]->positions);
    free(prio_q->data_array);

    return 0;
}