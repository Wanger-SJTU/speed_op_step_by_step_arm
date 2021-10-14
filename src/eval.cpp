
#include <vector>

#include "matmul.h"

using namespace std;
int main()
{
    float *a, *b, *c, *ref;
    vector<vector<int>> test_params = {
        {1, 1, 1}, {128, 128, 128}, {3, 4, 5}, {2, 2, 3}};
    for (auto params : test_params)
    {
        a = new float[params[0] * params[1]];
        b = new float[params[1] * params[2]];
        c = new float[params[0] * params[2]];
        ref = new float[params[0] * params[2]];
        matmul_ref(params[0], params[1], params[2], a, b, ref);
        matmul_ref(params[0], params[1], params[2], a, b, c);
        auto res = compare_matrix(params[0], params[2], ref, c);
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