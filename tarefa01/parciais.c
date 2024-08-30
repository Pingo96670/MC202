#include <stdio.h>
#define MAX 1000

// Creates copy of int array of size n into another
void copy_sequence(int sequence[], int sequence_copy[], int n) {
    int i;

    for (i=0; i<n; i++) {
        sequence_copy[i]=sequence[i];
    }
}

// Returns the partial sum up to a number of position i in an int array of size n
int partial_sum(int sequence[], int n, int i) {
    int j, partial_sum=0;

    for (j=i; j>=0; j--) {
        partial_sum+=sequence[j];
    }

    return partial_sum;
}

// Reverses an int array of size n
void reverse_sequence(int sequence[], int n) {
    int i, aux[MAX];

    copy_sequence(sequence, aux, n);

    for (i=0; i<n; i++) {
        sequence[i]=aux[n-i-1];
    }

}

// Prints an int array of size n
void print_sequence(int sequence[], int n) {
    int i;

    for (i=0; i<n; i++) {
        printf("%d ", sequence[i]);
    }
}

int main() {
    int n, sequence[MAX];

    scanf("%d", &n);

    for (int i=0; i<n; i++) {
        scanf("%d", &sequence[i]);
    }

    for (int i=n-1; i>0; i--) {
        sequence[i]=partial_sum(sequence, n, i);
    }

    reverse_sequence(sequence, n);
    print_sequence(sequence, n);

    return 0;
}