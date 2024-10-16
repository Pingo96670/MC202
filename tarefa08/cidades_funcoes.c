#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "cidades_funcoes.h"
#define MAX_CITY_LEN 15

// Function to calculate distance between two points A and B using the Pythagorean Theorem
// Returns a float
float distance(int a_x, int a_y, int b_x, int b_y) {
    float temp=sqrt(pow(a_x-b_x, 2)+pow(a_y-b_y, 2));

    return temp;
}

// Function to allocate memory to and initialize a free leaf node with given centre coordinates
// Returns the initialized node
node initialize_node(node node, float centre_x, float centre_y) {
    node=malloc(sizeof(struct node_type));
    node->category=free_leaf;
    node->centre.x=centre_x;
    node->centre.y=centre_y;

    return node;
}

// Recursive function to free a quaternary tree
void free_tree(node root) {
    if (root->category==internal_node) {
        free_tree(root->north_west);
        free_tree(root->north_east);
        free_tree(root->south_west);
        free_tree(root->south_east);
    }

    free(root);
}

// Recursive function to insert a new city with given (x,y) coordinates
// Alters the tree directly
void insert_city(node root, char city_name[MAX_CITY_LEN], int x, int y, float_coords centre, node parent_node) {
    float centre_refactor;
    char temp_name[MAX_CITY_LEN];
    coords temp_coords;
    node temp_node=root;

    // Finds the orthogonal distance between a quadrant's centre and its subquadrants' centres
    if (parent_node==NULL) {
        centre_refactor=centre.x/2.0;
    } else {
        centre_refactor=abs(centre.x-parent_node->centre.x)/2.0;
        if (centre_refactor<abs(centre.y-parent_node->centre.y)/2.0) {
            centre_refactor=abs(centre.y-parent_node->centre.y)/2.0;
        }
    }

    switch (temp_node->category) {
        // If internal node:
        // Finds the correct quadrant and corrects the new centre coordinates, then recursively runs over the suitable quadrant
        case internal_node:
            if (x<=temp_node->centre.x) {
                centre.x-=centre_refactor;
                if (y<=temp_node->centre.y) {
                    centre.y-=centre_refactor;
                    insert_city(temp_node->south_west, city_name, x, y, centre, temp_node);
                } else {
                    centre.y+=centre_refactor;
                    insert_city(temp_node->north_west, city_name, x, y, centre, temp_node);
                }
            } else {
                centre.x+=centre_refactor;
                if (y<=temp_node->centre.y) {
                    centre.y-=centre_refactor;
                    insert_city(temp_node->south_east, city_name, x, y, centre, temp_node);
                } else {
                    centre.y+=centre_refactor;
                    insert_city(temp_node->north_east, city_name, x, y, centre, temp_node);
                }
            }

            break;

        // If free leaf:
        // Simply alters data of the node
        // Base case
        case free_leaf:
            temp_node->category=occupied_leaf;
            strcpy(temp_node->city_name, city_name);
            temp_node->city_coords.x=x;
            temp_node->city_coords.y=y;
            temp_node->parent=parent_node;

            break;

        // If occupied leaf:
        // Stores the leaf's data in auxiliary variables
        // Changes leaf to internal node and initializes subquadrants
        // Calls the insert_city function for the original leaf's data, as well as the original insert command target
            // This only runs over the newly initialized nodes
        case occupied_leaf:
            strcpy(temp_name, temp_node->city_name);
            temp_coords=temp_node->city_coords;
            temp_node->category=internal_node;

            root->north_west=initialize_node(root->north_west, centre.x-centre_refactor, centre.y+centre_refactor);
            root->north_east=initialize_node(root->north_east, centre.x+centre_refactor, centre.y+centre_refactor);
            root->south_west=initialize_node(root->south_west, centre.x-centre_refactor, centre.y-centre_refactor);
            root->south_east=initialize_node(root->south_east, centre.x+centre_refactor, centre.y-centre_refactor);

            insert_city(temp_node, temp_name, temp_coords.x, temp_coords.y, temp_node->centre, temp_node->parent);
            insert_city(temp_node, city_name, x, y, temp_node->centre, temp_node->parent);

            break;
        
        // If no matching cases:
        // Raises error
        // Shouldn't occur
        default:
            assert(0);
    }
}

// Recursive function to search for a leaf in given (x,y) coordinates
// Returns the found node
node search_for_point(node node, int search_x, int search_y) {
    switch (node->category) {
        // If internal node:
        // Finds the correct quadrant, then recursively searches over it
        case internal_node:
            if (search_x<=node->centre.x) {
                if (search_y<=node->centre.y) {
                    node=search_for_point(node->south_west, search_x, search_y);
                } else {
                    node=search_for_point(node->north_west, search_x, search_y);
                }
            } else {
                if (search_y<=node->centre.y) {
                    node=search_for_point(node->south_east, search_x, search_y);
                } else {
                    node=search_for_point(node->north_east, search_x, search_y);
                }
            }

            break;
        
        // If free leaf:
        // Breaks, then returns the found node
        case free_leaf:
            break;

        // If occupied leaf:
        // Breaks, then returns the found node
        case occupied_leaf:
            break;
        
        // If no matching cases:
        // Raises error
        // Shouldn't occur
        default:
            assert(0);
    }

    return node;
}

// Recursive function to print the names of all cities inside a given radius from a point
void search_in_region(node node, int circle_x, int circle_y, int radius) {
    switch (node->category) {
        // If internal node:
        // Finds the correct quadrant, then recursively searches over it
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

        // If free_leaf:
        // Breaks and does nothing
        case free_leaf:
            break;

        // If occupied_leaf:
        // Checks if the city's coordinates fall within the circle's radius
            // Prints its name if True
            // Does nothing otherwise
        case occupied_leaf:
            if (distance(node->city_coords.x, node->city_coords.y, circle_x, circle_y)<=radius) {
                printf(" %s", node->city_name);
            }

            break;
        
        // If no matching cases:
        // Raises error
        // Shouldn't occur
        default:
            assert(0);
    }
}

// Function to check if a node can be collapsed
    // Condition: 1 occupied leaf and 3 free leaves
// Used in remove_from_point
// Returns a value of 0 or 1 as boolean
int branch_collapse_check(node node) {
    int occupied_leaf_count=0, free_leaf_count=0;

    if (node->north_west->category==occupied_leaf) {
        occupied_leaf_count++;
    } else if (node->north_west->category==free_leaf) {
        free_leaf_count++;
    }

    if (node->north_east->category==occupied_leaf) {
        occupied_leaf_count++;
    } else if (node->north_east->category==free_leaf) {
        free_leaf_count++;
    }

    if (node->south_west->category==occupied_leaf) {
        occupied_leaf_count++;
    } else if (node->south_west->category==free_leaf) {
        free_leaf_count++;
    }

    if (node->south_east->category==occupied_leaf) {
        occupied_leaf_count++;
    } else if (node->south_east->category==free_leaf) {
        free_leaf_count++;
    }

    return (occupied_leaf_count==1 && free_leaf_count==3);
}

// Recursive function to collapse a branch if possible
// Moves the only occupied leaf up the tree until collapsing is not possible anymore
// Alters the tree directly
void collapse_branch(node node) {
    char temp_name[MAX_CITY_LEN];
    struct node_type *only_occupied_node;
    coords temp_coords;

    node->category=occupied_leaf;

    // Finds the only occupied leaf
    if (node->north_west->category==occupied_leaf) {
        only_occupied_node=node->north_west;
    } else if (node->north_east->category==occupied_leaf) {
        only_occupied_node=node->north_east;
    } else if (node->south_west->category==occupied_leaf) {
        only_occupied_node=node->south_west;
    } else {
        only_occupied_node=node->south_east;
    }

    // Temporary storage to auxiliary variables
    strcpy(temp_name, only_occupied_node->city_name);
    temp_coords=only_occupied_node->city_coords;

    // Freeing subquadrants
    free(node->north_west);
    free(node->north_east);
    free(node->south_west);
    free(node->south_east);

    // Setting the data of the new occupied leaf
    strcpy(node->city_name, temp_name);
    node->city_coords=temp_coords;

    // Runs recursively if possible
    if (node->parent!=NULL && branch_collapse_check(node->parent)) {
        collapse_branch(node->parent);
    }
}


// Function to remove a city from the given (x,y) coordinates
// Simply changes an occupied leaf's category to free leaf
// Collapses the branch if possible
// Alters the tree directly
void remove_from_point(node node_to_remove, int x, int y) {
    node_to_remove->category=free_leaf;

    if (node_to_remove->parent!=NULL && branch_collapse_check(node_to_remove->parent)) {
        collapse_branch(node_to_remove->parent);
    }
}