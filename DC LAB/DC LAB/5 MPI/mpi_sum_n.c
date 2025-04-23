#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    int rank, nprocs;
    int n = 100;          // Sum from 1 to n
    int local_sum = 0;    // Each process's partial sum
    int total_sum = 0;

    MPI_Init(&argc, &argv);  
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);  
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  

    // Divide range of numbers among processes
    int chunk = n / nprocs;
    int start = rank * chunk + 1;
    int end = (rank == nprocs - 1) ? n : (rank + 1) * chunk;

    // Each process computes its partial sum
    for (int i = start; i <= end; i++) {
        local_sum += i;
    }

    // Reduce all partial sums into total_sum at root process (rank 0)
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Only rank 0 prints the final result
    if (rank == 0) {
        printf("Sum of numbers from 1 to %d is %d\n", n, total_sum);
    }

    MPI_Finalize();  
    return 0;  
}
