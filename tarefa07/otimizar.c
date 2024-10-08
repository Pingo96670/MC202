#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STR_LEN 4096

// TODO
// Alocação dinâmica para o input
// Comentários mais definidos
// Outras correções apontadas na correção

// Struct de um nó para a árvore
typedef struct node_type *node;
struct node_type {
    char data;
    node left;
    node right;
    int is_negative;
};


// Função recursiva para liberar uma árvore binária em pós-ordem
void free_tree(node root) {
    if (root->left!=NULL) {
        free_tree(root->left);
    }

    if (root->right!=NULL) {
        free_tree(root->right);
    }

    free(root);
}

// Função para ler uma expressão recursivamente e armazená-la como árvore binária
// Retorna a raiz da árvore principal
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

    } else {
        current_node_temp=malloc(sizeof(struct node_type));

        current_node_temp->data=current;
        current_node_temp->left=NULL;
        current_node_temp->right=NULL;
        current_node_temp->is_negative=is_negative;
        return current_node_temp;
    }
}

// Função suporte para inverter o atributo is_negative de um nó
void invert_negative(int *is_negative) {
    *is_negative=(*is_negative+1)%2;
}

// Função para aplicar o Teorema de De Morgan sobre a árvore em pré-ordem
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

// Função para checar se duas expressões são equivalentes
int is_equivalent(node root_expression1, node root_expression2) {
    if (root_expression1->data!='&' && root_expression1->data!='|' && root_expression2->data!='&' && root_expression2->data!='|') {
        return ((root_expression1->data==root_expression2->data) && (root_expression1->is_negative==root_expression2->is_negative));
        
    } else if ((root_expression1->data=='&' && root_expression2->data=='&') || (root_expression1->data=='|' && root_expression2->data=='|')) {
        return ((is_equivalent(root_expression1->left, root_expression2->left) && is_equivalent(root_expression1->right, root_expression2->right)) ||
                (is_equivalent(root_expression1->left, root_expression2->right) && is_equivalent(root_expression1->right, root_expression2->left)));
    } else {
        return 0;
    }
}

// Função para simplificar uma expressão, percorrendo a árvore em pós-ordem
void simplify_expression(node root) {
    node temp_node;

    if (root->left!=NULL) {
        simplify_expression(root->left);
    }

    if (root->right!=NULL) {
        simplify_expression(root->right);
    }

    switch (root->data) {
        case 'T':
            if (root->is_negative) {
                root->data='F';
            }
            break;
        case 'F':
            if (root->is_negative) {
                root->data='T';
            }
            break;
        case '&':
            if (root->left->data=='F' || root->right->data=='F') {
                root->data='F';
                free_tree(root->left);
                free_tree(root->right);
                root->left=root->right=NULL;
            } else if (root->left->data=='T') {
                temp_node=root->right;

                free(root->left);

                root->data=root->right->data;
                root->left=root->right->left;
                root->is_negative=root->right->is_negative;
                root->right=root->right->right;

                free(temp_node);
            } else if (root->right->data=='T' || is_equivalent(root->left, root->right)) {
                temp_node=root->left;

                free_tree(root->right);

                root->data=root->left->data;
                root->right=root->left->right;
                root->is_negative=root->left->is_negative;
                root->left=root->left->left;

                free(temp_node);
            }
            break;
        case '|':
            if ((root->left->data=='T' || root->right->data=='T')) {
                root->data='T';
                free_tree(root->left);
                free_tree(root->right);
                root->left=root->right=NULL;
            } else if (root->left->data=='F') {
                temp_node=root->right;

                free(root->left);

                root->data=root->right->data;
                root->left=root->right->left;
                root->is_negative=root->right->is_negative;
                root->right=root->right->right;

                free(temp_node);
            } else if (root->right->data=='F' || is_equivalent(root->left, root->right)) {
                temp_node=root->left;

                free_tree(root->right);

                root->data=root->left->data;
                root->right=root->left->right;
                root->is_negative=root->left->is_negative;
                root->left=root->left->left;
                
                free(temp_node);
            }
            break;
        default:
            break;
    }
}

// Função para imprimir uma expressão, percorrendo a árvore em in-ordem
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


// Função main
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