#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct de um nó para a árvore
typedef struct node_type *node;
struct node_type {
    char data;
    //node parent;
    node left;
    node right;
    int is_negative;
};


node read_expression(char expression[], int *reading_pos, int is_negative) {
    char current;
    node parent_temp, left_temp, right_temp, current_node_temp;

    current=expression[*reading_pos];

    if (current=='!') {
        is_negative==1;
        *reading_pos+=1;
        current=expression[*reading_pos];
    }

    if (current=='(') {
        *reading_pos+=1;
        left_temp=read_expression(expression, reading_pos, is_negative);
        *reading_pos+=1;
        parent_temp=read_expression(expression, reading_pos, is_negative);
        *reading_pos+=1;
        right_temp=read_expression(expression, reading_pos, is_negative);

        parent_temp->left=left_temp;
        parent_temp->right=right_temp;

        // Pula o caractere ")"
        *reading_pos+=1;

        return parent_temp;
    }

    if (current!='(' && current!=')') {
        current_node_temp=malloc(sizeof(struct node_type));

        current_node_temp->data=current;
        current_node_temp->left=NULL;
        current_node_temp->right=NULL;
        current_node_temp->is_negative=is_negative;
        return current_node_temp;
    }
}

void print_tree(node root) {
    if (root!=NULL) {
        print_tree(root->left);
        printf("%c", root->data);
        print_tree(root->right);
    }
}


int main() {
    int reading_pos=0;
    node tree;
    char _;

    tree=read_expression("(a|b)", &reading_pos, 0);
    
    print_tree(tree);

    return 0;
}