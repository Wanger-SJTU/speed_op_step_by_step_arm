
#include "matmul.h"
#include "parameters.h"

using namespace std;

float perf_one_pass(int m, int k, int n)
{
    float *a = new float[m * k]; // m * k
    float *b = new float[k * n]; // k * n
    float *c = new float[m * n]; // m * n
    memset(c, 0, m * n * sizeof(float));

    eval_gflops(m, k, n, a, b, c);
    delete[] a;
    delete[] b;
    delete[] c;
}

int main(int argc, char *argv[])
{

    //   set_sched_affinity({7});

    for (auto &m_k_n : parameters)
    {
        perf_one_pass(m_k_n[0], m_k_n[1], m_k_n[2]);
    }

    return 0;
}