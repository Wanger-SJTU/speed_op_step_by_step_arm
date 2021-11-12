
/* Create macros so that the matrices are stored in column-major order */
#include "matmul.h"

#define A(i, j) a[(j)*lda + (i)]
#define B(i, j) b[(j)*ldb + (i)]
#define C(i, j) c[(j)*ldc + (i)]

#define Y(i) y[(i)*incx]

void AddDot_1x8(int k, float *a, int lda, float *b, int ldb, float *c, int ldc)
{
    for (int p = 0; p < k; p++)
    {
        C(0, 0) += A(0, p) * B(p, 0);
        C(0, 1) += A(0, p) * B(p, 1);
        C(0, 2) += A(0, p) * B(p, 2);
        C(0, 3) += A(0, p) * B(p, 3);
        C(0, 4) += A(0, p) * B(p, 4);
        C(0, 5) += A(0, p) * B(p, 5);
        C(0, 6) += A(0, p) * B(p, 6);
        C(0, 7) += A(0, p) * B(p, 7);
    }
}

void AddDot_1x4(int k, float *a, int lda, float *b, int ldb, float *c, int ldc)
{
    for (int p = 0; p < k; p++)
    {
        C(0, 0) += A(0, p) * B(p, 0);
        C(0, 1) += A(0, p) * B(p, 1);
        C(0, 2) += A(0, p) * B(p, 2);
        C(0, 3) += A(0, p) * B(p, 3);
    }
}

/* Routine for computing C = A * B + C */
// colum-major
void matmul(int m, int n, int k, float *a, int lda,
            float *b, int ldb,
            float *c, int ldc)
{
    int j = 0;
    for (; j < (n - n % 8); j += 8) // k*n
    {
        for (int i = 0; i < m; i++) // m*k
        {
            AddDot_1x8(k, &A(i, 0), lda, &B(0, j), ldb, &C(i, j), ldc);
        }
    }
    for (; j < (n - n % 4); j += 4) // k*n
    {
        for (int i = 0; i < m; i++) // m*k
        {
            AddDot_1x4(k, &A(i, 0), lda, &B(0, j), ldb, &C(i, j), ldc);
        }
    }
}
