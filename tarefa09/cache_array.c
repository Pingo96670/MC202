#include <stdlib.h>
#include "cache_array.h"


// Function to initialize a pos_array struct with starting values
// Returns the initialized array
pos_array initialize_array(int len, int n_accesses, int n) {
    pos_array array;

    array=malloc(sizeof(pos_array)*2);
    array->positions=malloc(len*sizeof(int));

    array->positions[0]=n_accesses;
    array->n_elements=0;
    array->size=len;
    array->current_index=0;
    array->value=n;

    return array;
}

// Function to insert a value to array->positions
// Reallocates memory if needed
void insert_pos_in_array(pos_array array, int n) {
    if (array->n_elements==array->size) {
        array->positions=realloc(array->positions, 2*(array->size)*sizeof(int));
        array->size*=2;
    }

    array->positions[array->n_elements]=n;
    array->n_elements++;
}