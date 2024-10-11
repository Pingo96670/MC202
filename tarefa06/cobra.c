#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cobra_funcoes.h"
#define MAX_COMMAND_SIZE 10


// Função main
int main() {
    int i, j, win=0, n_eaten=0;
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
    board.data[i][j]='#';    // Coloca o caractere # na posição correta do tabuleiro

    // Loop do jogo
    while (1) {
        scanf("%s", command);

        if (strcmp(command, "FRUTA")==0) {

            scanf("%d %d", &i, &j);

            fruit=create_fruit(j, i);
            board.data[i][j]='*';    // Coloca o caractere * na posição correta do tabuleiro


        } else if (strcmp(command, "w")==0) {
            if (self_collision_check(head, 0, -1, board)) {
                break;
            }

            move(head, 0, -1, fruit, &n_eaten, board);


        } else if (strcmp(command, "a")==0) {
            if (self_collision_check(head, -1, 0, board)) {
                break;
            }

            move(head, -1, 0, fruit, &n_eaten, board);


        } else if (strcmp(command, "s")==0) {
            if (self_collision_check(head, 0, 1, board)) {
                break;
            }

            move(head, 0, 1, fruit, &n_eaten, board);


        } else if (strcmp(command, "d")==0) {
            if (self_collision_check(head, 1, 0, board)) {
                break;
            }

            move(head, 1, 0, fruit, &n_eaten, board);


        } else {
            printf("COMANDO NAO RECONHECIDO");
        }

        // Checa se a quantidade máxima de frutas foi obtida e encerra o jogo
        if (n_eaten==board.size_x*board.size_y-1) {
            print_board(board);
            win=1;
            break;
        }

        print_board(board);

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