#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUCLEOTIDE_LEN 1
#define MAX_COMMAND_LENGTH 20

typedef struct node_type *node;

struct node_type {
    char nucleotide;
    node previous;
    node next;
};

node insert_nucleotide(node DNA_start, char nucleotide, int pos) {
    int i;
    node new, previous_node;
    
    new=malloc(sizeof(struct node_type));

    new->nucleotide=nucleotide;

    if (pos==0) {
        new->previous=NULL;
        new->next=DNA_start;

        if (DNA_start!=NULL) {
            DNA_start->previous=new;
        }

        printf("%c inserido em %d", nucleotide, pos);

        return new;

    } else {
        previous_node=DNA_start;
        for (i=0; i<pos-1; i++) {
            previous_node=previous_node->next;
        }
    }    

    new->previous=previous_node;

    if (previous_node->next!=NULL) {
        previous_node->next->previous=new;
    }

    new->next=previous_node->next;
    previous_node->next=new;

    printf("%c inserido em %d", nucleotide, pos);

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

    printf("%c removido de %d", sequence->nucleotide, pos);

    free(sequence);

    return DNA_start;
}

void reverse_prefix(node DNA_start, int len) {
    int i;
    char temp;
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
}

void reverse_suffix(node DNA_start, int len) {
    int i;
    char temp;
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
}

node transpose_sequence(node DNA_start, int start, int end, int offset) {
    int i;
    node start_node, end_node, temp_node;

    if (offset!=0) {
        start_node=DNA_start;
        end_node=DNA_start;

        for (i=0; i<start; i++) {
            start_node=start_node->next;
        }

        for (i=0; i<end; i++) {
            end_node=end_node->next;
        }

        if (start==0) {
            DNA_start=end_node->next;
        }

        if (offset>0) {
            temp_node=end_node->next->next;

            if (start_node->previous!=NULL) {
                start_node->previous->next=end_node->next;
            } else {
                DNA_start=start_node->next;
            }

            end_node->next->previous=start_node->previous;

            start_node->previous=end_node->next;
            end_node->next->next=start_node;

            if (temp_node!=NULL) {
                temp_node->previous=end_node;
            }

            end_node->next=temp_node;

            transpose_sequence(DNA_start, start+1, end+1, offset-1);

        } else if (offset<0) {
            temp_node=start_node->previous->previous;

            if (end_node->next!=NULL){
                end_node->next->previous=start_node->previous;
            }

            start_node->previous->next=end_node->next;

            end_node->next=start_node->previous;
            start_node->previous->previous=end_node;

            if (temp_node!=NULL) {
                temp_node->next=start_node;
            }
            
            start_node->previous=temp_node;

            transpose_sequence(DNA_start, start-1, end-1, offset+1);
        }
    }

    return DNA_start;
}


void print_sequence(node sequence_start, int is_subsequence, int len) {
    int i;
    node current;

    current=sequence_start;

    if (!is_subsequence) {
        while (current!=NULL) {
            printf("%c ", current->nucleotide);
            current=current->next;
        }
    } else {
        for (i=0; i<len; i++) {
            printf("%c ", current->nucleotide);
            current=current->next;
        }
    }
}

void free_sequence(node DNA_sequence) {
    node temp_next, temp_current;

    temp_current=DNA_sequence;

    while (temp_current!=NULL) {
        temp_next=temp_current->next;
        //free(temp_current->nucleotide);
        free(temp_current);
        temp_current=temp_next;
    }

    free(temp_current);
    free(temp_next);
}


int main() {
    int i, position, length, start, end, offset;
    char command[MAX_COMMAND_LENGTH], nucleotide;
    node DNA_sequence_start=NULL, start_node;
    
    while (1) {
        
        scanf("%s", command);

        if (strcmp(command, "inserir")==0) {
            scanf("%*[ ]%c%d", &nucleotide, &position);

            DNA_sequence_start=insert_nucleotide(DNA_sequence_start, nucleotide, position);






        } else if (strcmp(command, "remover")==0) {
            scanf("%d", &position);

            DNA_sequence_start=remove_nucleotide(DNA_sequence_start, position);





        } else if (strcmp(command, "inverter-prefixo")==0) {
            scanf("%d", &length);

            printf("prefixo ");

            print_sequence(DNA_sequence_start, 1, length);

            printf("-> ");

            reverse_prefix(DNA_sequence_start, length);

            print_sequence(DNA_sequence_start, 1, length);


        } else if (strcmp(command, "inverter-sufixo")==0) {
            scanf("%d", &length);

            start_node=DNA_sequence_start;

            for (; start_node->next!=NULL; start_node=start_node->next);

            for (i=0; i<length-1; i++) {
                start_node=start_node->previous;
            }

            printf("sufixo ");

            print_sequence(start_node, 1, length);

            printf("-> ");

            reverse_suffix(DNA_sequence_start, length);

            print_sequence(start_node, 1, length);



        } else if (strcmp(command, "transpor")==0) {
            scanf("%d %d %d", &start, &end, &offset);

            start_node=DNA_sequence_start;

            for (i=0; i<start; i++) {
                start_node=start_node->next;
            }

            printf("subsequencia ");

            print_sequence(start_node, 1, end-start+1);

            if (offset>0) {
                printf(">> %d", offset);
            } else {
                printf("<< %d", -1*offset);
            }

            DNA_sequence_start=transpose_sequence(DNA_sequence_start, start, end, offset);

        } else if (strcmp(command, "imprimir")==0) {
            printf("sequencia ");
            print_sequence(DNA_sequence_start, 0, 0);





        } else if (strcmp(command, "sair")==0) {
            break;





        } else {
            printf("Comando nao reconhecido");
        }

        printf("\n");
    }

    free_sequence(DNA_sequence_start);

    return 0;
}