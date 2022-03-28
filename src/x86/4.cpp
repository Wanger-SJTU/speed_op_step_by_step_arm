
#include "inc.h"

#include <mmintrin.h>
#include <xmmintrin.h> // SSE
#include <pmmintrin.h> // SSE2
#include <emmintrin.h> // SSE3

typedef union
{
    __m128 v;
    float d[4];
} vec2f_t;

void add_dot_4x4_reg_reduce_k(float *a, float *b, float *c, int m, int n, int k)
{

    vec2f_t c_0_vreg, c_1_vreg, c_2_vreg, c_3_vreg,
            a_p0_vreg, a_p1_vreg,a_p2_vreg,a_p3_vreg,
            b_p_vreg;

    float *a_p0_pntr, *a_p1_pntr, *a_p2_pntr, *a_p3_pntr;

    a_p0_pntr = &A(0, 0);
    a_p1_pntr = &A(1, 0);
    a_p2_pntr = &A(2, 0);
    a_p3_pntr = &A(3, 0);
    
    c_0_vreg.v = _mm_setzero_ps();
    c_1_vreg.v = _mm_setzero_ps();
    c_2_vreg.v = _mm_setzero_ps();
    c_3_vreg.v = _mm_setzero_ps();
    
    for (int i = 0; i < k; i++)
    {
        a_p0_vreg.v = _mm_load1_ps((float *)a_p0_pntr++); /* load and duplicate */
        a_p1_vreg.v = _mm_load1_ps((float *)a_p1_pntr++); /* load and duplicate */
        a_p2_vreg.v = _mm_load1_ps((float *)a_p2_pntr++); /* load and duplicate */
        a_p3_vreg.v = _mm_load1_ps((float *)a_p3_pntr++); /* load and duplicate */

        b_p_vreg.v = _mm_load_ps((float *) &B(0, i));

        c_0_vreg.v += a_p0_vreg.v * b_p_vreg.v;
        c_1_vreg.v += a_p1_vreg.v * b_p_vreg.v;
        c_2_vreg.v += a_p2_vreg.v * b_p_vreg.v;
        c_3_vreg.v += a_p3_vreg.v * b_p_vreg.v;
    }

    C(0, 0) += c_0_vreg.d[0];
    C(0, 1) += c_0_vreg.d[1];
    C(0, 2) += c_0_vreg.d[2];
    C(0, 3) += c_0_vreg.d[3];

    C(1, 0) += c_1_vreg.d[0];
    C(1, 1) += c_1_vreg.d[1];
    C(1, 2) += c_1_vreg.d[2];
    C(1, 3) += c_1_vreg.d[3];

    C(2, 0) += c_2_vreg.d[0];
    C(2, 1) += c_2_vreg.d[1];
    C(2, 2) += c_2_vreg.d[2];
    C(2, 3) += c_2_vreg.d[3];

    C(3, 0) += c_3_vreg.d[0];
    C(3, 1) += c_3_vreg.d[1];
    C(3, 2) += c_3_vreg.d[2];
    C(3, 3) += c_3_vreg.d[3];
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
