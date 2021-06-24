
#include <stdio.h>
#include <string>
#include <sys/time.h>

#include "matmul.h"

using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 4) {
    printf("too few args\n");
    return 0;
  }

  int params[3];
  for (int i = 1; i < 4; ++i) {
    params[i - 1] = stoi(argv[i]);
  }

  float *a = new float[params[0] * params[1]];
  float *b = new float[params[1] * params[2]];
  float *c = new float[params[0] * params[2]];

  double flops = params[0] * params[2] * (2 * params[1] - 1);
  int run_cnt = 2000;
  struct timeval t1, t2;

  gettimeofday(&t1, nullptr);
  for (int i = 0; i < 20; ++i) {
    matmul(params[0], params[1], params[2], a, b, c);
  }
  for (int i = 0; i < run_cnt; ++i) {
    matmul(params[0], params[1], params[2], a, b, c);
  }
  gettimeofday(&t2, nullptr);

  double timeuse = (t2.tv_sec - t1.tv_sec);

  printf("===========result=======\n");
  printf(" use time   |   %.3f ms     \n", timeuse / run_cnt * 1000);
  printf(" GFLOPS     |   %.3f     \n", flops / (timeuse / run_cnt) * 1e-9);
  printf("===========end==========\n");

  delete[] a;
  delete[] b;
  delete[] c;

  return 0;
}