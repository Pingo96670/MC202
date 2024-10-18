#include <stdlib.h>
#include "cache_array.h"


pos_array initialize_array(int len) {
    pos_array array;

    array=malloc(sizeof(pos_array));
    array->positions=malloc(len*sizeof(int));

    array->positions[0]=NULL;
    array->n_elements=0;
    array->size=len;
    array->current_index=0;

    return array;
}

void insert_in_array(pos_array array, int n) {
    if (array->n_elements==array->size) {
        array=realloc(array, 2*array->size);
        array->size*=2;
    }

    array->positions[array->n_elements]=n;
    array->n_elements++;
}

void free_array(pos_array array);

