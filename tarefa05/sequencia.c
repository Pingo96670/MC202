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

node insert_nucleotide(node DNA_start, char *nucleotide, int pos) {
    int i;
    node new, sequence;

    sequence=DNA_start;

    for (i=0; i<pos; i++) {
        sequence=sequence->next;
    }

    new=malloc(sizeof(struct node_type));
    new->nucleotide=malloc(sizeof(char));

    new->nucleotide=nucleotide;

    new->next=sequence;

    if (sequence!=NULL) {
        new->previous=sequence->previous;
    } else {
        new->previous=NULL;
    }

    if (pos==0) {
        return new;
    }

    return DNA_start;
}

node remove_nucleotide(node DNA_start, int pos) {
    int i;
    node sequence;

    sequence=DNA_start;

    for (i=0; i<pos; i++) {
        sequence=sequence->next;
    }

    if (pos!=0) {
        sequence->previous->next=sequence->next;
    } else {
        DNA_start=sequence->next;
    }

    if (sequence->next!=NULL) {
        sequence->next->previous=sequence->previous;
    }

    free(sequence);
    
    return DNA_start;
}

void reverse_prefix();

void reverse_suffix();

void transpose_sequence();

void print_sequence();

void free_sequence();


int main() {
    int exit=0, position, length, start, end;
    char command[MAX_COMMAND_LENGTH], *nucleotide;
    node DNA_sequence_start=NULL;
    
    while (!exit) {
        scanf("%s", command);

        if (strcmp(command, "inserir")==0) {
            scanf("%s %d", nucleotide, &position);

            insert_nucleotide(DNA_sequence_start, nucleotide, position);

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