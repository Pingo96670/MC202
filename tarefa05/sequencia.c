#include <stdio.h>
#define NUCLEOTIDE_LEN 1
#define MAX_COMMAND_LENGTH 20

typedef struct node {
    char nucleotide[NUCLEOTIDE_LEN];
    node *previous;
    node *next;
} node;

void insert_nucleotide();

void remove_nucleotide();

void reverse_prefix();

void reverse_suffix();

void transpose_sequence();

void print_sequence();


int main() {
    int n, exit=0;
    char command[MAX_COMMAND_LENGTH];
    node *DNA_sequence;
    
    while (!exit) {
        scanf("%s", command);

        if (strcmp(command, "inserir")==0) {
            scanf();

            insert_nucleotide();

        } else if (strcmp(command, "remover")==0) {
            scanf();

            remove_nucleotide();

        } else if (strcmp(command, "inverter-prefixo")==0) {
            scanf();

            reverse_prefix();

        } else if (strcmp(command, "inverter-sufixo")==0) {
            scanf();

            reverse_suffix();

        } else if (strcmp(command, "transpor")==0) {
            scanf();

            transpose_sequence();

        } else if (strcmp(command, "imprimir")==0) {
            scanf();

            print_sequence();

        } else if (strcmp(command, "sair")==0) {
            exit=1;

        } else {
            printf("Comando nao reconhecido");
        } 



    }



    return 0;
}