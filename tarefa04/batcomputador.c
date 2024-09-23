#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_COMMAND_LENGTH 10
#define INITIAL_MEMORY_SIZE 8


typedef struct mem {
    int size;
    int *num_array;
    int free_space;
} mem;

// Function to initialize a mem type variable
// Sets all values in memory.num_array to -1, indicating free slots
void initialize_mem(mem *memory) {
    int i;

    memory->size=INITIAL_MEMORY_SIZE;
    memory->free_space=INITIAL_MEMORY_SIZE;

    memory->num_array=malloc(INITIAL_MEMORY_SIZE*sizeof(int));

    for (i=0; i<INITIAL_MEMORY_SIZE; i++) {
        memory->num_array[i]=-1;
    }
}

// Function to expand memory, doubling its size
void double_mem(mem *bat_mem) {
    int i=0, *temp_array;

    temp_array=bat_mem->num_array;

    bat_mem->free_space+=bat_mem->size;
    bat_mem->size*=2;

    bat_mem->num_array=malloc(bat_mem->size*sizeof(int));

    for (; i<bat_mem->size/2; i++) {
        bat_mem->num_array[i]=temp_array[i];
    }

    for (; i<bat_mem->size; i++) {
        bat_mem->num_array[i]=-1;
    }

    free(temp_array);
}

// Function to find the first free continuous slot in memory with specified size
// Returns -1 if none are found
int find_free(mem* bat_mem, int num_search) {
    int i=0, count=0;

    for (; i<bat_mem->size; i++) {
        if (bat_mem->num_array[i]==-1) {
            count++;

            if (count==num_search) {
                return i-num_search+1;
            }
        } else {
            count=0;
        }
    }

    return -1;
}

// Bat_alloc command
// Allocates memory for an array, containing [size + data]
// Runs double_mem if needed
void bat_alloc(mem *bat_mem, int n_int) {
    int i, temp_int, start_address;

    if (n_int+1>bat_mem->free_space || find_free(bat_mem, n_int+1)==-1) {
        double_mem(bat_mem);
    }

    bat_mem->free_space-=n_int+1;

    start_address=find_free(bat_mem, n_int+1);

    bat_mem->num_array[start_address]=n_int;

    for (i=0; i<n_int; i++) {
        scanf("%d", &temp_int);

        bat_mem->num_array[start_address+i+1]=temp_int;
    }

    printf("%d\n", start_address);
}

// Function to check if a function can be cleaned up
int can_cleanup(mem *bat_mem) {
    int i;

    for (i=0; i<bat_mem->size/4; i++) {
        if (bat_mem->num_array[i]==-1) {
            return 0;
        }
    }

    return 1;
}

// Function to free memory, reducing size by 1/2
void mem_cleanup(mem *bat_mem) {
    int i=0, *temp_array;

    temp_array=bat_mem->num_array;

    bat_mem->free_space-=bat_mem->size*1/2;
    bat_mem->size/=2;

    bat_mem->num_array=malloc(bat_mem->size*sizeof(int));

    for (; i<bat_mem->size; i++) {
        bat_mem->num_array[i]=temp_array[i];
    }
}

// Bat_free command
// Frees up an array in memory from a specified address
// Runs can_cleanup and mem_cleanup if possible
void bat_free(mem *bat_mem, int address) {
    int n, i, mem_used;

    n=bat_mem->num_array[address];
    bat_mem->free_space+=n+1;
    mem_used=bat_mem->size-bat_mem->free_space;

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

// Bat_print command
// Prints the array stored in the specified position
void bat_print(mem *bat_mem, int address) {
    int i, n;

    n=bat_mem->num_array[address];

    for (i=0; i<n; i++) {
        printf("%d ", bat_mem->num_array[address+i+1]);
    }

    printf("\n");
}

// Bat_usage command
// Prints out used/total memory
void bat_usage(mem *bat_mem) {
    int used=bat_mem->size-bat_mem->free_space;

    printf("%d de %d\n", used, bat_mem->size);
}


// Main
int main() {
    int n, i, n_int, address;
    mem bat_mem;
    char command[MAX_COMMAND_LENGTH];

    initialize_mem(&bat_mem);

    scanf("%d", &n);

    for (i=0; i<n; i++) {
        scanf("%s", command);

        if (strcmp(command, "bat-alloc")==0) {
            scanf("%d", &n_int);

            bat_alloc(&bat_mem, n_int);

        } else if (strcmp(command, "bat-free")==0) {
            scanf("%d", &address);

            bat_free(&bat_mem, address);

        } else if (strcmp(command, "bat-print")==0) {
            scanf("%d", &address);

            bat_print(&bat_mem, address);

        } else if (strcmp(command, "bat-uso")==0) {
            bat_usage(&bat_mem);

        } else {
            printf("Comando nao reconhecido");
            break;
        } 
    }

    free(bat_mem.num_array);

    return 0;
}