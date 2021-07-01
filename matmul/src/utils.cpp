
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

void eval_gflops(int m, int k, int n, float *a, float *b, float *c) {

  double gflops = 2 * m * k * n * 1e-9;
  int run_cnt = 5000;

  printf("======== warm up ======\n");
  for (int i = 0; i < 50; ++i) {
    matmul(m, k, n, a, b, c);
  }
  printf("========== start ======\n");

  auto time = clock();
  for (int i = 0; i < run_cnt; ++i) {
    matmul(m, k, n, a, b, c);
  }
  time = clock() - time;
  // gettimeofday(&t2, nullptr);

  // double timeuse = (t2.tv_sec - t1.tv_sec);
  double timeuse = (time * 1.0) / CLOCKS_PER_SEC;

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