
#include <stdio.h>
#include <string>
#include <sys/time.h>
#include <vector>

#include <stdint.h>
#include <sys/syscall.h>
#include <unistd.h>

#include "matmul.h"

using namespace std;

int set_sched_affinity(const std::vector<int> cpu_ids) {
// #define CPU_SETSIZE 1024
// #define __NCPUBITS  (8 * sizeof (unsigned long))
// typedef struct
// {
//    unsigned long __bits[CPU_SETSIZE / __NCPUBITS];
// } cpu_set_t;

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

int main(int argc, char *argv[]) {
  if (argc < 4) {
    printf("too few args\n");
    return 0;
  }

  set_sched_affinity({7});

  int params[3];
  for (int i = 1; i < 4; ++i) {
    params[i - 1] = stoi(argv[i]);
  }

  float *a = new float[params[0] * params[1]];
  float *b = new float[params[1] * params[2]];
  float *c = new float[params[0] * params[2]];

  double flops = params[0] * params[2] * (2 * params[1] - 1);
  int run_cnt = 20000;
  struct timeval t1, t2;

  for (int i = 0; i < 50; ++i) {
    matmul(params[0], params[1], params[2], a, b, c);
  }
  gettimeofday(&t1, nullptr);
  for (int i = 0; i < run_cnt; ++i) {
    matmul(params[0], params[1], params[2], a, b, c);
  }
  gettimeofday(&t2, nullptr);

  double timeuse = (t2.tv_sec - t1.tv_sec);

  printf("===========result=======\n");
  printf(" use time   |   %.3f ms     \n", timeuse / run_cnt * 1000);
  printf(" GFLOPS     |   %.3f     \n", flops * run_cnt / (timeuse)*1e-9);
  printf("===========end==========\n");

  delete[] a;
  delete[] b;
  delete[] c;

  return 0;
}