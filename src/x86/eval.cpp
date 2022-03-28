
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

float ref_cmp(float*a, float*b, int m, int n) 
{
    float err = 0;
    
    for(int i = 0; i < m*n; i++) {
        err += (a[i] - b[i]);
    }

    return err;
}


int main()
{
    int mkn = 32;
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
    matmul(a, b, c, mkn, mkn, mkn);

    float err = ref_cmp(c, c_ref, mkn, mkn);
    cout << "err:" << err << endl;
   
    delete a;
    delete b;
    delete c;
}