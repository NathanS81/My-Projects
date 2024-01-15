#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#define N 1001
#define TOLERANCE 0.001
#define MAX_ITER 1000

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int block_size = N / size;  // Number of elements per process

    double x[block_size + 2];  // +2 for the boundary elements
    double x_new[block_size + 2];
    double x_global[N];

    for (int i = 0; i < block_size + 2; i++) {
        x[i] = 0.0;
        x_new[i] = 0.0;
    }

    // Set boundary conditions for the first and last processes
    if (rank == 0) {
        x[0] = 10.0;
    }
    if (rank == size - 1) {
        x[block_size + 1] = 250.0;
    }

    int iteration = 0;
    double max_diff = TOLERANCE + 1.0;

    while (iteration < MAX_ITER && max_diff > TOLERANCE) {
        max_diff = 0.0;

        // Compute the new values of x
        for (int i = 1; i <= block_size; i++) {
            x_new[i] = (x[i - 1] + x[i + 1]) / 2.0;
            double diff = fabs(x_new[i] - x[i]);
            if (diff > max_diff) {
                max_diff = diff;
            }
        }

        // Exchange boundary elements with neighboring processes
        if (rank > 0) {
            MPI_Send(&x_new[1], 1, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD);
            MPI_Recv(&x_new[0], 1, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        if (rank < size - 1) {
            MPI_Send(&x_new[block_size], 1, MPI_DOUBLE, rank + 1, 0, MPI_COMM_WORLD);
            MPI_Recv(&x_new[block_size + 1], 1, MPI_DOUBLE, rank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        // Copy the new values back to x
        for (int i = 1; i <= block_size; i++) {
            x[i] = x_new[i];
        }

        // Gather all values on Process 0
        MPI_Gather(x + 1, block_size, MPI_DOUBLE, x_global, block_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        if (rank == 0 && (iteration % 50 == 0 || max_diff <= TOLERANCE)) {
            printf("Iteration %d: ", iteration);
            for (int i = 0; i <= 10; i++) {
                int index = i * 100;
                if (index < N) {
                    printf("%.2f ", x_global[index]);
                }
            }
            printf("\n");
        }

        iteration++;
    }

    MPI_Finalize();
    return 0;
}