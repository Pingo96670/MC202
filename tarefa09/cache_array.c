#include <stdlib.h>
#include "cache_array.h"
#define INITIAL_ARRAY_SIZE 4

pos_array initialize_array() {
    pos_array array;

    array=malloc(sizeof(pos_array));
    array->positions=malloc(INITIAL_ARRAY_SIZE*sizeof(int));
    array->n_elements=0;
    array->size=INITIAL_ARRAY_SIZE;
}

void free_array(pos_array array);

void insert_array(pos_array array, int n);