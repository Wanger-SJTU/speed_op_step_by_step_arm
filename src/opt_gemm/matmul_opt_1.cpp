
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
    AddDot(k, &A(0, 0), lda, &B(0, 0), &C(0, 0));
    AddDot(k, &A(0, 0), lda, &B(0, 0), &C(0, 0));
    AddDot(k, &A(0, 0), lda, &B(0, 0), &C(0, 0));
    AddDot(k, &A(0, 0), lda, &B(0, 0), &C(0, 0));
}

/* Routine for computing C = A * B + C */
// colum-major
void matmul(int m, int n, int k, float *a, int lda,
            float *b, int ldb,
            float *c, int ldc)
{

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j += 4)
        {
            AddDot(k, &B(0, j), m, &A(i, 0), &C(i, j));
            AddDot(k, &B(0, j + 1), m, &A(i, 0), &C(i, j + 1));
            AddDot(k, &B(0, j + 2), m, &A(i, 0), &C(i, j + 2));
            AddDot(k, &B(0, j + 3), m, &A(i, 0), &C(i, j + 3));
        }
    }
}
