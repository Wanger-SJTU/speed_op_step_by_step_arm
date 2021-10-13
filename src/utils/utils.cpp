
#include "matmul.h"
#include <stdio.h>

#define A(i, j) a[(j)*m + (i)]
#define B(i, j) b[(j)*m + (i)]

double dclock();

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

bool compare_matrix(int m, int n, float *a, float *b) {
  int i, j;
  double max_diff = 0.0, diff;

  for (j = 0; j < n; j++)
    for (i = 0; i < m; i++) {
      diff = abs(A(i, j) - B(i, j));
      max_diff = (diff > max_diff ? diff : max_diff);
    }

  return max_diff < 1e-6;
}

void set_matrix_value(int m, int n, float *a) {
  int i, j = 1;
  for (i = 1; i <= m * n; i++) {
    a[i - 1] = j;
    if ((i) % m == 0)
      j++;
  }
}

bool test_acc(int m, int k, int n) {

  float *a = new float[m * k]; // m * k
  float *b = new float[k * n]; // k * n
  float *c = new float[m * n]; // m * n
  memset(c, 0, m * n * sizeof(float));

  set_matrix_value(m, k, a);
  set_matrix_value(k, n, b);
  print_matrix(m, k, a);
  print_matrix(k, n, b);
  matmul(m, k, n, a, b, c);
  print_matrix(m, n, c);
  return true;
}

void eval_gflops(int m, int k, int n, float *a, float *b, float *c) {

  double gflops = (2 * m * k * n - 1) * 1e-9;
  int run_cnt = 200;

  for (int i = 0; i < 50; ++i) {
    matmul(m, k, n, a, b, c);
  }

  auto time = dclock();
  for (int i = 0; i < run_cnt; ++i) {
    matmul(m, k, n, a, b, c);
  }
  double timeuse = dclock() - time;

  printf("===========result=======\n");
  printf(" use time   | %.3f ms     \n", timeuse / run_cnt * 1000);
  printf(" GFLOPS     | %.3f     \n", gflops * run_cnt / (timeuse + 1e-6));
  printf("===========end==========\n");
}

int set_sched_affinity(const std::vector<int> cpu_ids) {

// set affinity for thread
#ifdef __GLIBC__
  pid_t pid = syscall(SYS_gettid);
#else
  pid_t pid = gettid();
#endif
  cpu_set_t mask;
  CPU_ZERO(&mask);
  for (int i = 0; i < cpu_ids.size(); ++i) {
    CPU_SET(cpu_ids[i], &mask);
  }
  int syscallret = syscall(__NR_sched_setaffinity, pid, sizeof(mask), &mask);
  if (syscallret) {
    return -1;
  }
  return 0;
}