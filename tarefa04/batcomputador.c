#include <stdio.h>
#include <stdlib.h>

// TODO
// bat_alloc: 
    //1 alloc [array_size + array]
    //2 copy list with double the size, keeping addresses intact
    //3 must store in first position the array fits
    //4 store occupied addresses

// bat_free
    //1 update free addresses (bat_alloc4)
    //2 if last 3/4 are free, half list's size, keeping it >8

// bat_print
    //1 print integers of corresponding array (without its size)
        // it can refer to the middle of it (?)

// bat_use
    //1 print used/total ints from memory

void bat_alloc(int n_int);
    int i, temp_int;

    for (i=0; i<n_int; i++) {
        scanf("%d", &int_store);
    }

void bat_free(int address);

void bat_print();

void bat_use();


int main() {
    int n, i, n_int, address, bat_mem[8];
    char command[10];

    scanf("%d", &n);

    for (i=0; i<n; i++) {
        scanf("%s", command);

        if (command=="bat-alloc") {
            scanf("%d", &n_int);

            bat_alloc(n_int);
        }

        else if (command=="bat-free") {
            scanf("%d", &address);

            bat_free(address);
        }

        else if (command=="bat-print") {
            scanf("%d", &address);
            bat_print();
        }

        else if (command=="bat-use") {
            bat_use();
        }

        else {
            printf("Comando nao reconhecido");
        }
        
    }

    return 0;
}