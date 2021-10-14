

#include "matmul.h"

#undef A
#undef B
#undef C
#define A(i, j) a[(j)*lda + (i)]
#define B(i, j) b[(j)*ldb + (i)]
#define C(i, j) c[(j)*ldc + (i)]

void matmul(int m, int k, int n, float *a, float *b, float *c)
{

    int lda = m;
    int ldb = k;
    int ldc = m;

    for (int i = 0; i < m; i += 4)
    {
        for (int j = 0; j < n; j += 4)
        {
            // col major
            C(i + 0, j + 0) = 0;
            C(i + 1, j + 0) = 0;
            C(i + 2, j + 0) = 0;
            C(i + 3, j + 0) = 0;

            C(i + 0, j + 1) = 0;
            C(i + 1, j + 1) = 0;
            C(i + 2, j + 1) = 0;
            C(i + 3, j + 1) = 0;

            C(i + 0, j + 2) = 0;
            C(i + 1, j + 2) = 0;
            C(i + 2, j + 2) = 0;
            C(i + 3, j + 2) = 0;

            C(i + 0, j + 3) = 0;
            C(i + 1, j + 3) = 0;
            C(i + 2, j + 3) = 0;
            C(i + 3, j + 3) = 0;

            for (int p = 0; p < k; p + 4)
            {
                // TODO
                C(i + 0, j + 0) += A(i + 0, p) * B(p, j + 0);
                C(i + 1, j + 0) += A(i + 1, p) * B(p, j + 0);
                C(i + 2, j + 0) += A(i + 2, p) * B(p, j + 0);
                C(i + 3, j + 0) += A(i + 3, p) * B(p, j + 0);

                C(i + 0, j + 1) += A(i + 0, p) * B(p, j + 1);
                C(i + 1, j + 1) += A(i + 1, p) * B(p, j + 1);
                C(i + 2, j + 1) += A(i + 2, p) * B(p, j + 1);
                C(i + 3, j + 1) += A(i + 3, p) * B(p, j + 1);

                C(i + 0, j + 2) += A(i + 0, p) * B(p, j + 2);
                C(i + 1, j + 2) += A(i + 1, p) * B(p, j + 2);
                C(i + 2, j + 2) += A(i + 2, p) * B(p, j + 2);
                C(i + 3, j + 2) += A(i + 3, p) * B(p, j + 2);

                C(i + 0, j + 3) += A(i + 0, p) * B(p, j + 3);
                C(i + 1, j + 3) += A(i + 1, p) * B(p, j + 3);
                C(i + 2, j + 3) += A(i + 2, p) * B(p, j + 3);
                C(i + 3, j + 3) += A(i + 3, p) * B(p, j + 3);
            }
        }
    }
}