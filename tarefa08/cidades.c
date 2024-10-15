#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX_CITY_LEN 15


typedef struct coordinates {
    int x;
    int y;
} coords;

enum node_category {internal_node, free_leaf, occupied_leaf};

// Node struct for quaternary tree
typedef struct node_type *node;
struct node_type {
    coords centre;
    enum node_category category;
    union {
        struct {node north_west; node north_east; node south_west; node south_east;};
        struct {char city_name[MAX_CITY_LEN]; coords coord;};
    };
};


void initialize_node(node node, int size_x, int size_y) {
    node->category=free_leaf;
    node->centre.x=size_x/2;
    node->centre.y=size_y/2;
}

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


void insert_city(node tree, char city_name[MAX_CITY_LEN], int x, int y) {
    switch (tree->category)
    {
    case internal_node:
        /* code */
        break;

    case free_leaf:
        break;

    case occupied_leaf:
        break;
    
    default:
        assert(0);
    } 
}

node search_in_point(node node, int search_x, int search_y) {
    switch (node->category) {
        case internal_node:
            if (search_x<=node->centre.x) {
                if (search_y<=node->centre.y) {
                    node=search_in_point(node->south_west, search_x, search_y);
                } else {
                    node=search_in_point(node->north_west, search_x, search_y);
                }
            } else {
                if (search_y<=node->centre.y) {
                    node=search_in_point(node->south_east, search_x, search_y);
                } else {
                    node=search_in_point(node->north_east, search_x, search_y);
                }
            }

            break;
        
        case free_leaf:
            break;

        case occupied_leaf:
            break;
        
        default:
            assert(0);
    }

    return node;
}

void search_in_region() {

}

void remove_from_point() {

}

void print_from_point() {

}


int main() {
    int dimensions, end_program=0, coord_x, coord_y;
    char command, city_name[MAX_CITY_LEN];
    node tree=NULL;

    scanf("%d", &dimensions);

    initialize_node(tree, dimensions, dimensions);

    while(!end_program) {
        scanf("%c", &command);

        switch (command) {
            case 'i':
                scanf("%d %d %s", &coord_x, &coord_y, city_name);

                insert_city(tree, city_name, coord_x, coord_y);

                break;

            case 'b':
                //
                break;

            case 'o':
                //
                break;

            case 'r':
                //
                break;

            case 'p':
                //
                break;

            case 's':
                printf("Sistema encerrado.");
                free_tree(tree);
                end_program=1;
                break;
            
            default:
                printf("Comando não reconhecido");
                break;
        }
    }

    return 0;
}