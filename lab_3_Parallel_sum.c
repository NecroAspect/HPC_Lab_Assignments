#include <stdio.h>
#include <mpi.h>

#define ARRAY_SIZE 10

int main(int argc, char *argv[]) {
    int rank, size;
    int array[ARRAY_SIZE];
    int sum = 0;
    int total_sum = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Initialize array with values
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i + 1;
    }

    // Distribute array elements among processes
    int local_sum = 0;
    for (int i = rank; i < ARRAY_SIZE; i += size) {
        local_sum += array[i];
    }

    // Sum the local sums from each process
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Print result
    if (rank == 0) {
        printf("Total sum: %d\n", total_sum);
    }

    MPI_Finalize();
    return 0;
}




/*

    terminal commands : 
    mpicc -o lab_3_Parallel_sum lab_3_Parallel_sum.c
    mpiexec -np 4 ./lab_3_Parallel_sum

*/