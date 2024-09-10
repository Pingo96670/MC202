#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to print a point's coordinates
void print_point(double *point, int d) {
    for (int i=0; i<d; i++) {
        printf("%.3lf ", point[i]);
    }
}

// Function to find the maximum value in a given coordinate from a list of points
// Used in the function min_max
double max_coord(double **coord_array, int n, int pos) {
    double max=coord_array[0][pos];

    for (int i=1; i<n; i++) {
        if (coord_array[i][pos]>max) {
            max=coord_array[i][pos];
        }
    }

    return max;
}

// Function to find the minimum value in a given coordinate from a list of points
// Used in the function min_max
double min_coord(double **coord_array, int n, int pos) {
    double min=coord_array[0][pos];

    for (int i=1; i<n; i++) {
        if (coord_array[i][pos]<min) {
            min=coord_array[i][pos];
        }
    }
    
    return min;
}

// Function to find the min-max value of a given coordinate in a point from an array
// Used in the function strat2
double min_max(double x, double **array, int n, int pos) {
    if (min_coord(array, n, pos)==max_coord(array, n, pos)) {
        return 0;
    }
    return 2*(x-min_coord(array, n, pos))/(max_coord(array, n, pos)-min_coord(array, n, pos))-1;
}

// Direct method
void strat1(double **points, int n, int d, double centroid1[]) {
    double temp_sum;

    // Simple average of respective coordinates
    for (int i=0; i<d; i++) {
        temp_sum=0;
        for (int j=0; j<n; j++) {
            temp_sum+=points[j][i];
        }

        centroid1[i]=temp_sum/n;
    };
}

// Min-max normalization method
void strat2(double **points, int n, int d, double centroid2[]) {
    int i, j;

    // Readying the centroid array
    for (i=0; i<d; i++) {
        centroid2[i]=0;
    }

    // Evaluating the centroid's coordinates
    for (i=0; i<n; i++) {
        for (j=0; j<d; j++) {
            centroid2[j]+=min_max(points[i][j], points, n, j)/n;
        }
    }
}

// Unit vector method
void strat3(double **points, int n, int d, double centroid3[]) {
    double temp_sum, *norm;
    int i, j;

    // Allocation, evaluation and storage of each point's norm
    norm=malloc(n*sizeof(double));

    for (i=0; i<n; i++) {
        temp_sum=0;
        for (j=0; j<d; j++) {
            temp_sum+=powf(points[i][j], 2);
        }
        norm[i]=sqrt(temp_sum);
    }

    // Normalization
    for (j=0; j<d; j++) {
        temp_sum=0;

        for (int i=0; i<n; i++) {
            temp_sum+=points[i][j]/norm[i];
        }

        centroid3[j]=temp_sum/n;
    }

    //Freeing allocated memory
    free(norm);    
}

int main() {
    int d, n;
    double **points, *centroid;

    scanf("%d %d", &d, &n);

    //Memory allocation
    points = malloc(n*sizeof(double*));
    centroid = malloc(d*sizeof(double));

    for (int i=0; i<n; i++) {
        points[i]=malloc(d*sizeof(double));

        for (int j=0; j<d; j++) {
            scanf("%lf", &points[i][j]);
        } 
    }

    // Printing results
    printf("nenhum: ");
    strat1(points, n, d, centroid);
    print_point(centroid, d);

    printf("\njanela: ");
    strat2(points, n, d, centroid);
    print_point(centroid, d);

    printf("\nnormal: ");
    strat3(points, n, d, centroid);
    print_point(centroid, d);

    //Freeing allocated memory
    for (int i=0; i<n; i++) {
        free(points[i]);
    }

    free(centroid);
    free(points);

    return 0;
}