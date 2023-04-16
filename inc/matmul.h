
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/syscall.h>
#include <sys/time.h>
#include <unistd.h>
#include <vector>

/* Routine for computing C = A * B + C */
/*
  suppose a b c are col-major
  then A[i,j] = A[(j) * row + i]
*/

void matmul_ref(int m, int n, int k, float *a, int lda,
                float *b, int ldb,
                float *c, int ldc);

void print_matrix(int m, int n, float *a, int lda);
bool compare_matrix(int m, int n, float *a, float *ref, int lda);
void set_matrix_value(int m, int n, int k, float *a, int lda,
                      float *b, int ldb,
                      float *c, int ldc, float *ref);

void eval_gflops(int m, int n, int k, float *a, int lda,
                 float *b, int ldb,
                 float *c, int ldc);

int set_sched_affinity(const std::vector<int> cpu_ids);

void malloc_matrix(int m, int n, int k, float **a, int &lda,
                   float **b, int &ldb,
                   float **c, int &ldc, float **ref);

void matmul(int m, int n, int k, float *a, int lda,
            float *b, int ldb,
            float *c, int ldc);

void* aligned_malloc(size_t required_bytes, size_t alignment);
void aligned_free(void *p2);

