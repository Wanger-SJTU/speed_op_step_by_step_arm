
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

    for (int i = 0; i < m; i += 4)
    {
        for (int j = 0; j < n; j += 4)
        {
            AddDot(k, &B(0, j + 0), ldb, &A(i + 0, 0), &C(i + 0, j + 0));
            AddDot(k, &B(0, j + 1), ldb, &A(i + 0, 0), &C(i + 0, j + 1));
            AddDot(k, &B(0, j + 2), ldb, &A(i + 0, 0), &C(i + 0, j + 2));
            AddDot(k, &B(0, j + 3), ldb, &A(i + 0, 0), &C(i + 0, j + 3));

            AddDot(k, &B(0, j + 0), ldb, &A(i + 1, 0), &C(i + 1, j + 0));
            AddDot(k, &B(0, j + 1), ldb, &A(i + 1, 0), &C(i + 1, j + 1));
            AddDot(k, &B(0, j + 2), ldb, &A(i + 1, 0), &C(i + 1, j + 2));
            AddDot(k, &B(0, j + 3), ldb, &A(i + 1, 0), &C(i + 1, j + 3));

            AddDot(k, &B(0, j + 0), ldb, &A(i + 2, 0), &C(i + 2, j + 0));
            AddDot(k, &B(0, j + 1), ldb, &A(i + 2, 0), &C(i + 2, j + 1));
            AddDot(k, &B(0, j + 2), ldb, &A(i + 2, 0), &C(i + 2, j + 2));
            AddDot(k, &B(0, j + 3), ldb, &A(i + 2, 0), &C(i + 2, j + 3));

            AddDot(k, &B(0, j + 0), ldb, &A(i + 3, 0), &C(i + 3, j + 0));
            AddDot(k, &B(0, j + 1), ldb, &A(i + 3, 0), &C(i + 3, j + 1));
            AddDot(k, &B(0, j + 2), ldb, &A(i + 3, 0), &C(i + 3, j + 2));
            AddDot(k, &B(0, j + 3), ldb, &A(i + 3, 0), &C(i + 3, j + 3));
        }
    }
}
