#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "otimizar_funcoes.h"
#define MAX_STR_LEN 4096


int main() {
    int reading_pos=0;
    node tree;
    char input[MAX_STR_LEN];

    scanf("%s", input);

    tree=read_expression(input, &reading_pos, 0);
    
    printf("%s\n", input);
    de_morgan(tree);
    print_tree(tree);
    printf("\n");
    simplify_expression(tree);
    print_tree(tree);

    free_tree(tree);

    return 0;
}