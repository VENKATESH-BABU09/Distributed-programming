#include <stdio.h>
#include <mpi.h>

#define N 4  // Size of matrix (N x N)

int main(int argc, char* argv[]) {
    int rank, size;
    int A[N][N], B[N][N], C[N][N];
    int rows_per_process;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    rows_per_process = N / size;

    int local_A[rows_per_process][N], local_B[rows_per_process][N], local_C[rows_per_process][N];

    if (rank == 0) {
        // Initialize matrices A and B with sample values
        printf("Matrix A:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                A[i][j] = i + j;
                B[i][j] = i * j;
                printf("%3d ", A[i][j]);
            }
            printf("\n");
        }

        printf("\nMatrix B:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%3d ", B[i][j]);
            }
            printf("\n");
        }
    }

    // Scatter rows of matrices A and B to all processes
    MPI_Scatter(A, rows_per_process * N, MPI_INT, local_A, rows_per_process * N, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(B, rows_per_process * N, MPI_INT, local_B, rows_per_process * N, MPI_INT, 0, MPI_COMM_WORLD);

    // Perform addition of corresponding rows
    for (int i = 0; i < rows_per_process; i++) {
        for (int j = 0; j < N; j++) {
            local_C[i][j] = local_A[i][j] + local_B[i][j];
        }
    }

    // Gather the local_C matrices to form the final result in matrix C
    MPI_Gather(local_C, rows_per_process * N, MPI_INT, C, rows_per_process * N, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("\nResultant Matrix C (A + B):\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%3d ", C[i][j]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();
    return 0;
}
