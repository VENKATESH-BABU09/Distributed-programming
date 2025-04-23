//omp_sum_n_numbers
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int i, n = 10, sum = 0;

    // Set number of threads
    omp_set_num_threads(4);

    // Use reduction to avoid race condition
    #pragma omp parallel for reduction(+:sum)
    for (i = 1; i <= n; i++) {
        int tid = omp_get_thread_num();
        printf("Thread %d: adding %d\n", tid, i);
        sum += i;
    }

    printf("Final sum = %d\n", sum);
    return 0;
}
