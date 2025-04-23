#include <stdio.h>
#include <omp.h>

#define N 4

int main() {
    int A[N][N], B[N][N], C[N][N];

    // Initialize matrices A and B
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

    // Parallel matrix addition
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    // Print result
    printf("\nMatrix C (A + B):\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%3d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
