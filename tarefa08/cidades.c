#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#define MAX_CITY_LEN 15


typedef struct coordinates {
    int x;
    int y;
} coords;

typedef struct float_coordinates {
    float x;
    float y;
} float_coords;


enum node_category {internal_node, free_leaf, occupied_leaf};

// Node struct for quaternary tree
typedef struct node_type *node;
struct node_type {
    float_coords centre;
    node parent;
    enum node_category category;
    union {
        struct {node north_west; node north_east; node south_west; node south_east;};
        struct {char city_name[MAX_CITY_LEN]; coords city_coords;};
    };
};


float distance(int a_x, int a_y, int b_x, int b_y) {
    float temp=sqrt(pow(a_x-b_x, 2)+pow(a_y-b_y, 2));

    return temp;
}

node initialize_node(node node, float centre_x, float centre_y) {
    node=malloc(sizeof(struct node_type));
    node->category=free_leaf;
    node->centre.x=centre_x;
    node->centre.y=centre_y;

    return node;
}

// Recursive function to free a quaternary tree in postorder
void free_tree(node root) {
    if (root->category==internal_node) {
        free_tree(root->north_west);
        free_tree(root->north_east);
        free_tree(root->south_west);
        free_tree(root->south_east);
    }

    free(root);
}


node insert_city(node root, char city_name[MAX_CITY_LEN], int x, int y, float_coords centre) {
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
            temp_node->city_coords.x=x;
            temp_node->city_coords.y=y;
            break;

        case occupied_leaf:
            strcpy(temp_name, temp_node->city_name);
            temp_coords=temp_node->city_coords;
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

    return root;
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

void search_in_region(node node, int circle_x, int circle_y, int radius) {
    switch (node->category) {
    case internal_node:
        if (circle_x+radius>node->centre.x) {
            if (circle_y+radius>node->centre.y) {
                search_in_region(node->north_east, circle_x, circle_y, radius);
            }

            if (circle_y-radius<node->centre.y) {
                search_in_region(node->south_east, circle_x, circle_y, radius);
            }
        }

        if (circle_x-radius<node->centre.x) {
            if (circle_y+radius>node->centre.y) {
                search_in_region(node->north_west, circle_x, circle_y, radius);
            }

            if (circle_y-radius<node->centre.y) {
                search_in_region(node->south_west, circle_x, circle_y, radius);
            }
        }
        break;

    case free_leaf:
        break;

    case occupied_leaf:
        if (distance(node->city_coords.x, node->city_coords.y, circle_x, circle_y)<=radius) {
            printf(" %s", node->city_name);
        }
    
    default:
        break;
    }
}

void remove_from_point() {

}

void print_from_point() {

}


int main() {
    int dimensions, end_program=0, coord_x, coord_y, radius;
    char command, city_name[MAX_CITY_LEN];
    node tree=NULL, found_point;

    scanf("%d", &dimensions);

    tree=initialize_node(tree, (dimensions+1)/2, (dimensions+1)/2);

    while(!end_program) {
        scanf(" %c", &command);

        switch (command) {
            case 'i':
                scanf("%d %d %s", &coord_x, &coord_y, city_name);

                insert_city(tree, city_name, coord_x, coord_y, tree->centre);

                printf("Cidade %s inserida no ponto (%d,%d).\n", city_name, coord_x, coord_y);

                break;

            case 'b':
                scanf("%d %d", &coord_x, &coord_y);

                found_point=search_in_point(tree, coord_x, coord_y);

                if (found_point->category==occupied_leaf && (found_point->city_coords.x=coord_x && found_point->city_coords.y==coord_y)) {
                    printf("Cidade %s encontrada no ponto (%d,%d).\n", found_point->city_name, coord_x, coord_y);
                } else {
                    printf("Nenhuma cidade encontrada no ponto (%d,%d).\n", coord_x, coord_y);
                }

                break;

            case 'o':
                scanf("%d %d %d", &coord_x, &coord_y, &radius);

                printf("Cidades a distancia %d de (%d,%d):", radius, coord_x, coord_y);
                search_in_region(tree, coord_x, coord_y, radius);
                printf("\n");

                break;

            case 'r':
                //
                break;

            case 'p':
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