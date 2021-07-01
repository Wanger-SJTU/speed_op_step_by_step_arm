

#include "matmul.h"

#undef A
#undef B
#undef C
#define A(i, j) a[(j)*lda + (i)]
#define B(i, j) b[(j)*ldb + (i)]
#define C(i, j) c[(j)*ldc + (i)]

void matmul(int m, int k, int n, float *a, float *b, float *c) {

  int lda = m;
  int ldb = k;
  int ldc = m;

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j += 4) {
      C(i, j + 0) = 0;
      C(i, j + 1) = 0;
      C(i, j + 2) = 0;
      C(i, j + 3) = 0;
      for (int p = 0; p < k; p++) {
        C(i, j + 0) += A(i, p) * B(p, j + 0);
        C(i, j + 1) += A(i, p) * B(p, j + 1);
        C(i, j + 2) += A(i, p) * B(p, j + 2);
        C(i, j + 3) += A(i, p) * B(p, j + 3);
      }
    }
  }
}