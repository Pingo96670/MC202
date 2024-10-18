typedef struct array* pos_array;
struct array {
    int* positions;
    int n_elements;
    int size;
};

pos_array initialize_array(int len);

void free_array(pos_array array);

void insert_array(pos_array array, int n);