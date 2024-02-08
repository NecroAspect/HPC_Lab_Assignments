#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define SIZE 100

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

int main(int argc, char* argv[]) {
    int rank, size;
    int arr[SIZE];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        printf("Error: Number of processes must be at least 2.\n");
        MPI_Finalize();
        return 1;
    }

    if (rank == 0) {
        printf("Generating array...\n");
        srand(123); // Seed for reproducibility
        for (int i = 0; i < SIZE; i++) {
            arr[i] = rand() % 1000; // Random values between 0 and 999
        }
        printf("Array generated.\n");
    }

    // Broadcast the array to all processes
    MPI_Bcast(arr, SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    // Divide the array into chunks for each process
    int chunk_size = SIZE / size;
    int start = rank * chunk_size;
    int end = (rank == size - 1) ? SIZE : start + chunk_size;

    // Perform local quick sort
    quick_sort(arr, start, end - 1);

    // Gather sorted chunks to the root process
    int* sorted_arr = NULL;
    if (rank == 0) {
        sorted_arr = (int*)malloc(SIZE * sizeof(int));
    }
    MPI_Gather(arr + start, chunk_size, MPI_INT, sorted_arr, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Merge the sorted chunks in the root process
    if (rank == 0) {
        printf("Merging sorted chunks...\n");
        quick_sort(sorted_arr, 0, SIZE - 1);
        printf("Array sorted.\n");
        // Print sorted array
        printf("Sorted array: ");
        for (int i = 0; i < SIZE; i++) {
            printf("%d ", sorted_arr[i]);
        }
        printf("\n");
        free(sorted_arr);
    }

    MPI_Finalize();
    return 0;
}




/*

    terminal commands : 
    mpicc -o lab_5_parallel_quick_sort lab_5_parallel_quick_sort.c
    mpiexec -np 4 ./lab_5_parallel_quick_sort


*/