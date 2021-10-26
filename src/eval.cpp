
#include <vector>

#include "matmul.h"

using namespace std;
int main()
{
    float *a, *b, *c, *ref;
    int m, n, k;
    int lda, ldb, ldc;

    vector<vector<int>> test_params = {
        {1, 1, 1}, {128, 128, 128}, {3, 4, 5}, {2, 2, 3}};

    for (auto &params : test_params)
    {
        m = params[0];
        n = params[1];
        k = params[2];

        malloc_matrix(m, k, n, &a, lda, &b, ldb, &c, ldc, &ref);
        set_matrix_value(m, k, a, lda);
        set_matrix_value(k, n, b, ldb);
        memset(c, 0, m * n * sizeof(float));
        memset(ref, 0, m * n * sizeof(float));

        matmul_ref(m, k, n, a, lda, b, ldb, c, ldc);
        matmul(m, k, n, a, lda, b, ldb, c, ldc);
        auto res = compare_matrix(params[0], params[2], ref, c, ldc);

        if (!res)
        {
            printf(".Error");
        }
        else
        {
            printf(".Pass");
        }
    }
    printf("\n");
}