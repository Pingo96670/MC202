#include <stdlib.h>
#include "cache_array.h"


// Function to initialize a pos_array struct with starting values
// Returns the initialized array
pos_array initialize_array(int len, int n_accesses, int n) {
    pos_array array;

    array=malloc(sizeof(struct array));
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

// Debloats an array's allocated memory
void debloat_array(pos_array* aux_pos_array, int n_distinct) {
    int i;

    for (i=0; i<n_distinct; i++) {
        aux_pos_array[i]->positions=realloc(aux_pos_array[i]->positions, aux_pos_array[i]->n_elements*sizeof(int));
        aux_pos_array[i]->size=aux_pos_array[i]->n_elements;
    }
}