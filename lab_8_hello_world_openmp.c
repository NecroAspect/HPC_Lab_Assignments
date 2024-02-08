#include <stdio.h>
#include <omp.h>

int main() {
    int num_threads;

    // Set the number of threads to use
    omp_set_num_threads(4); // You can change this value as needed

    // Parallel region starts here
    #pragma omp parallel
    {
        // Get the total number of threads
        num_threads = omp_get_num_threads();

        // Get the thread number
        int thread_num = omp_get_thread_num();

        // Print "Hello World" message with thread number
        printf("Hello World from thread %d\n", thread_num);
    } // Parallel region ends here

    // Print the total number of threads
    printf("Total number of threads: %d\n", num_threads);

    return 0;
}





/*

    terminal commands : 
    gcc -o lab_8_hello_world_openmp lab_8_hello_world_openmp.c -fopenmp
    ./lab_8_hello_world_openmp


*/