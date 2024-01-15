#include <math.h>
#include <iostream>
#include "mpi.h"

void printit();

int main(int argc, char* argv[]) {
    double actual_pi = 3.141592653589793238462643; // for comparison later
    int n, rank, num_proc, i;
    double temp_pi, calc_pi, int_size, part_sum, x;
    char response = 'y';

    MPI_Init(&argc, &argv); // Initialize MPI
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) printit(); /* I am root node, print out welcome */

    while (response == 'y') {
        if (rank == 0) { /* I am root node */
            std::cout << "__________________________________" << std::endl;
            std::cout << "\nEnter the number of intervals: (0 will exit)" << std::endl;
            std::cin >> n;
        } else
            n = 0;

        MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD); // Broadcast n

        if (n == 0)
            break; // Check for quit condition
        else {
            int_size = 1.0 / static_cast<double>(n); // Calculate interval size
            part_sum = 0.0;

            for (i = rank; i < n; i += num_proc) {
                x = int_size * (static_cast<double>(i) + 0.5);
                part_sum += (4.0 / (1.0 + x * x));
            }

            temp_pi = int_size * part_sum;

            // Collect all partial sums and compute pi
            MPI_Reduce(&temp_pi, &calc_pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

            if (rank == 0) { /* I am server */
                std::cout << "pi is approximately " << calc_pi
                          << ". Error is " << fabs(calc_pi - actual_pi) << std::endl
                          << "_______________________________________" << std::endl;
            }
        } // End else

        if (rank == 0) { /* I am root node */
            std::cout << "\nCompute with new intervals? (y/n)" << std::endl;
            std::cin >> response;
        }
    } // End while

    MPI_Finalize(); // Terminate MPI
    return 0;
} // End main