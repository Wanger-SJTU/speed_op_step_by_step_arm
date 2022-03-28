
#include "inc.h"

void matmul(float *a, float *b, float *c, int m, int n, int k)
{
    for (int i = 0; i < m; i += 4)
    {
        for (int j = 0; j < n; j += 4)
        {
            for (int r = 0; r < k; r++)
            {
                C(i, j + 0) += A(i, r) * B(r, j + 0);
                C(i, j + 1) += A(i, r) * B(r, j + 1);
                C(i, j + 2) += A(i, r) * B(r, j + 2);
                C(i, j + 3) += A(i, r) * B(r, j + 3);

                C(i + 1, j + 0) += A(i + 1, r) * B(r, j + 0);
                C(i + 1, j + 1) += A(i + 1, r) * B(r, j + 1);
                C(i + 1, j + 2) += A(i + 1, r) * B(r, j + 2);
                C(i + 1, j + 3) += A(i + 1, r) * B(r, j + 3);

                C(i + 2, j + 0) += A(i + 2, r) * B(r, j + 0);
                C(i + 2, j + 1) += A(i + 2, r) * B(r, j + 1);
                C(i + 2, j + 2) += A(i + 2, r) * B(r, j + 2);
                C(i + 2, j + 3) += A(i + 2, r) * B(r, j + 3);

                C(i + 3, j + 0) += A(i + 3, r) * B(r, j + 0);
                C(i + 3, j + 1) += A(i + 3, r) * B(r, j + 1);
                C(i + 3, j + 2) += A(i + 3, r) * B(r, j + 2);
                C(i + 3, j + 3) += A(i + 3, r) * B(r, j + 3);
            }
        }
    }
}
