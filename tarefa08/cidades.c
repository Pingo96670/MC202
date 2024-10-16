#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "cidades_funcoes.h"
#define MAX_CITY_LEN 15


int main() {
    int dimensions, end_program=0, coord_x, coord_y, radius;
    char command, city_name[MAX_CITY_LEN];
    node tree=NULL, found_point;

    scanf("%d", &dimensions);

    // Initialize main tree
    tree=initialize_node(tree, (dimensions+1)/2, (dimensions+1)/2);
    tree->parent=NULL;

    while(!end_program) {
        scanf(" %c", &command);

        switch (command) {
            // Insert command
            case 'i':
                scanf("%d %d %s", &coord_x, &coord_y, city_name);

                insert_city(tree, city_name, coord_x, coord_y, tree->centre, NULL);

                printf("Cidade %s inserida no ponto (%d,%d).\n", city_name, coord_x, coord_y);

                break;

            // Seach for point command
            // Prints the suitable message based on the leaf type returned
            case 'b':
                scanf("%d %d", &coord_x, &coord_y);

                found_point=search_for_point(tree, coord_x, coord_y);

                if (found_point->category==occupied_leaf && (found_point->city_coords.x==coord_x && found_point->city_coords.y==coord_y)) {
                    printf("Cidade %s encontrada no ponto (%d,%d).\n", found_point->city_name, coord_x, coord_y);
                } else {
                    printf("Nenhuma cidade encontrada no ponto (%d,%d).\n", coord_x, coord_y);
                }

                break;

            // Search in region command
            case 'o':
                scanf("%d %d %d", &coord_x, &coord_y, &radius);

                printf("Cidades a distancia %d de (%d,%d):", radius, coord_x, coord_y);
                search_in_region(tree, coord_x, coord_y, radius);
                printf("\n");

                break;

            // Remove command
            // Searches for the node using the search_for_point function, prints, the runs remove_from_point over the found node
            case 'r':
                scanf("%d %d", &coord_x, &coord_y);

                found_point=search_for_point(tree, coord_x, coord_y);

                printf("Cidade %s removida do ponto (%d,%d).\n", found_point->city_name, coord_x, coord_y);

                remove_from_point(found_point, coord_x, coord_y);

                break;

            // Exit command
            // Frees the tree and ends program
            case 's':
                printf("Sistema encerrado.\n");
                free_tree(tree);
                end_program=1;
                break;
            
            // Unrecognized command
            default:
                printf("Comando não reconhecido\n");
                break;
        }
    }

    return 0;
}