
/* Create macros so that the matrices are stored in column-major order */
#include "matmul.h"

#define A(i, j) a[(j)*m + (i)]
#define B(i, j) b[(j)*k + (i)]
#define C(i, j) c[(j)*m + (i)]

#define X(i) x[(i)*incx]

void AddDot(int k, float *x, int incx, float *y, float *out)
{
    /* compute out := x' * y + out with vectors x and y of length n.
       Here x starts at location x with increment (stride) incx and y starts at
       location y and has (implicit) stride of 1.
    */

    for (int p = 0; p < k; p++)
    {
        *out += X(p) * y[p];
    }
}

/* Routine for computing C = A * B + C */
// colum-major
void matmul(int m, int k, int n, float *a, float *b, float *c)
{

    for (int j = 0; j < n; j++)
    { /* Loop over the columns of C */
        for (int i = 0; i < m; i += 4)
        { /* Loop over the rows of C */
            /* Update C(i,j) with the inner
                product of the ith
                row of A and the jth column of B */

            AddDot(k, &A(i, 0), m, &B(0, j), &C(i, j));

            /* Update the C( i,j+1 ) with the inner product of the ith row of A
               and the (j+1)th column of B */

            AddDot(k, &A(i + 1, 0), m, &B(0, j), &C(i + 1, j));

            /* Update the C( i,j+2 ) with the inner product of the ith row of A
               and the (j+2)th column of B */

            AddDot(k, &A(i + 2, 0), m, &B(0, j), &C(i + 2, j));

            /* Update the C( i,j+3 ) with the inner product of the ith row of A
               and the (j+1)th column of B */

            AddDot(k, &A(i + 3, 0), m, &B(0, j), &C(i + 3, j));
        }
    }
}
