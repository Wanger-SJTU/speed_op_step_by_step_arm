
#include <chrono>
#include <iostream>

#define A(i, j) a[i  + j* m] // m * k
#define B(i, j) a[i  + j* k] // k * n
#define C(i, j) a[i  + j* m] // m * n

using namespace std;

void matmul(float *a, float *b, float *c, int m, int n, int k)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j += 4)
        {
            for (int r = 0; r < k; r++)
            {
                C(i, j + 0) += A(i, r) * B(r, j + 0);
                C(i, j + 1) += A(i, r) * B(r, j + 1);
                C(i, j + 2) += A(i, r) * B(r, j + 2);
                C(i, j + 3) += A(i, r) * B(r, j + 3);
            }
        }
    }
}

int main()
{
    for (int mkn = 32; mkn <= 1024; mkn *= 2)
    {
        float *a, *b, *c;
        a = new float[mkn * mkn];
        b = new float[mkn * mkn];
        c = new float[mkn * mkn];
        double gflops = (2 * mkn * mkn * mkn ) * 1e-9;
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
}