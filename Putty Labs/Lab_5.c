#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size, p;
    char message[100];
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number of times to pass messages>\n", argv[0]);
        MPI_Finalize();
        return 1;
    }
    p = atoi(argv[1]);
    if (size < 2) {
        fprintf(stderr, "This program should be run with at least 2 processes.\n");
        MPI_Finalize();
        return 1;
    }
    int next_rank = (rank + 1) % size;
    int prev_rank = (rank - 1 + size) % size;
    for (int i = 0; i < p; i++) {
        sprintf(message, "Greetings from Process %d, round %d", rank, i);
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, next_rank, 0, MPI_COMM_WORLD);
        MPI_Recv(message, 100, MPI_CHAR, prev_rank, 0, MPI_COMM_WORLD, &status);
        printf("Process %d received: %s\n", rank, message);
    }
    MPI_Finalize();
    return 0;
}

