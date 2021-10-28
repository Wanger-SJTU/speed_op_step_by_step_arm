
/* Create macros so that the matrices are stored in column-major order */
#include <stdio.h>

#include "matmul.h"

#undef A
#undef B
#undef C
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
// col-major
void matmul(int m, int n, int k,
            float *a, int lda,
            float *b, int ldb,
            float *c, int ldc)
{
    int i, j, p;

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            AddDot(k, &B(0, j), lda, &A(i, 0), &C(i, j));
        }
    }
}
