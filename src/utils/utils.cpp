
#include "matmul.h"

#include <stdio.h>
#include <random>

#ifdef ENABLE_ARM64
#include <linux/perf_event.h>
#include <sys/ioctl.h>
#include <asm/unistd.h>
#include <unistd.h>
#endif

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
    std::random_device rd;
    std::mt19937 mt(rd());

    for (int i = 0; i <= m * k; i++)
    {
        a[i] = mt();
    }

    for (int i = 0; i <= k * n; i++)
    {
        b[i] = mt();
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

#ifdef __arm__
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

int InitPerfProfilingCallbackParameter()
{
#ifndef ENABLE_ARM64
    return -1;
#else
    struct perf_event_attr pe, pe2;
    memset(&pe, 0, sizeof(struct perf_event_attr));
    memset(&pe2, 0, sizeof(struct perf_event_attr));
    pe.type = PERF_TYPE_HARDWARE;
    pe2.type = PERF_TYPE_HARDWARE;
    pe.size = sizeof(struct perf_event_attr);
    pe2.size = sizeof(struct perf_event_attr);
    pe.disabled = 1;
    pe2.disabled = 1;
    pe.exclude_kernel = 1;  // don't count kernel
    pe2.exclude_kernel = 1; // don't count kernel
    pe.exclude_hv = 1;      // don't count hypervisor
    pe2.exclude_hv = 1;     // don't count hypervisor
    pe.read_format = PERF_FORMAT_GROUP | PERF_FORMAT_ID;
    pe2.read_format = PERF_FORMAT_GROUP | PERF_FORMAT_ID;
    if (flags_->perf_event_ == "CACHE")
    {
        pe.config = PERF_COUNT_HW_CACHE_REFERENCES;
        pe2.config = PERF_COUNT_HW_CACHE_MISSES;
    }
    else if (flags_->perf_event_ == "STALL")
    {
        pe.config = PERF_COUNT_HW_STALLED_CYCLES_FRONTEND;
        pe2.config = PERF_COUNT_HW_STALLED_CYCLES_BACKEND;
    }
    else
    {
        pe.config = PERF_COUNT_HW_CPU_CYCLES;
        pe2.config = PERF_COUNT_HW_INSTRUCTIONS;
    }
    perf_fd = syscall(__NR_perf_event_open, pe, 0, -1, -1, 0);
    if (perf_fd == -1)
    {
        cout << "ERROR"
             << "Failed to open perf event " << pe.config;
        return RET_ERROR;
    }
    perf_fd2 = syscall(__NR_perf_event_open, pe2, 0, -1, perf_fd, 0);
    if (perf_fd2 == -1)
    {
        cout << "ERROR"
             << "Failed to open perf event " << pe2.config;
        return RET_ERROR;
    }
    struct PerfCount zero;
    zero.value[0] = 0;
    zero.value[1] = 0;
    // before callback

    before_call_back_ = [&](const CallBackParam &call_param)
    {
        if (op_perf_by_type_.find(call_param.node_type) == op_perf_by_type_.end())
        {
            op_perf_by_type_.insert(std::make_pair(call_param.node_type, std::make_pair(0, zero)));
        }
        if (op_perf_by_name_.find(call_param.node_name) == op_perf_by_name_.end())
        {
            op_perf_by_name_.insert(std::make_pair(call_param.node_name, std::make_pair(0, zero)));
        }

        op_call_times_total_++;
        ioctl(perf_fd, PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP);
        ioctl(perf_fd, PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP);
        return true;
    };

    // after callback
    after_call_back_ = [&](const CallBackParam &call_param)
    {
        struct PerfResult res;
        ioctl(perf_fd, PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP);
        if (read(perf_fd, &res, sizeof(struct PerfResult)) == -1)
        {
            cout << "ERROR"
                 << "Failed to read perf_fd";
            return false;
        }

        float cost1 = static_cast<float>(res.values[0].value);
        float cost2 = static_cast<float>(res.values[1].value);
        op_cost_total_ += cost1;
        op_cost2_total_ += cost2;
        op_perf_by_type_[call_param.node_type].first++;
        op_perf_by_type_[call_param.node_type].second.value[0] += cost1;
        op_perf_by_type_[call_param.node_type].second.value[1] += cost2;
        op_perf_by_name_[call_param.node_name].first++;
        op_perf_by_name_[call_param.node_name].second.value[0] += cost1;
        op_perf_by_name_[call_param.node_name].second.value[1] += cost2;
        return true;
    };
#endif
    return 0;
}

void* aligned_malloc(size_t required_bytes, size_t alignment)
{
    int offset = alignment - 1 + sizeof(void*);
    void* p1 = (void*)malloc(required_bytes + offset);
    if (p1 == nullptr)
        return nullptr;
    void** p2 = (void**)( ( (size_t)p1 + offset ) & ~(alignment - 1) );
    p2[-1] = p1;
    return p2;
}
 
void aligned_free(void *p2)
{
    void* p1 = ((void**)p2)[-1];
    free(p1);
}