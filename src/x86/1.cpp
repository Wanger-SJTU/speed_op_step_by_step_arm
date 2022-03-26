
#include <chrono>
#include <iostream>

#define A(i, j) a[i * m + j] // m * k
#define B(i, j) a[i * k + j] // k * n
#define C(i, j) a[i * m + j] // m * n

using namespace std;

void matmul(float *a, float *b, float *c, int m, int n, int k)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j+=4)
        {
            for (int r = 0; r < k; r++)
            {
                C(i, j) += A(i, r) * B(r, j+0);
                C(i, j) += A(i, r) * B(r, j+1);
                C(i, j) += A(i, r) * B(r, j+2);
                C(i, j) += A(i, r) * B(r, j+3);
            }
        }
    }
}
int main()
{
    for(int mkn = 32; mkn <= 1024; mkn *= 2)
    {
        float *a, *b, *c;
        a = new float[mkn * mkn];
        b = new float[mkn * mkn];
        c = new float[mkn * mkn];
        double gflops = (2 * mkn * mkn * mkn - 1) * 1e-9;
        auto time_span = std::chrono::duration<double, std::milli>::max().count();
        for(int i = 0; i < 10; ++i)
        {   
            auto start = std::chrono::high_resolution_clock::now();
            matmul(a, b, c, mkn, mkn, mkn);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> dur = end-start;
            time_span = dur.count() < time_span ? dur.count() : time_span;
        }
        std::cout << "mkn:" << mkn << " FLOPs:" << gflops \
                  << " time:" << time_span  <<" gflops:"<< gflops/(time_span/1e6) << endl;
        delete a;
        delete b;
        delete c;
    }
}