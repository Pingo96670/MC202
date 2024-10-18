#include <stdio.h>
#include <stdlib.h>
#include "cache_prio-queue.h"


int main() {
    int cache_size, range, n_accesses, *access_list, i;
    prio_queue prio_q;

    scanf("%d %d %d", &cache_size, &range, &n_accesses);

    access_list=malloc(n_accesses*sizeof(int));

    for (i=0; i<n_accesses; i++) {
        scanf("%d", &access_list[i]);
    }

    free(access_list);
    free(prio_q->data_array[0]->positions);
    free(prio_q->data_array);

    return 0;
}