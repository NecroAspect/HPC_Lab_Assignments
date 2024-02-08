#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_TERM 100

// Structure to hold arguments for each thread
typedef struct {
    int n;  // Number of terms to generate
    unsigned long long* fibonacci_sequence;  // Array to store the Fibonacci sequence
} ThreadArgs;

// Function to generate Fibonacci sequence
void* generate_fibonacci(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    int n = args->n;
    unsigned long long* fibonacci_sequence = args->fibonacci_sequence;

    // Generate Fibonacci sequence
    fibonacci_sequence[0] = 0;
    fibonacci_sequence[1] = 1;
    for (int i = 2; i < n; i++) {
        fibonacci_sequence[i] = fibonacci_sequence[i - 1] + fibonacci_sequence[i - 2];
    }

    pthread_exit(NULL);
}

int main() {
    int num_terms;
    pthread_t tid;
    ThreadArgs args;

    printf("Enter the number of Fibonacci terms to generate: ");
    scanf("%d", &num_terms);

    // Ensure the number of terms does not exceed the maximum limit
    if (num_terms > MAX_TERM) {
        printf("Number of terms exceeds maximum limit. Setting it to %d.\n", MAX_TERM);
        num_terms = MAX_TERM;
    }

    // Allocate memory for the Fibonacci sequence array
    unsigned long long* fibonacci_sequence = (unsigned long long*)malloc(num_terms * sizeof(unsigned long long));
    if (fibonacci_sequence == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Set arguments for the thread
    args.n = num_terms;
    args.fibonacci_sequence = fibonacci_sequence;

    // Create a thread to generate Fibonacci sequence
    if (pthread_create(&tid, NULL, generate_fibonacci, &args)) {
        printf("Error creating thread.\n");
        free(fibonacci_sequence);
        return 1;
    }

    // Wait for the thread to finish
    if (pthread_join(tid, NULL)) {
        printf("Error joining thread.\n");
        free(fibonacci_sequence);
        return 1;
    }

    // Print the generated Fibonacci sequence
    printf("Fibonacci sequence:\n");
    for (int i = 0; i < num_terms; i++) {
        printf("%llu ", fibonacci_sequence[i]);
    }
    printf("\n");

    // Free allocated memory
    free(fibonacci_sequence);

    return 0;
}





/*

    terminal commands : 
    gcc -o lab_6_fibonacci lab_6_fibonacci.c -pthread
    ./lab_6_fibonacci


*/