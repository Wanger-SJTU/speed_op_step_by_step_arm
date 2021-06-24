#define A(i, j) a[(j)*lda + (i)]
#define B(i, j) b[(j)*ldb + (i)]
#define C(i, j) c[(j)*ldc + (i)]

/* Routine for computing C = A * B + C */

void matmul(int m, int n, int k, float *a, float *b, float *c);