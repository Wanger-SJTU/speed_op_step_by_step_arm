
/* Create macros so that the matrices are stored in column-major order */
#include "matmul.h"

#define A(i, j) a[(j)*lda + (i)]
#define B(i, j) b[(j)*ldb + (i)]
#define C(i, j) c[(j)*ldc + (i)]

#define Y(i) y[(i)*incx]

void AddDot1x4(int m, float *x, int incx, float *y, float *out)
{
    for (int i = 0; i < m; i++)
    {
        out[i + incx * 0] += *(x + incx * 0) * y[i];
        out[i + incx * 1] += *(x + incx * 1) * y[i];
        out[i + incx * 2] += *(x + incx * 2) * y[i];
        out[i + incx * 3] += *(x + incx * 3) * y[i];
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
        for (int p = 0; p < k; p++) // m*k
        {
            AddDot1x4(m, &B(p, j + 0), lda, &A(0, p), &C(0, j + 0));
        }
    }
}
