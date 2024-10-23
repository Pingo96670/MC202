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

