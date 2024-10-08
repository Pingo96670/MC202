#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STR_LEN 1024

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
    int negative_count=0;
    char current;
    node parent_temp, left_temp, right_temp, current_node_temp;

    current=expression[*reading_pos];


    while (current=='!') {
        negative_count++;
        *reading_pos+=1;
        current=expression[*reading_pos];
    }

    if (negative_count!=0) {
        is_negative=negative_count%2;
    }

    if (current=='(') {
        *reading_pos+=1;
        left_temp=read_expression(expression, reading_pos, 0);
        *reading_pos+=1;
        parent_temp=read_expression(expression, reading_pos, is_negative);
        *reading_pos+=1;
        right_temp=read_expression(expression, reading_pos, 0);

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

void invert_negative(int *is_negative) {
    *is_negative=(*is_negative+1)%2;
}

void de_morgan(node root) {
    if (root->is_negative && root->data=='&') {
        root->data='|';
        root->is_negative=0;
        invert_negative(&(root->left->is_negative));
        invert_negative(&(root->right->is_negative));
    } else if (root->is_negative && root->data=='|') {
        root->data='&';
        root->is_negative=0;
        invert_negative(&(root->left->is_negative));
        invert_negative(&(root->right->is_negative));
    }


    if (root->left!=NULL) {
        de_morgan(root->left);
    }

    if (root->right!=NULL) {
        de_morgan(root->right);
    }

}

void print_tree(node root) {
    if (root!=NULL) {
        if(root->is_negative) {
            printf("!");
        }
        if (root->data=='&' || root->data=='|') {
            printf("(");
        }
        print_tree(root->left);
        printf("%c", root->data);
        print_tree(root->right);
        if (root->data=='&' || root->data=='|') {
            printf(")");
        }
    }
}


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

    return 0;
}