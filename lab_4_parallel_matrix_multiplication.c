#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define SIZE 100

void initialize_matrix(int matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            matrix[i][j] = rand() % 10; // Random values between 0 and 9
        }
    }
}

void print_matrix(int matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void multiply_matrices(int mat1[SIZE][SIZE], int mat2[SIZE][SIZE], int result[SIZE][SIZE], int start_row, int end_row) {
    for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = 0;
            for (int k = 0; k < SIZE; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int rank, size;
    int mat1[SIZE][SIZE];
    int mat2[SIZE][SIZE];
    int result[SIZE][SIZE];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        printf("Error: Number of processes must be at least 2.\n");
        MPI_Finalize();
        return 1;
    }

    // Master process initializes matrices
    if (rank == 0) {
        initialize_matrix(mat1);
        initialize_matrix(mat2);
    }

    // Broadcast matrices to all processes
    MPI_Bcast(mat1, SIZE * SIZE, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(mat2, SIZE * SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    // Split work among processes
    int rows_per_process = SIZE / (size - 1);
    int start_row = (rank - 1) * rows_per_process;
    int end_row = (rank == size - 1) ? SIZE : start_row + rows_per_process;

    // Multiply matrices in parallel
    multiply_matrices(mat1, mat2, result, start_row, end_row);

    // Gather results from all processes to the master process
    MPI_Gather(result + start_row, rows_per_process * SIZE, MPI_INT, result, rows_per_process * SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    // Master process prints the result
    if (rank == 0) {
        // print_matrix(result);
        printf("Matrix multiplication completed successfully.\n");
    }

    MPI_Finalize();
    return 0;
}








/*

    terminal commands : 
    mpicc -o lab_4_parallel_matrix_multiplication lab_4_parallel_matrix_multiplication.c
    mpiexec -np 4 ./lab_4_parallel_matrix_multiplication



*/