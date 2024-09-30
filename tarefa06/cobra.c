#include <stdio.h>
#include <stdlib.h>


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

void move(node head, int move_x, int move_y) {
    node temp_node=head->previous;

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

int collision_check(node head, pos fruit) {
    int i;
    node current_node;
    current_node=head->next;

    if (head->position.x==fruit.x && head->position.y==fruit.y) {
        eat_fruit(head)
    }

    while (!current_node->is_head) {
        if (head->position.x==current_node->position.x && head->position.y==current_node->position.y) {
            return 1;
        } else {
            current_node=current_node->next;
        }
    }

    return 0;
}

void eat_fruit(node head) {
    if 
}



void print_board();


int main() {
    int *board;
    node head;



    return 0;
}