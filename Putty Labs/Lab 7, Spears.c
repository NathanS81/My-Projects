#include <stdio.h>
#include <mpi.h>
#include <unistd.h>

#define NUM_TOKENS 100
#define SLEEP_TIME 1

int main(int argc, char** argv) {
    int rank, size;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        printf("This program should be run with at least 2 processes.\n");
        MPI_Finalize();
        return 1;
    }

    if (rank == 0) {
        int tokens[NUM_TOKENS];
        for (int i = 0; i < NUM_TOKENS; i++) {
            tokens[i] = i; // Generate tokens (integers)
        }

        // Distribute tokens to the first worker process
        for (int i = 0; i < NUM_TOKENS; i++) {
            MPI_Send(&tokens[i], 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        }

        // Send termination token to stop the pipeline
        int termination_token = -1;
        for (int i = 1; i < size; i++) {
            MPI_Send(&termination_token, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    } else {
        int received_token;
        int tasks_processed = 0;

        while (1) {
            MPI_Recv(&received_token, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);

            if (received_token == -1) {
                // Termination token received, exit the loop
                break;
            }

            usleep(SLEEP_TIME * 1000000); // Simulate task processing
            tasks_processed++;

            MPI_Send(&received_token, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
        }

        // Print the rank and the number of tasks processed
        printf("Process %d processed %d tasks.\n", rank, tasks_processed);
    }

    MPI_Finalize();
    return 0;
}