typedef struct array* pos_array;
struct array {
    int* positions;
    int n_elements;
    int size;
    int current_index;
};

pos_array initialize_array(int len);

void insert_in_array(pos_array array, int n);

void free_array(pos_array array);

