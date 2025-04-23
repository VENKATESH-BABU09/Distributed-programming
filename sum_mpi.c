#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int rank, size, n, local_sum = 0, global_sum = 0;

    MPI_Init(&argc, &argv);                 // Initialize MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   // Get process rank
    MPI_Comm_size(MPI_COMM_WORLD, &size);   // Get total number of processes

    if (rank == 0) {
        printf("Enter the value of n: ");
        scanf("%d", &n);
    }

    // Broadcast n to all processes
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    // int MPI_Bcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm);

    // Determine the range of numbers each process will handle
    int start = rank * (n / size) + 1;
    int end = (rank == size - 1) ? n : (rank + 1) * (n / size);

    for (int i = start; i <= end; i++) {
        local_sum += i;
    }

    // Reduce all local sums into the global sum at rank 0
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    // int MPI_Reduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm);


    if (rank == 0) {
        printf("Sum of first %d natural numbers is %d\n", n, global_sum);
    }

    MPI_Finalize();
    return 0;
}
