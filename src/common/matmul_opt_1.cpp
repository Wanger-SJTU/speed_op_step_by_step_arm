
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

void AddDot_1x4(int k, float *a, int lda, float *b, int ldb, float *c, int ldc)
{
    AddDot(k, &B(0, 0), ldb, &A(0, 0), &C(0, 0));
    AddDot(k, &B(0, 0), ldb, &A(0, 1), &C(0, 1));
    AddDot(k, &B(0, 0), ldb, &A(0, 2), &C(0, 2));
    AddDot(k, &B(0, 0), ldb, &A(0, 3), &C(0, 3));
}

/* Routine for computing C = A * B + C */
// colum-major
void matmul(int m, int n, int k, float *a, int lda,
            float *b, int ldb,
            float *c, int ldc)
{

    for (int i = 0; i < m; i++) // m*k
    {
        for (int j = 0; j < n; j += 4) // k*n
        {
            AddDot(k, &B(j + 0, 0), lda, &A(0, i), &C(i, j + 0));
            AddDot(k, &B(j + 1, 0), lda, &A(0, i), &C(i, j + 1));
            AddDot(k, &B(j + 2, 0), lda, &A(0, i), &C(i, j + 2));
            AddDot(k, &B(j + 3, 0), lda, &A(0, i), &C(i, j + 3));
        }
    }
}
