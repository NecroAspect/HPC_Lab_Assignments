#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

void multiply_matrices(int** mat1, int** mat2, int** result) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = 0;
            for (int k = 0; k < SIZE; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

int main() {
    int** mat1 = (int**)malloc(SIZE * sizeof(int*));
    int** mat2 = (int**)malloc(SIZE * sizeof(int*));
    int** result = (int**)malloc(SIZE * sizeof(int*));

    // Allocate memory for each row
    for (int i = 0; i < SIZE; i++) {
        mat1[i] = (int*)malloc(SIZE * sizeof(int));
        mat2[i] = (int*)malloc(SIZE * sizeof(int));
        result[i] = (int*)malloc(SIZE * sizeof(int));
    }

    // Initialize matrices
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            mat1[i][j] = rand() % 100; // random values between 0 and 99
            mat2[i][j] = rand() % 100;
        }
    }

    // Measure execution time
    clock_t start_time = clock();

    multiply_matrices(mat1, mat2, result);

    clock_t end_time = clock();
    double execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Execution time: %f seconds\n", execution_time);

    // Free dynamically allocated memory
    for (int i = 0; i < SIZE; i++) {
        free(mat1[i]);
        free(mat2[i]);
        free(result[i]);
    }
    free(mat1);
    free(mat2);
    free(result);

    return 0;
}



/*

    terminal commands : 
    gcc -o lab_1_matrix_multiplication lab_1_matrix_multiplication.c
    time ./lab_1_matrix_multiplication

    the code is okay, it is just taking a lot of time to execute. 

*/
