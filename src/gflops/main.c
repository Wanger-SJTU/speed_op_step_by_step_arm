

#define __USE_GNU

#include <sched.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include <sys/types.h>

#include <time.h>
#include <stdio.h>
#include <syscall.h>

#define LOOP (1e9)
#define OP_FLOATS (96)

void func2(int);

int set_cpu_core(int core_idx)
{

    cpu_set_t mask;
    CPU_ZERO(&mask);

    CPU_SET(core_idx, &mask);

    if (sched_setaffinity(0, sizeof(mask), &mask) < 0)
    {
        return -1;
    }
    return 0;
}

static double get_time(struct timespec *start,
                       struct timespec *end)
{
    return end->tv_sec - start->tv_sec + (end->tv_nsec - start->tv_nsec) * 1e-9;
}

int main()
{
    struct timespec start, end;
    double time_used = 0.0;
    set_cpu_core(7);
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    func2(LOOP);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    time_used = get_time(&start, &end);
    printf("perf: %.6lf \n", LOOP * OP_FLOATS * 1.0 * 1e-9 / time_used);
}