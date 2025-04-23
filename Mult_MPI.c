#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    long long total_factorial = 1;

    int n = 10; // Compute factorial of 10

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Calculate local factorial for each process
    long long local_factorial = 1;
    int chunk_size = n / size;
    int start = rank * chunk_size + 1;
    int end = (rank == size - 1) ? n : start + chunk_size - 1; // Last process handles any remaining numbers

    // Adjust the end for the last process to handle any remaining numb

    // Calculate the local factorial for the assigned range
    for (int i = start; i <= end; i++) {
        local_factorial *= i;
    }

    // Reduce all partial factorials to get the final result at rank 0
    MPI_Reduce(&local_factorial, &total_factorial, 1, MPI_LONG_LONG, MPI_PROD, 0, MPI_COMM_WORLD);

    // Rank 0 prints the result
    if (rank == 0) {
        printf("Factorial of %d is %lld\n", n, total_factorial);
    }

    MPI_Finalize();
    return 0;
}