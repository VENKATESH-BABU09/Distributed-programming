#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size, i, n = 10, local_sum = 0, total_sum = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Get process rank
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Get total number of processes

    int chunk = n / size;
    int start = rank * chunk + 1;
    int end = (rank == size - 1) ? n : start + chunk - 1;

    for (i = start; i <= end; i++) {
        local_sum += i;
    }

    // Collective communication: Reduce all local sums to total_sum at rank 0
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Sum of first %d numbers is %d\n", n, total_sum);
    }

    MPI_Finalize();
    return 0;
}