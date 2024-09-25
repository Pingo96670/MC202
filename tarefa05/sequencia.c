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

    printf("%s inserido em %d", nucleotide, pos);

    return DNA_start;
}

node remove_nucleotide(node DNA_start, int pos) {
    int i;
    node sequence;
    char nucleotide[1];

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

    printf("%s removido de %d", sequence->nucleotide, pos);

    free(sequence->nucleotide);
    free(sequence);

    return DNA_start;
}

void reverse_prefix(node DNA_start, int len) {
    int i;
    char *temp;
    node start, end;

    start=DNA_start;
    end=DNA_start;
    
    for (i=0; i<len-1; i++) {
        end=end->next;
    }
    
    temp=start->nucleotide;
    start->nucleotide=end->nucleotide;
    end->nucleotide=temp;

    if (len-2>1) {
        reverse_prefix(start->next, len-2);
    }

    free(temp);
}

void reverse_suffix(node DNA_start, int len) {
    int i;
    char *temp;
    node start, end;

    end=DNA_start;
    
    for (; end->next!=NULL; end=end->next);

    start=end;

    for (i=0; i<len-1; i++) {
        start=start->previous;
    }
    
    temp=start->nucleotide;
    start->nucleotide=end->nucleotide;
    end->nucleotide=temp;

    if (len-2>1) {
        reverse_prefix(start->next, len-2);
    }

    free(temp);
}

node transpose_sequence(node DNA_start, int start, int end, int offset) {
    int i;
    node start_node, end_node, temp_node;

    start_node=DNA_start;
    end_node=DNA_start;

    for (i=0; i<start; i++) {
        start_node=start_node->next;
    }

    for (i=0; i<end; i++) {
        end_node=end_node->next;
    }

    if (start=0) {
        DNA_start=end_node->next;
    }

    if (offset>0) {
        temp_node=end_node->next;

        start_node->previous->next=end_node->next;
        end_node->next->previous=start_node->previous;

        start_node->previous=end_node->next;
        end_node->next=start_node;

        temp_node->next->previous=end_node;
        end_node->next=temp_node->next;

        free(temp_node);

        transpose_sequence(DNA_start, start+1, end+1, offset-1);

    } else if (offset<0) {
        temp_node=start_node->previous;

        end_node->next->previous=start_node->previous;
        start_node->previous->next=end_node->next;

        end_node->next=start_node->previous;
        start_node->previous=end_node;

        temp_node->previous->next=start_node;
        start_node->previous=temp_node->previous;

        free(temp_node);

        transpose_sequence(DNA_start, start-1, end-1, offset+1);
    }

    return DNA_start;
}


void print_sequence(node sequence_start, int is_subsequence, int len) {
    int i;
    node current;

    current=sequence_start;

    if (!is_subsequence) {
        while (sequence_start->next!=NULL) {
            printf("%s ", current->nucleotide);
            current=current->next;
        }
    } else {
        for (i=0; i<len; i++) {
            printf("%s ", current->nucleotide);
            current=current->next;
        }
    }
}

void free_sequence(node DNA_sequence) {
    node temp_next, temp_current;

    temp_current=DNA_sequence;

    while (temp_current!=NULL) {
        temp_next=temp_current->next;
        free(temp_current->nucleotide);
        free(temp_current);
        temp_current=temp_next;
    }

    free(temp_current);
    free(temp_next);
}


int main() {
    int exit=0, position, length, start, end, offset;
    char command[MAX_COMMAND_LENGTH], *nucleotide;
    node DNA_sequence_start=NULL;
    
    while (!exit) {
        scanf("%s", command);

        if (strcmp(command, "inserir")==0) {
            scanf("%s %d", nucleotide, &position);

            insert_nucleotide(DNA_sequence_start, nucleotide, position);

        } else if (strcmp(command, "remover")==0) {
            scanf("%d", &position);

            remove_nucleotide(DNA_sequence_start, position);

        } else if (strcmp(command, "inverter-prefixo")==0) {
            scanf("%d", &length);

            reverse_prefix(DNA_sequence_start, length);

        } else if (strcmp(command, "inverter-sufixo")==0) {
            scanf("%d", &length);

            reverse_suffix(DNA_sequence_start, length);

        } else if (strcmp(command, "transpor")==0) {
            scanf("%d %d %d", &start, &end, &offset);

            transpose_sequence(DNA_sequence_start, start, end, offset);

        } else if (strcmp(command, "imprimir")==0) {
            print_sequence(DNA_sequence_start, 0, 0);

        } else if (strcmp(command, "sair")==0) {
            exit=1;

        } else {
            printf("Comando nao reconhecido");
        } 
    }

    free_sequence(DNA_sequence_start);

    free(DNA_sequence_start);

    return 0;
}