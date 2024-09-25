#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUCLEOTIDE_LEN 1
#define MAX_COMMAND_LENGTH 20

typedef struct node_type *node;

struct node_type {
    char *nucleotide;
    node previous;
    node next;
};

node insert_nucleotide(node sequence, char *nucleotide, int pos) {
    node new;

    new=malloc(sizeof(struct node_type));
    new->nucleotide=malloc(sizeof(char));

    new->nucleotide=nucleotide;

    new->next=sequence;

    if (sequence!=NULL) {
        new->previous=sequence->previous;
    } else {
        new->previous=NULL;
    }
};

void remove_nucleotide();

void reverse_prefix();

void reverse_suffix();

void transpose_sequence();

void print_sequence();

void free_sequence();


int main() {
    int exit=0, position, length, start, end;
    char command[MAX_COMMAND_LENGTH], *nucleotide;
    node DNA_sequence=NULL;
    
    while (!exit) {
        scanf("%s", command);

        if (strcmp(command, "inserir")==0) {
            scanf("%s %d", nucleotide, &position);

            insert_nucleotide(DNA_sequence, nucleotide, position);

        } else if (strcmp(command, "remover")==0) {
            scanf("%d", &position);

            remove_nucleotide();

        } else if (strcmp(command, "inverter-prefixo")==0) {
            scanf("%d", &length);

            reverse_prefix();

        } else if (strcmp(command, "inverter-sufixo")==0) {
            scanf("%d", &length);

            reverse_suffix();

        } else if (strcmp(command, "transpor")==0) {
            scanf("%d %d %d", &start, &end, &position);

            transpose_sequence();

        } else if (strcmp(command, "imprimir")==0) {
            print_sequence();

        } else if (strcmp(command, "sair")==0) {
            exit=1;

        } else {
            printf("Comando nao reconhecido");
        } 
    }

    free_sequence();

    return 0;
}