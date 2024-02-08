#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 4
#define NUM_ITERATIONS 20

int main() {
    int i;

    // Set the number of threads to use
    omp_set_num_threads(NUM_THREADS);

    // Default loop scheduling
    printf("Default loop scheduling:\n");
    #pragma omp parallel
    {
        #pragma omp for
        for (i = 0; i < NUM_ITERATIONS; i++) {
            printf("Thread %d: Iteration %d\n", omp_get_thread_num(), i);
        }
    }

    // Static loop scheduling
    printf("\nStatic loop scheduling:\n");
    #pragma omp parallel
    {
        #pragma omp for schedule(static)
        for (i = 0; i < NUM_ITERATIONS; i++) {
            printf("Thread %d: Iteration %d\n", omp_get_thread_num(), i);
        }
    }

    // Dynamic loop scheduling
    printf("\nDynamic loop scheduling:\n");
    #pragma omp parallel
    {
        #pragma omp for schedule(dynamic)
        for (i = 0; i < NUM_ITERATIONS; i++) {
            printf("Thread %d: Iteration %d\n", omp_get_thread_num(), i);
        }
    }

    return 0;
}





/*

    terminal commands : 
    gcc -o lab_11_loop_scheduling lab_11_loop_scheduling.c -fopenmp
    ./lab_11_loop_scheduling

*/