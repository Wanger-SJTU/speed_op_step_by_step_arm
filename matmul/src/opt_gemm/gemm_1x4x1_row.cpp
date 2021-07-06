

#include "matmul.h"

#undef A
#undef B
#undef C

#define A(i, j) a[(j)*m + (i)]
#define B(i, j) b[(j)*k + (i)]
#define C(i, j) c[(j)*m + (i)]

// colum-major
void matmul(int m, int k, int n, float *a, float *b, float *c) {

  for (int j = 0; j < n; j++) {
    for (int i = 0; i < m; i += 4) {
      C(i + 0, j) = 0;
      C(i + 1, j) = 0;
      C(i + 2, j) = 0;
      C(i + 3, j) = 0;
      for (int p = 0; p < k; p++) {
        C(i + 0, j) += A(i + 0, p) * B(p, j);
        C(i + 1, j) += A(i + 1, p) * B(p, j);
        C(i + 2, j) += A(i + 2, p) * B(p, j);
        C(i + 3, j) += A(i + 3, p) * B(p, j);
      }
    }
  }
}