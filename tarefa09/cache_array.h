// Position array struct
// Stores a value's insertion positions, as well as the current index
typedef struct array* pos_array;
struct array {
    int* positions;
    int n_elements;
    int size;
    int current_index;
    int value;
};


// Function to initialize a pos_array struct with starting values
// Returns the initialized array
pos_array initialize_array(int len, int n_accesses, int n);

// Function to insert a value to array->positions
// Reallocates memory if needed
void insert_pos_in_array(pos_array array, int n);

// Debloats an array's allocated memory
void debloat_array(pos_array* aux_pos_array, int n_distinct);

// Frees up memory allocated to aux_pos_array
void free_aux_pos_array(pos_array* aux_pos_array, int n_distinct);