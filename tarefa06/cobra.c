#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_COMMAND_SIZE 10

typedef struct board {
    char **data;
    int size_x;
    int size_y;
} board;

typedef struct pos {
    int x;
    int y;
} pos;

// Struct de um nó para a lista duplamente ligada
typedef struct node_type *node;
struct node_type {
    pos position;
    int is_head;
    node previous;
    node next;
};

char **create_matrix(int i, int j) {
    int k, l;
    char **matrix;

    matrix=malloc(i*sizeof(char*));

    for (k=0; k<i; k++) {
        matrix[k]=malloc(j*sizeof(char));

        for (l=0; l<j; l++) {
            matrix[k][l]=95;
        }
    }

    return matrix;
}


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

pos create_fruit(int fruit_x, int fruit_y) {
    pos fruit;

    fruit.x=fruit_x;
    fruit.y=fruit_y;

    return fruit;    
}

void eat_fruit(node head, int move_x, int move_y) {
    node new, temp;

    new=malloc(sizeof(node));

    new->is_head=0;

    new->position=head->position;  

    head->next->previous=new;
    new->next=head->previous;

    new->previous=head;
    head->next=new;
    
    head->position.x+=move_x;
    head->position.y+=move_y;
}

void move(node head, int move_x, int move_y, pos fruit, int *n_eaten) {
    node temp_node=head->previous;

    if (head->position.x==fruit.x && head->position.y==fruit.y) {
        *n_eaten++;
        eat_fruit(head, move_x, move_y);
    } else {


        head->previous->position=head->position;

        head->position.x+=move_x;
        head->position.y+=move_y;

        if (head->previous!=NULL) {
            head->previous->previous->next=head;
            head->previous=head->previous->previous;

            temp_node->previous=head;
            temp_node->next=head->next;

            head->next->previous=temp_node;
            head->next=temp_node;
        }
    }
}

int self_collision_check(node head) {
    int i;
    node current_node;
    current_node=head->next;

    while (!current_node->is_head) {
        if (head->position.x==current_node->position.x && head->position.y==current_node->position.y) {
            return 1;
        } else {
            current_node=current_node->next;
        }
    }

    return 0;
}





void print_board(board board) {
    int i, j;

    for (i=0; i<board.size_y; i++) {
        for (j=0; j<board.size_x; j++) {
            printf("%c ", board.data[i][j]);
        }

        printf("\n");
    }
}


int main() {
    int i, j, game_end=0, win=0, n_eaten;
    char command[MAX_COMMAND_SIZE];
    pos fruit;
    board board;
    node head;

    // Cria a matriz correspondente ao mapa
    scanf("%s %d %d", command, &i, &j);
    board.data=create_matrix(i, j);
    board.size_x=j;
    board.size_y=i;

    // Cria e posiciona a cobra
    scanf("%s %d %d", command,&i, &j);
    head=create_head(j, i);
    board.data[i][j]=35;

    while (!game_end) {
        scanf("%s", command);

        if (strcmp(command, "FRUTA")==0) {

            scanf("%d %d", &i, &j);

            fruit=create_fruit(j, i);

            board.data[i][j]=42;

        } else if (strcmp(command, "w")==0) {

            if (!(head->position.x==fruit.x && head->position.y==fruit.y)) {
                board.data[head->previous->position.y][head->previous->position.x]=95;
            }
            board.data[head->position.y-1][head->position.x]=35;

            move(head, 0, 1, fruit, &n_eaten);
            game_end=self_collision_check(head);

        } else if (strcmp(command, "a")==0) {

            if (!(head->position.x==fruit.x && head->position.y==fruit.y)) {
                board.data[head->previous->position.y][head->previous->position.x]=95;
            }
            board.data[head->position.y][head->position.x-1]=35;

            move(head, -1, 0, fruit, &n_eaten);
            game_end=self_collision_check(head);

        } else if (strcmp(command, "s")==0) {

            if (!(head->position.x==fruit.x && head->position.y==fruit.y)) {
                board.data[head->previous->position.y][head->previous->position.x]=95;
            }
            board.data[head->position.y+1][head->position.x]=35;

            move(head, 0, -1, fruit, &n_eaten);
            game_end=self_collision_check(head);

        } else if (strcmp(command, "d")==0) {

            if (!(head->position.x==fruit.x && head->position.y==fruit.y)) {
                board.data[head->previous->position.y][head->previous->position.x]=95;
            }
            board.data[head->position.y][head->position.x+1]=35;

            move(head, 1, 0, fruit, &n_eaten);
            game_end=self_collision_check(head);


        } else {
            printf("COMANDO NAO RECONHECIDO");
        }

        print_board(board);

        if (n_eaten==board.size_x*board.size_y-1) {
            win=1;
        }
    }

    if (win) {
        printf("YOU WIN");
    } else {
        printf("YOU LOSE");
    }

    return 0;
}