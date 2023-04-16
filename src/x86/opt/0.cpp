
#include "inc.h"

void matmul(float *a, float *b, float *c, int m, int n, int k)
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
