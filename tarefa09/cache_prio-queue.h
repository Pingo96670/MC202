#include "cache_array.h"

typedef struct priority_queue* prio_queue;
typedef struct priority_queue {
    int len;
    int n_elements;
    pos_array* data_array;
};


void swap(int* a, int* b);

prio_queue initialize_priority_queue(int len);

void up_heap(prio_queue prio_q, int k);

void insert_prio_queue(prio_queue prio_q, int n);

void down_heap(prio_queue prio_q, int k);

int extract_max(prio_queue prio_q);

void edit_priority(prio_queue prio_q, int k, int new_value);