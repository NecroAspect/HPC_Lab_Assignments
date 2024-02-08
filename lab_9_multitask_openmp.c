#include <stdio.h>
#include <omp.h>

int main() {
    // Define the number of tasks
    int num_tasks = 5;

    // Parallel region starts here
    #pragma omp parallel num_threads(num_tasks)
    {
        // Get the task ID
        int task_id = omp_get_thread_num();

        // Perform different tasks based on task ID
        switch(task_id) {
            case 0:
                printf("Task %d: Printing 'Hello' from thread %d\n", task_id, omp_get_thread_num());
                break;
            case 1:
                printf("Task %d: Printing 'World' from thread %d\n", task_id, omp_get_thread_num());
                break;
            case 2:
                printf("Task %d: Printing 'OpenMP' from thread %d\n", task_id, omp_get_thread_num());
                break;
            case 3:
                printf("Task %d: Printing 'Multitasking' from thread %d\n", task_id, omp_get_thread_num());
                break;
            case 4:
                printf("Task %d: Printing 'Using OpenMP' from thread %d\n", task_id, omp_get_thread_num());
                break;
        }
    } // Parallel region ends here

    return 0;
}





/*

    terminal commands : 
    gcc -o lab_9_multitask_openmp lab_9_multitask_openmp.c -fopenmp
    ./lab_9_multitask_openmp


*/