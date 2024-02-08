#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5
#define NUM_ITERATIONS 10000

// Global variables
int counter = 0;
pthread_mutex_t mutex;

// Function executed by each thread
void* increment_counter(void* arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        // Acquire the mutex lock
        pthread_mutex_lock(&mutex);

        // Critical section
        counter++;

        // Release the mutex lock
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Initialize the mutex
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        printf("Mutex initialization failed.\n");
        return 1;
    }

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, increment_counter, NULL) != 0) {
            printf("Error creating thread %d.\n", i);
            return 1;
        }
    }

    // Join threads
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            printf("Error joining thread %d.\n", i);
            return 1;
        }
    }

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    // Print the final value of the counter
    printf("Final counter value: %d\n", counter);

    return 0;
}




/*

    gcc -o lab_7_process_synchronization lab_7_process_synchronization.c -pthread
    ./lab_7_process_synchronization


*/