#include <stdio.h> 
#include <omp.h> 
int main() { 
 int n = 5; 
 long long sum_seq = 1, sum_par = 1;  
//  double start_time_seq = omp_get_wtime(); 
 for (int i = 1; i <= n; i++)  
 sum_seq *= i ; 
//  double end_time_seq = omp_get_wtime(); 
//  double start_time_par = omp_get_wtime(); 
 #pragma omp parallel for reduction(*:sum_par) 
 for (int i = 1; i <= n; i++)  
 sum_par *= i ; 
//  double end_time_par = omp_get_wtime(); 
 printf("Sequential Sum: %lld\n", sum_seq); 
//  printf("Execution time (Sequential): %f seconds\n", end_time_seq - start_time_seq); 
 printf("Parallel Sum: %lld\n", sum_par); 
//  printf("Execution time (Parallel): %f seconds\n", end_time_par - start_time_par); 
 return 0; 
}