
#include <chrono>
#include <iostream>

#define A(i, j) a[i  + j* m] // m * k
#define B(i, j) a[i  + j* k] // k * n
#define C(i, j) a[i  + j* m ] // m * n

using namespace std;

void add_dot_4x4_reg_reduce_k(float *a, float *b, float *c, int m, int n, int k)
{

    register float c_00_reg, c_01_reg, c_02_reg, c_03_reg,
        c_10_reg, c_11_reg, c_12_reg, c_13_reg,
        c_20_reg, c_21_reg, c_22_reg, c_23_reg,
        c_30_reg, c_31_reg, c_32_reg, c_33_reg;

    register float a_0_reg, a_1_reg, a_2_reg, a_3_reg;

    c_00_reg = 0.0;
    c_01_reg = 0.0;
    c_02_reg = 0.0;
    c_03_reg = 0.0;
    c_10_reg = 0.0;
    c_11_reg = 0.0;
    c_12_reg = 0.0;
    c_13_reg = 0.0;
    c_20_reg = 0.0;
    c_21_reg = 0.0;
    c_22_reg = 0.0;
    c_23_reg = 0.0;
    c_30_reg = 0.0;
    c_31_reg = 0.0;
    c_32_reg = 0.0;
    c_33_reg = 0.0;

    for (int i = 0; i < k; i++)
    {
        a_0_reg = A(0, i);
        a_1_reg = A(1, i);
        a_2_reg = A(2, i);
        a_3_reg = A(3, i);

        c_00_reg += a_0_reg * B(i, 0);
        c_01_reg += a_0_reg * B(i, 1);
        c_02_reg += a_0_reg * B(i, 2);
        c_03_reg += a_0_reg * B(i, 3);

        c_10_reg += a_1_reg * B(i, 0);
        c_11_reg += a_1_reg * B(i, 1);
        c_12_reg += a_1_reg * B(i, 2);
        c_13_reg += a_1_reg * B(i, 3);

        c_20_reg += a_2_reg * B(i, 0);
        c_21_reg += a_2_reg * B(i, 1);
        c_22_reg += a_2_reg * B(i, 2);
        c_23_reg += a_2_reg * B(i, 3);

        c_30_reg += a_3_reg * B(i, 0);
        c_31_reg += a_3_reg * B(i, 1);
        c_32_reg += a_3_reg * B(i, 2);
        c_33_reg += a_3_reg * B(i, 3);
    }
    C(0, 0) += c_00_reg;
    C(0, 1) += c_01_reg;
    C(0, 2) += c_02_reg;
    C(0, 3) += c_03_reg;
    C(1, 0) += c_10_reg;
    C(1, 1) += c_11_reg;
    C(1, 2) += c_12_reg;
    C(1, 3) += c_13_reg;
    C(2, 0) += c_20_reg;
    C(2, 1) += c_21_reg;
    C(2, 2) += c_22_reg;
    C(2, 3) += c_23_reg;
    C(3, 0) += c_30_reg;
    C(3, 1) += c_31_reg;
    C(3, 2) += c_32_reg;
    C(3, 3) += c_33_reg;
}

void matmul(float *a, float *b, float *c, int m, int n, int k)
{
    for (int i = 0; i < m; i += 4)
    {
        for (int j = 0; j < n; j += 4)
        {
            add_dot_4x4_reg_reduce_k(&(A(i, 0)), &(B(0, j)), &(C(i, j)), m, n, k);
        }
    }
}

int main()
{
    for (int mkn = 4; mkn <= 1024; mkn *= 2)
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
}