#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_COMMAND_SIZE 10
#define HASH 35
#define ASTERISK 42
#define UNDERSCORE 95


// Struct do tabuleiro, contendo dimensões e uma matriz com os caracteres de cada célula
typedef struct board {
    char **data;
    int size_x;
    int size_y;
} board;

// Struct de posição (x, y)
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


// Função para a operação módulo (formato a mod b)
int mod(int a, int b) {
    if (a>=0) {
        return a%b;
    }

    return b+a%b;
}

// Função para criar uma matriz i×j, atribuindo o caractere "_" (ASCII 95) a todas as células
char **create_matrix(int i, int j) {
    int k, l;
    char **matrix;

    matrix=malloc(i*sizeof(char*));

    for (k=0; k<i; k++) {
        matrix[k]=malloc(j*sizeof(char));

        for (l=0; l<j; l++) {
            matrix[k][l]=UNDERSCORE;
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

// Função para criar a fruta na posição (head_x, head_y), que é então retornada como pos
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

    if (abs(mod(head->position.x+move_x, board.size_x))==fruit.x && abs(mod(head->position.y+move_y, board.size_y))==fruit.y) {
        *n_eaten+=1;
        eat_fruit(head, move_x, move_y, board);

    } else {
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
int self_collision_check(node head, int move_x, int move_y, board board) {
    if (board.data[abs(mod(head->position.y+move_y, board.size_y))][abs(mod(head->position.x+move_x, board.size_x))]==HASH) {
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


// Função main
int main() {
    int i, j, game_end=0, win=0, n_eaten=0;
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
    board.data[i][j]=HASH;    // Coloca o caractete # (ASCII 35) na posição correta do tabuleiro

    // Loop do jogo
    while (!game_end) {
        scanf("%s", command);

        if (strcmp(command, "FRUTA")==0) {

            scanf("%d %d", &i, &j);

            fruit=create_fruit(j, i);
            board.data[i][j]=ASTERISK;    // Coloca o caractete * (ASCII 42) na posição correta do tabuleiro


        } else if (strcmp(command, "w")==0) {
            game_end=self_collision_check(head, 0, -1, board);

            if (!(head->position.x==fruit.x && abs(mod(head->position.y-1,board.size_y))==fruit.y)) {
                board.data[head->previous->position.y][head->previous->position.x]=UNDERSCORE;
            }

            board.data[abs(mod(head->position.y-1, board.size_y))][head->position.x]=HASH;
            move(head, 0, -1, fruit, &n_eaten, board);


        } else if (strcmp(command, "a")==0) {
            game_end=self_collision_check(head, -1, 0, board);

            if (!(abs(mod(head->position.x-1, board.size_x))==fruit.x && head->position.y==fruit.y)) {
                board.data[head->previous->position.y][head->previous->position.x]=UNDERSCORE;
            }

            board.data[head->position.y][abs(mod(head->position.x-1, board.size_x))]=HASH;
            move(head, -1, 0, fruit, &n_eaten, board);


        } else if (strcmp(command, "s")==0) {
            game_end=self_collision_check(head, 0, 1, board);

            if (!(head->position.x==fruit.x && (head->position.y+1)%board.size_y==fruit.y)) {
                board.data[head->previous->position.y][head->previous->position.x]=UNDERSCORE;
            }

            board.data[(head->position.y+1)%board.size_y][head->position.x]=HASH;
            move(head, 0, 1, fruit, &n_eaten, board);


        } else if (strcmp(command, "d")==0) {
            game_end=self_collision_check(head, 1, 0, board);

            if (!((head->position.x+1)%board.size_x==fruit.x && head->position.y==fruit.y)) {
                board.data[head->previous->position.y][head->previous->position.x]=UNDERSCORE;
            }

            board.data[head->position.y][(head->position.x+1)%board.size_x]=HASH;
            move(head, 1, 0, fruit, &n_eaten, board);


        } else {
            printf("COMANDO NAO RECONHECIDO");
        }

        if (!game_end) {
            print_board(board);
        }

        // Checa se a quantidade máxima de frutas foi obtida e encerra o jogo
        if (n_eaten==board.size_x*board.size_y-1) {
            game_end=1;
            win=1;
        }

        printf("\n");
    }

    // Fim de jogo
    if (win) {
        printf("YOU WIN");
    } else {
        printf("GAME OVER");
    }

    free_game(head, board);

    return 0;
}