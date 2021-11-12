
#include "matmul.h"
#include "parameters.h"

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

    // set_sched_affinity({7});
    int m = 4;
    for (int i = 2; i < 256; i += 1)
    {
        perf_one_pass(m * i, m * i, m * i);
    }

    return 0;
}