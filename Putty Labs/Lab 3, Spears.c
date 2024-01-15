#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <mpi.h>

#define N 1000000  // Number of random points
#define ANALYTICAL_RESULT 3.14159265359 // Analytical result for comparison
#define THRESHOLD 0.001 // Threshold for convergence

double f(double x) {
    return 4.0 / (1.0 + x * x);
}

int main(int argc, char** argv) {
    int rank, size;
    double local_sum = 0.0;
    double global_sum = 0.0;
    int n = N; // Initial number of random points

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    srand(time(NULL) + rank); // Seed the random number generator differently for each process

    while (1) {
        local_sum = 0.0;

        // Generate random xr's and calculate the local sum
        for (int i = 0; i < n; i++) {
            double x = (double)rand() / RAND_MAX; // Random number between 0 and 1
            local_sum += f(x);
        }

        // Reduce local sums to get the global sum
        MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

        if (rank == 0) {
            global_sum /= n * size; // Average the global sum
            double empirical_result = global_sum;
            double error = fabs(empirical_result - ANALYTICAL_RESULT);

            printf("N = %d, Empirical Result = %lf, Error = %lf\n", n, empirical_result, error);

            if (error < THRESHOLD) {
                break; // Convergence achieved
            } else {
                n *= 2; // Double the number of random points and continue
            }
        }

        MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD); // Broadcast the updated value of n
    }

    MPI_Finalize();
    return 0;
}

