
#include "matmul.h"

#include <stdio.h>

#define A(i, j) a[(j)*lda + (i)]
#define B(i, j) b[(j)*ldb + (i)]
#define REF(i, j) ref[(j)*lda + (i)]

double dclock();

void print_matrix(int m, int n, float *a, int lda)
{
    int i, j;

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            // printf("%d %d %f    ", i + 1, j + 1, A(i, j));
            printf("%.0f ", A(i, j));
        }
        printf("\n");
    }
    printf("\n");
}

bool compare_matrix(int m, int n, float *a, float *ref, int lda)
{
    int i, j;
    double max_diff = 0.0, diff;

    for (j = 0; j < n; j++)
        for (i = 0; i < m; i++)
        {
            diff = abs(A(i, j) - REF(i, j));
            max_diff = (diff > max_diff ? diff : max_diff);
        }
    printf("%f \t", max_diff);
    return max_diff < 1e-6;
}

void set_matrix_value(int m, int n, int k, float *a, int lda,
                      float *b, int ldb,
                      float *c, int ldc, float *ref)
{
    for (int i = 0; i <= m * k; i++)
    {
        a[i] = 1;
    }
    for (int i = 0; i <= k * n; i++)
    {
        b[i] = 1;
    }
    for (int i = 0; i <= m * n; i++)
    {
        c[i] = 0;
        ref[i] = 0;
    }
}

void eval_gflops(int m, int n, int k, float *a, int lda,
                 float *b, int ldb,
                 float *c, int ldc)
{

    double gflops = (2 * m * k * n - 1) * 1e-9;
    int run_cnt = 200;

#ifdef __android__
    for (int i = 0; i < 5; ++i)
    {
        matmul(m, k, n, a, lda, b, ldb, c, ldc);
    }
#endif

    auto time = dclock();
    for (int i = 0; i < run_cnt; ++i)
    {
        matmul(m, k, n, a, lda, b, ldb, c, ldc);
    }
    double timeuse = dclock() - time;

    printf("M:%d K:%d N:%d GFLOPS:%.3f use time:%.3f ms \n", m, k, n,
           gflops * run_cnt / (timeuse + 1e-6), timeuse / run_cnt * 1000);
}

int set_sched_affinity(const std::vector<int> cpu_ids)
{

// set affinity for thread
#ifdef __GLIBC__
    pid_t pid = syscall(SYS_gettid);
#else
    pid_t pid = gettid();
#endif
    cpu_set_t mask;
    CPU_ZERO(&mask);
    for (int i = 0; i < cpu_ids.size(); ++i)
    {
        CPU_SET(cpu_ids[i], &mask);
    }
    int syscallret = syscall(__NR_sched_setaffinity, pid, sizeof(mask), &mask);
    if (syscallret)
    {
        return -1;
    }
    return 0;
}

void malloc_helper(int m, int n, void **ptr)
{
    *ptr = malloc(m * n * sizeof(float));

    if (ptr == nullptr)
    {
        printf("malloc failed\n");
        exit(-1);
    }
    else
    {
        printf("malloc %p \n", *ptr);
    }
}

void malloc_matrix(int m, int n, int k, float **a, int &lda,
                   float **b, int &ldb,
                   float **c, int &ldc,
                   float **ref)
{
    // #ifndef ALIGN
    //     malloc_helper(m, k, reinterpret_cast<void **>(a));
    //     malloc_helper(k, n, reinterpret_cast<void **>(b));
    //     malloc_helper(m, n, reinterpret_cast<void **>(c));
    //     malloc_helper(m, n, reinterpret_cast<void **>(ref));
    //     lda = m;
    //     ldb = k;
    //     ldc = m;
    // #else
    malloc_helper(m, n, reinterpret_cast<void **>(ref));
    malloc_helper(m, n, reinterpret_cast<void **>(c));
    malloc_helper(m, k, reinterpret_cast<void **>(a));
    malloc_helper(k, n, reinterpret_cast<void **>(b));
    lda = m;
    ldb = k;
    ldc = m;
    // #endif
    memset(*c, 0, m * n * sizeof(float));
    memset(*ref, 0, m * n * sizeof(float));
}