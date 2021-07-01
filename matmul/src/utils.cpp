#include "matmul.h"
#include <stdio.h>

#define A(i, j) a[(j)*m + (i)]

void print_matrix(int m, int n, float *a) {
  int i, j;

  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      // printf("%d %d %f    ", i + 1, j + 1, A(i, j));
      printf("%.0f ", A(i, j));
    }
    printf("\n");
  }
  printf("\n");
}

void set_matrix_value(int m, int n, float *a) {
  int i, j = 1;
  for (i = 1; i <= m * n; i++) {
    a[i - 1] = j;
    if ((i) % m == 0)
      j++;
  }
}

void test_acc(int m, int k, int n, float *a, float *b, float *c) {

  set_matrix_value(m, k, a);
  set_matrix_value(k, n, b);
  print_matrix(m, k, a);
  print_matrix(k, n, b);
  matmul(m, k, n, a, b, c);
  print_matrix(m, n, c);
}