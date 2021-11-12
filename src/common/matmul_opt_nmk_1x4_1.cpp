
/* Create macros so that the matrices are stored in column-major order */
#include "matmul.h"

#define A(i, j) a[(j)*lda + (i)]
#define B(i, j) b[(j)*ldb + (i)]
#define C(i, j) c[(j)*ldc + (i)]

#define Y(i) y[(i)*incx]

void AddDot(int k, float *x, int incx, float *y, float *out)
{
    for (int p = 0; p < k; p++)
    {
        *out += x[p] * Y(p);
    }
}

/* Routine for computing C = A * B + C */
// colum-major
void matmul(int m, int n, int k, float *a, int lda,
            float *b, int ldb,
            float *c, int ldc)
{
    for (int j = 0; j < n; j += 4) // k*n
    {
        for (int i = 0; i < m; i++) // m*k
        {
            AddDot(k, &B(0, j + 0), lda, &A(i, 0), &C(i, j + 0));
            AddDot(k, &B(0, j + 1), lda, &A(i, 0), &C(i, j + 1));
            AddDot(k, &B(0, j + 2), lda, &A(i, 0), &C(i, j + 2));
            AddDot(k, &B(0, j + 3), lda, &A(i, 0), &C(i, j + 3));
        }
    }
}
