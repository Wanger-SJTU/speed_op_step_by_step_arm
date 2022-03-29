
#include "inc.h"

#include <iostream>
#include <random>
#include <cstring>

using namespace std;

void matmul_cmp(float *a, float *b, float *c, int m, int n, int k)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int r = 0; r < k; r++)
            {
                C(i, j) += A(i, r) * B(r, j);
            }
        }
    }
}

void rand_matrix(float* a, int m, int n) 
{
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<float> dis(1.0, 2.0);
    
    for(int i = 0; i < m*n; i++) {
        a[i] = dis(gen);
    }
}


void print_matrix(int *a, int m, int n) 
{
    for (int i = 0; i < m*n ; i++) {
        if (i % n == 0) {
            cout << endl;
        }
        cout << a[i] << " " << flush;
    }
    cout << endl;
}

float ref_cmp(float*a, float*b, int m, int n) 
{
    float err = 0;
    int mask[m*n] = {0};

    for(int i = 0; i < m*n; i++) {
        if (abs(a[i] - b[i]) > 1e-6) {
            mask[i] = 1;
        }
        err += (a[i] - b[i]);
    }
    print_matrix(mask, m, n);
    return err;
}


int main()
{
    int mkn = 16;
    float *a, *b, *c, *c_ref;
    a = new float[mkn * mkn];
    b = new float[mkn * mkn];
    c = new float[mkn * mkn];
    c_ref = new float[mkn * mkn];

    rand_matrix(a, mkn, mkn);
    rand_matrix(b, mkn, mkn);

    memset(c, 0, mkn * mkn * sizeof(float));
    memset(c_ref, 0, mkn * mkn * sizeof(float));

    matmul_cmp(a, b, c_ref, mkn, mkn, mkn);
    cout << c[0] << " " << c_ref[0] << endl;
    matmul(a, b, c, mkn, mkn, mkn);

    float err = ref_cmp(c, c_ref, mkn, mkn);
    cout << "err:" << err << endl;
   
    delete a;
    delete b;
    delete c;
}