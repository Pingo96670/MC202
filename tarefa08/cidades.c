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
    node parent;
    enum node_category category;
    union {
        struct internal_node {node north_west; node north_east; node south_west; node south_east;};
        struct occupied_leaf {char city_name[MAX_CITY_LEN]; coords coord;};
    };
};


node initialize_node(node node, int centre_x, int centre_y) {
    node=malloc(sizeof(struct node_type));
    node->category=free_leaf;
    node->centre.x=centre_x;
    node->centre.y=centre_y;

    return node;
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


node insert_city(node root, char city_name[MAX_CITY_LEN], int x, int y, coords centre) {
    char temp_name[MAX_CITY_LEN];
    coords temp_coords;
    node temp_node=root;

    switch (temp_node->category) {
        case internal_node:
            if (x<=temp_node->centre.x) {
                centre.x/=2;
                if (y<=temp_node->centre.y) {
                    centre.y/=2;
                    temp_node=insert_city(temp_node->south_west, city_name, x, y, centre);
                } else {
                    centre.y+=centre.y/2;
                    temp_node=insert_city(temp_node->north_west, city_name, x, y, centre);
                }
            } else {
                centre.x+=centre.x/2;
                if (y<=temp_node->centre.y) {
                    centre.y/=2;
                    temp_node=insert_city(temp_node->south_east, city_name, x, y, centre);
                } else {
                    centre.y+=centre.y/2;
                    temp_node=insert_city(temp_node->north_east, city_name, x, y, centre);
                }
            }

            break;

        case free_leaf:
            temp_node->category=occupied_leaf;
            strcpy(temp_node->city_name, city_name);
            break;

        case occupied_leaf:
            strcpy(temp_name, temp_node->city_name);
            temp_coords=temp_node->coord;
            temp_node->category=internal_node;

            root->north_west=initialize_node(root->north_west, centre.x/2, centre.y+centre.y/2);
            root->north_east=initialize_node(root->north_east, centre.x+centre.x/2, centre.y+centre.y/2);
            root->south_west=initialize_node(root->south_west, centre.x/2, centre.y/2);
            root->south_east=initialize_node(root->south_east, centre.x+centre.x/2, centre.y/2);

            insert_city(temp_node, temp_name, temp_coords.x, temp_coords.y, temp_node->centre);
            insert_city(temp_node, city_name, x, y, temp_node->centre);

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

    tree=initialize_node(tree, dimensions/2, dimensions/2);

    while(!end_program) {
        scanf(" %c", &command);

        switch (command) {
            case 'i':
                scanf("%d %d %s", &coord_x, &coord_y, city_name);

                insert_city(tree, city_name, coord_x, coord_y, tree->centre);

                break;

            case 'b':
                scanf("%d %d", &coord_x, &coord_y);

                printf(search_in_point(tree, coord_x, coord_y)->city_name);

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