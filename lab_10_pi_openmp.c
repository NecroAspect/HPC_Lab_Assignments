#include <stdio.h>
#include <omp.h>

#define NUM_STEPS 1000000000

int main() {
    double pi;
    double step;
    double x, sum = 0.0;

    step = 1.0 / (double)NUM_STEPS;

    // Parallel region starts here
    #pragma omp parallel for private(x) reduction(+:sum)
    for (int i = 0; i < NUM_STEPS; i++) {
        x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    } // Parallel region ends here

    pi = step * sum;

    printf("Estimated value of PI: %f\n", pi);

    return 0;
}




/*

    terminal commands : 
    gcc -o lab_10_pi_openmp lab_10_pi_openmp.c -fopenmp
    ./lab_10_pi_openmp


*/