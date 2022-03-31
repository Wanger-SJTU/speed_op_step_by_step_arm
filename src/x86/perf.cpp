
#include "inc.h"
#include <chrono>

int main()
{
    for (int mkn = 32; mkn <= 2048; mkn += 32)
    {
        float *a, *b, *c;
        a = static_cast<float*>(aligned_malloc(mkn * mkn * sizeof(float), 128));
        b = static_cast<float*>(aligned_malloc(mkn * mkn * sizeof(float), 128));
        c = static_cast<float*>(aligned_malloc(mkn * mkn * sizeof(float), 128));

        double gflops = (2 * (double)mkn * mkn * mkn) * 1e-9;
        std::cout << "mkn:" << mkn << " FLOPs:" << gflops << flush;
        auto time_span = std::chrono::duration<double, std::micro>::max().count();
        for (int i = 0; i < 5; ++i)
        {
            auto start = std::chrono::high_resolution_clock::now();
            matmul(a, b, c, mkn, mkn, mkn);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::micro> dur = end - start;
            time_span = dur.count() < time_span ? dur.count() : time_span;
        }
        std::cout << " time:" << time_span << " GFLOPS:" << gflops / (time_span /1000000) << endl;
        aligned_free(a);
        aligned_free(b);
        aligned_free(c);
    }
    return 0;
}