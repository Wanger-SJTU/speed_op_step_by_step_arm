
#include <vector>

#include "matmul.h"

using namespace std;

int main()
{

    int m, n, k;
    int lda, ldb, ldc;

    vector<vector<int>> test_params = {
        {128, 128, 128}};

    for (auto &params : test_params)
    {
        float *a = nullptr, *b = nullptr, *c = nullptr, *ref = nullptr;
        m = params[0];
        n = params[1];
        k = params[2];

        printf("== test for %d %d %d ===\n", m, n, k);
        malloc_matrix(m, n, k, &a, lda, &b, ldb, &c, ldc, &ref);

        set_matrix_value(m, n, k, a, lda, b, ldb, c, ldc, ref);

        matmul_ref(m, n, k, a, lda, b, ldb, c, ldc);
        matmul_ref(m, n, k, a, lda, b, ldb, ref, ldc);

        auto res = compare_matrix(params[0], params[2], ref, c, ldc);

        if (!res)
        {
            printf(".Error\n");
        }
        else
        {
            printf(".Pass\n");
        }

        free(a);
        free(b);
        free(c);
        free(ref);
    }
    printf("Done \n");
}