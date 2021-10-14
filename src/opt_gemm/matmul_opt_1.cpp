
/* Create macros so that the matrices are stored in column-major order */
#include "matmul.h"

#define A(i, j) a[(j)*m + (i)]
#define B(i, j) b[(j)*k + (i)]
#define C(i, j) c[(j)*m + (i)]

#define Y(i) y[(i)*incx]

void AddDot(int k, float *x, int incx, float *y, float *out)
{
    /* compute out := x' * y + out with vectors x and y of length n.
       Here x starts at location x with increment (stride) incx and y starts at
       location y and has (implicit) stride of 1.
    */

    for (int p = 0; p < k; p++)
    {
        *out += x[p] * Y(p);
    }
}

/* Routine for computing C = A * B + C */
// colum-major
void matmul(int m, int k, int n, float *a, float *b, float *c)
{

    for (int i = 0; i < m; i++)
    { /* Loop over the rows of C */
        for (int j = 0; j < n; j++)
        { /* Loop over the columns of C */
            /* Update C(i,j) with the inner
                product of the ith
                row of A and the jth column of B */
            AddDot(k, &B(0, j), m, &A(i, 0), &C(i, j));
        }
    }
}
