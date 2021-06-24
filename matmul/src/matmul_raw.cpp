
/* Create macros so that the matrices are stored in column-major order */

#include "matmul.h"

/* Routine for computing C = A * B + C */

void matmul(int m, int n, int k, float *a, float *b, float *c) {
  int i, j, p;
  int lda = m;
  int ldb = k;
  int ldc = m;

  for (i = 0; i < m; i++) {   /* Loop over the rows of C */
    for (j = 0; j < n; j++) { /* Loop over the columns of C */
      for (p = 0; p < k; p++) {
        /* Update C(i,j) with the inner
            product of the ith
            row of A and the jth column of B */
        C(i, j) = C(i, j) + A(i, p) * B(p, j);
      }
    }
  }
}
