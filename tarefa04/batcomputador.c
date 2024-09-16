#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct mem {
    int size;
    int *num_array;
    int free;
} mem;

// TODO
// All
    // Reorganize arguments order
    // Cleanup

void debug_print(mem *bat_mem) {
    for (int i=0; i<bat_mem->size; i++) {
        printf("%d ", bat_mem->num_array[i]);
    }
}

int can_cleanup(mem *bat_mem) {
    int i;

    for (i=0; i<bat_mem->size/4; i++) {
        if (bat_mem->num_array[i]==-1) {
            return 0;
        }
    }

    return 1;
}

void mem_cleanup(mem *bat_mem) {
    int i=0, *temp_array;

    temp_array=bat_mem->num_array;

    bat_mem->free-=bat_mem->size*1/2;
    bat_mem->size/=2;

    bat_mem->num_array=malloc(bat_mem->size*sizeof(int));

    for (; i<bat_mem->size; i++) {
        bat_mem->num_array[i]=temp_array[i];
    }
}

void double_mem(mem *bat_mem) {
    int i=0, *temp_array;

    temp_array=bat_mem->num_array;

    bat_mem->free+=bat_mem->size;
    bat_mem->size*=2;

    //free(bat_mem->num_array);

    bat_mem->num_array=malloc(bat_mem->size*sizeof(int));

    for (; i<bat_mem->size/2; i++) {
        bat_mem->num_array[i]=temp_array[i];
    }

    for (; i<bat_mem->size; i++) {
        bat_mem->num_array[i]=-1;
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

    return -1;
}

void bat_alloc(int n_int, mem *bat_mem) {
    int i, temp_int, start_address;

    if (n_int+1>bat_mem->free || find_free(bat_mem, n_int+1)==-1) {
        double_mem(bat_mem);
    }

    bat_mem->free-=n_int+1;

    start_address=find_free(bat_mem, n_int+1);

    bat_mem->num_array[start_address]=n_int;

    for (i=0; i<n_int; i++) {
        scanf("%d", &temp_int);

        bat_mem->num_array[start_address+i+1]=temp_int;
    }

    printf("%d\n", start_address);
}

void bat_free(mem *bat_mem, int address) {
    int n, i, mem_used;

    n=bat_mem->num_array[address];
    bat_mem->free+=n+1;
    mem_used=bat_mem->size-bat_mem->free;

    for (i=0; i<n+1; i++) {
        bat_mem->num_array[address+i]=-1;
    }

    while (mem_used<=bat_mem->size/4 && bat_mem->size>8) {
        if (can_cleanup(bat_mem)) {
            mem_cleanup(bat_mem);

        } else {
            break;
        }
    }
}

void bat_print(mem *bat_mem, int address) {
    int i, n;

    n=bat_mem->num_array[address];

    for (i=0; i<n; i++) {
        printf("%d ", bat_mem->num_array[address+i+1]);
    }

    printf("\n");
}

void bat_usage(mem *bat_mem) {
    int used=bat_mem->size-bat_mem->free;

    printf("%d de %d\n", used, bat_mem->size);
}

int main() {
    int n, i, n_int, address;
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

            bat_alloc(n_int, &bat_mem);

        } else if (strcmp(command, "bat-free")==0) {
            scanf("%d", &address);

            bat_free(&bat_mem, address);

        } else if (strcmp(command, "bat-print")==0) {
            scanf("%d", &address);

            bat_print(&bat_mem, address);

        } else if (strcmp(command, "bat-uso")==0) {
            bat_usage(&bat_mem);

        } else if (strcmp(command, "debug")==0) {
            debug_print(&bat_mem);

        } else {
            printf("Comando nao reconhecido");
            break;
        }
        
    }

    return 0;
}