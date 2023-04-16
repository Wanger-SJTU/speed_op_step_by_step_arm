
#include "matmul.h"
#include "parameters.h"

#include <math.h>

using namespace std;

void perf_one_pass(int m, int k, int n)
{
    float *a, *b, *c, *ref;
    int lda, ldb, ldc;
    malloc_matrix(m, n, k, &a, lda, &b, ldb, &c, ldc, &ref);

    memset(c, 0, m * n * sizeof(float));
    memset(ref, 0, m * n * sizeof(float));

    set_matrix_value(m, n, k, a, lda, b, ldb, c, ldc, ref);

    eval_gflops(m, k, n, a, lda, b, ldb, c, ldc);

    free(a);
    free(b);
    free(c);
}

int main(int argc, char *argv[])
{

#ifdef __arm__
    set_sched_affinity({7});
#endif
    int m = 64;
    for (int i = 0; i < 10; i += 1)
    {
        int value = pow(2, i);
        perf_one_pass(m * value, m * value, m * value);
    }

    return 0;
}