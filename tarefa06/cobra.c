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
    node previous;
    node next;
};


node create_head(int head_x, int head_y) {
    node head;

    head->next=head;
    head->previous=head;

    head->position.x=head_x;
    head->position.y=head_y;

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

void eat_fruit(node head);

void collision_check(node head);

void print_board();


int main() {
    int *board;
    node head;



    return 0;
}