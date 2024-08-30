#include <stdio.h>
#define MAX 100

// Reads and stores a matrix of max size 100 by 100
void read_matrix(int matrix[][MAX], int rows, int columns) {
    int i, j;

    for (i=0; i<rows; i++) {
        for (j=0; j<columns; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

// Checks if matrix[i][j] is the only minimum value in row [i]
int is_min_in_row(int matrix[][MAX], int columns, int i, int j) {
    int k;

    for (k=0; k<columns; k++) {
        if (matrix[i][j]>=matrix[i][k] && k!=j) {
            return 0;
        }
    }

    return 1;
}

// Checks if matrix[i][j] is the only maximum value in column [j]
int is_max_in_column(int matrix[][MAX], int rows, int i, int j) {
    int k;

    for (k=0; k<rows; k++) {
        if (matrix[i][j]<=matrix[k][j] && k!=i) {
            return 0;
        }
    }

    return 1;
}

// Checks if matrix[i][j] is a saddle point
int is_saddle_point(int matrix[][MAX], int rows, int columns, int i, int j) {
    if (is_min_in_row(matrix, columns, i, j) && is_max_in_column(matrix, rows, i, j)) {
        return 1;
    }

    return 0;
}

int main() {
    int rows, columns, matrix[MAX][MAX];
    int i=0, j=0;
    int saddle_point_exists=0;

    scanf("%d %d", &rows, &columns);

    read_matrix(matrix, rows, columns);

    // Check each position in the matrix for a saddle point
    // Sets "saddle_point_exists" to 1 if one is found
    for (i=0; i<rows; i++) {
        for (j=0; j<columns; j++) {
            if (is_saddle_point(matrix, rows, columns, i, j)) {
                printf("(%d, %d) eh ponto de sela com valor %d\n", i, j, matrix[i][j]);
                saddle_point_exists=1;
            }
        }
    }

    // Case where no saddle point was found
    if (!saddle_point_exists) {
        printf("nao existe ponto de sela");
    }

    return 0;
}