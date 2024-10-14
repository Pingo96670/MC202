#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CITY_LEN 15


// Node struct for quaternary tree
typedef struct node_type *node;
struct node_type {
    char city_name[MAX_CITY_LEN];
    node north_west;
    node north_east;
    node south_west;
    node south_east;
};


// Recursive function to free a quaternary tree in postorder
void free_tree(node root) {
    if (root->north_west!=NULL) {
        free_tree(root->north_west);
    }

    if (root->north_east!=NULL) {
        free_tree(root->north_east);
    }

    if (root->south_west!=NULL) {
        free_tree(root->south_west);
    }

    if (root->south_east!=NULL) {
        free_tree(root->south_east);
    }

    free(root);
}


int main() {


    return 0;
}