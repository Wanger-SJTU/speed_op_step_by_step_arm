
#include "inc.h"

#include <chrono>
#include <iostream>
using namespace std;

int main()
{
    for (int mkn = 32; mkn <= 1024; mkn *= 2)
    {
        float *a, *b, *c;
        a = new float[mkn * mkn];
        b = new float[mkn * mkn];
        c = new float[mkn * mkn];
        double gflops = (2 * (double)mkn * mkn * mkn ) * 1e-9;
        auto time_span = std::chrono::duration<double, std::micro>::max().count();
        for (int i = 0; i < 10; ++i)
        {
            auto start = std::chrono::high_resolution_clock::now();
            matmul(a, b, c, mkn, mkn, mkn);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::micro> dur = end - start;
            time_span = dur.count() < time_span ? dur.count() : time_span;
        }
        std::cout << "mkn:" << mkn << " FLOPs:" << gflops
                  << " time:" << time_span << " GFLOPS:" << gflops / (time_span /1000000) << endl;
        delete a;
        delete b;
        delete c;
    }
    return 0;
}