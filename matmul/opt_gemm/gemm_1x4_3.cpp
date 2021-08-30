/* Create macros so that the matrices are stored in column-major order */

#define A(i, j) a[(j)*m + (i)]
#define B(i, j) b[(j)*k + (i)]
#define C(i, j) c[(j)*m + (i)]

/* Routine for computing C = A * B + C */

void AddDot(int, float *, int, float *, float *);
void AddDot1x4(int, float *, int, float *, int, float *, int);

void MY_MMult(int m, int k, int n, float *a, float *b, float *c) {
  int i, j;

  for (j = 0; j < n; j += 4) {   /* Loop over the columns of C, unrolled by 4 */
    for (i = 0; i < m; i += 1) { /* Loop over the rows of C */
      /* Update C( i,j ), C( i,j+1 ), C( i,j+2 ), and C( i,j+3 ) in
         one routine (four inner products) */

      AddDot1x4(m, k, n, &A(i, 0), &B(0, j), &C(i, j));
    }
  }
}

void AddDot1x4(int m, int k, int n, float *a, float *b, float *c) {
  /* So, this routine computes four elements of C:

           C( 0, 0 ), C( 0, 1 ), C( 0, 2 ), C( 0, 3 ).

     Notice that this routine is called with c = C( i, j ) in the
     previous routine, so these are actually the elements

           C( i, j ), C( i, j+1 ), C( i, j+2 ), C( i, j+3 )

     in the original matrix C */

  AddDot(k, &A(0, 0), m, &B(0, 0), &C(0, 0));
  AddDot(k, &A(0, 0), m, &B(0, 1), &C(0, 1));
  AddDot(k, &A(0, 0), m, &B(0, 2), &C(0, 2));
  AddDot(k, &A(0, 0), m, &B(0, 3), &C(0, 3));
}

/* Create macro to let X( i ) equal the ith element of x */

#define X(i) x[(i)*incx]

void AddDot(int k, float *x, int incx, float *y, float *gamma) {
  /* compute gamma := x' * y + gamma with vectors x and y of length n.

     Here x starts at location x with increment (stride) incx and y starts at
     location y and has (implicit) stride of 1.
  */

  int p;

  for (p = 0; p < k; p++) {
    *gamma += X(p) * y[p];
  }
}
