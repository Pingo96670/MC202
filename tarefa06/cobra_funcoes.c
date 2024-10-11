#include <stdio.h>
#include <stdlib.h>
#include "cobra_funcoes.h"


// Função para a operação módulo
// Retorna a mod b
int mod(int a, int b) {
    if (a>=0) {
        return a%b;
    }

    return b+a%b;
}


// Função para criar uma matriz i×j, atribuindo o caractere "_" (ASCII 95) a todas as células
// Retorna uma matriz i×j de char '_'
char **create_matrix(int i, int j) {
    int k, l;
    char **matrix;

    matrix=malloc(i*sizeof(char*));

    for (k=0; k<i; k++) {
        matrix[k]=malloc(j*sizeof(char));

        for (l=0; l<j; l++) {
            matrix[k][l]='_';
        }
    }

    return matrix;
}


// Função para criar um nó relacionado à cabeça da cobra na posição (head_x, head_y)
// Retorna o nó head
node create_head(int head_x, int head_y) {
    node head;

    head=malloc(sizeof(struct node_type));

    head->next=head;
    head->previous=head;

    head->position.x=head_x;
    head->position.y=head_y;

    head->is_head=1;

    return head;
}


// Função para criar a fruta na posição (head_x, head_y)
// Retorna a pos fruit
pos create_fruit(int fruit_x, int fruit_y) {
    pos fruit;

    fruit.x=fruit_x;
    fruit.y=fruit_y;

    return fruit;    
}


// Função utilizada ao comer uma fruta
// Cria um novo nó entre a cabeça e o nó seguinte
void eat_fruit(node head, int move_x, int move_y, board board) {
    node new;

    new=malloc(sizeof(struct node_type));

    new->is_head=0;
    
    new->position=head->position;
  
    new->previous=head;
    new->next=head->next;
    
    head->next->previous=new;
    head->next=new;
    
    head->position.x=abs(mod(head->position.x+move_x, board.size_x));
    head->position.y=abs(mod(head->position.y+move_y, board.size_y));
}


// Função para mover a cobra e checar se come uma fruta
// O "movimento" consiste em manipular o nó relacionado à cauda da cobra para ser o nó após a cabeça (ocupando a posição que era a cabeça antes do movimento)
void move(node head, int move_x, int move_y, pos fruit, int *n_eaten, board board) {
    node temp_node=head->previous;

    // Atualização do tabuleiro
    if (!(abs(mod(head->position.x+move_x, board.size_x))==fruit.x && abs(mod(head->position.y+move_y,board.size_y))==fruit.y)) {
        
    }

    // Checagem de colisão com a fruta
    if (abs(mod(head->position.x+move_x, board.size_x))==fruit.x && abs(mod(head->position.y+move_y, board.size_y))==fruit.y) {
        *n_eaten+=1;
        board.data[abs(mod(head->position.y+move_y, board.size_y))][abs(mod(head->position.x+move_x, board.size_x))]='#';
        eat_fruit(head, move_x, move_y, board);

    // Movimento da cobra
    } else {
        board.data[head->previous->position.y][head->previous->position.x]='_';
        board.data[abs(mod(head->position.y+move_y, board.size_y))][abs(mod(head->position.x+move_x, board.size_x))]='#';

        head->previous->position=head->position;

        head->position.x=abs(mod(head->position.x+move_x, board.size_x));
        head->position.y=abs(mod(head->position.y+move_y, board.size_y));

        head->previous->previous->next=head;
        head->previous=head->previous->previous;

        temp_node->previous=head;
        temp_node->next=head->next;

        head->next->previous=temp_node;
        head->next=temp_node;
        
    }
}


// Função para checar se a cobra colide com seu corpo
// Checa se a célula para qual a cobra irá se mover contém uma parte de seu corpo (#)
// Retorna 0 ou 1 para falso ou verdadeiro, respectivamente
int self_collision_check(node head, int move_x, int move_y, board board) {
    if (board.data[abs(mod(head->position.y+move_y, board.size_y))][abs(mod(head->position.x+move_x, board.size_x))]=='#') {
        return 1;
    }

    return 0;
}


// Função para imprimir o tabuleiro
void print_board(board board) {
    int i, j;

    for (i=0; i<board.size_y; i++) {
        for (j=0; j<board.size_x; j++) {
            printf("%c ", board.data[i][j]);
        }

        printf("\n");
    }
}


// Função para liberar a memória alocada à cobra e ao tabuleiro
void free_game(node head, board board) {
    int i;
    node current_node, next_node;

    current_node=head->next;
    next_node=head->next;

    while (!current_node->is_head) {
        next_node=next_node->next;
        free(current_node);
        current_node=next_node;
    }

    free(head);

    for (i=0; i<board.size_y; i++) {
        free(board.data[i]);
    }

    free(board.data);
}