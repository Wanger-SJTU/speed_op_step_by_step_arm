
#include "matmul.h"

using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 4) {
    printf("too few args\n");
    return 0;
  }

  set_sched_affinity({7});

  int params[3]; // m k n
  for (int i = 1; i < 4; ++i) {
    params[i - 1] = stoi(argv[i]);
  }

  float *a = new float[params[0] * params[1]]; // m * k
  float *b = new float[params[1] * params[2]]; // k * n
  float *c = new float[params[0] * params[2]]; // m * n
  memset(c, 0, params[0] * params[2] * sizeof(float));

  eval_gflops(params[0], params[1], params[2], a, b, c);
  delete[] a;
  delete[] b;
  delete[] c;

  return 0;
}