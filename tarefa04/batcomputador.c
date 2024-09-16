#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct mem {
    int size;
    int *num_array;
    int free;
} mem;

// TODO
// bat_alloc: 
    //1 alloc [array_size + array]      DONE
    //2 copy list with double the size, keeping addresses intact        DONE?
    //3 must store in first position the array fits     DONE?
    //4 store occupied addresses

// bat_free
    //1 update free addresses (bat_alloc4)
    //2 if last 3/4 are free, half list's size, keeping it >8

// bat_print
    //1 print integers of corresponding array (without its size)
        // it can refer to the middle of it (?)

// bat_use
    //1 print used/total ints from memory

void double_mem(mem *bat_mem) {
    int i=0, *temp_array;

    temp_array=bat_mem->num_array;

    bat_mem->size*=2;

    bat_mem->num_array=malloc(bat_mem->size*sizeof(int));

    for (; i<bat_mem->size-bat_mem->free; i++) {
        bat_mem->num_array[i]=temp_array[i];
    }

    free(temp_array);
}

int find_free(mem* bat_mem, int num_search) {
    int i=0, count=0;

    for (; i<bat_mem->size; i++) {
        if (bat_mem->num_array[i]==-1) {
            count++;

            if (count==num_search) {
                //return bat_mem->num_array[i-num_search+1];
                return i-num_search+1;
            }

        } else {
            count=0;
        }
    }
}

void bat_alloc(int n_int, mem *bat_mem, int free_mem) {
    int i, temp_int, *temp_array, start_address;

    temp_array=malloc((n_int+1)*sizeof(int));

    if (free_mem<n_int) {
        double_mem(bat_mem);
    }

    start_address=find_free(bat_mem, n_int+1);

    bat_mem->num_array[start_address]=n_int;

    for (i=0; i<n_int; i++) {
        scanf("%d", &temp_int);

        bat_mem->num_array[start_address+i+1]=temp_int;
    }

    printf("%d", start_address);
}

void bat_free(int address) {
    printf("bat_free");
}

void bat_print() {
    printf("bat_print");
}

void bat_use() {
    printf("bat_uso");
}

int main() {
    int n, i, n_int, address, bat_mem_old[8], free_mem=8, size=8, *temp;
    mem bat_mem;
    char command[10];

    bat_mem.size=8;
    bat_mem.free=8;

    bat_mem.num_array=malloc(8*sizeof(int));

    for (i=0; i<8; i++) {
        bat_mem.num_array[i]=-1;
    }

    scanf("%d", &n);

    for (i=0; i<n; i++) {
        scanf("%s", command);

        if (strcmp(command, "bat-alloc")==0) {
            scanf("%d", &n_int);

            free_mem-=n_int+1;

            bat_alloc(n_int, &bat_mem, free_mem);

        } else if (strcmp(command, "bat-free")==0) {
            scanf("%d", &address);

            bat_free(address);

        } else if (strcmp(command, "bat-print")==0) {
            scanf("%d", &address);
            bat_print();

        } else if (strcmp(command, "bat-uso")==0) {
            bat_use();

        } else {
            printf("Comando nao reconhecido");
        }
        
    }

    return 0;
}