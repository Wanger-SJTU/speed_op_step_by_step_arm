
#include "inc.h"

#include <mmintrin.h>
#include <xmmintrin.h> // SSE
#include <pmmintrin.h> // SSE2
#include <emmintrin.h> // SSE3

#include <immintrin.h>

#include <algorithm>

#define in_k 128
#define in_m 128

typedef union
{
    __m256 v;
    float d[8];
} vec256f_t;

typedef union
{
    __m128 v;
    float d[4];
} vec128f_t;

void add_dot_4x4_reg_reduce_k(float *a, float *b, float *c, int m, int n, int k)
{
    vec256f_t c_0_vreg, c_1_vreg, c_2_vreg, c_3_vreg,
        c_4_vreg, c_5_vreg, c_6_vreg, c_7_vreg,
        a_p0_vreg, a_p1_vreg, a_p2_vreg, a_p3_vreg,
        a_p4_vreg, a_p5_vreg, a_p6_vreg, a_p7_vreg,
        b_p_vreg;

    float *a_p0_pntr, *a_p1_pntr, *a_p2_pntr, *a_p3_pntr,
        *a_p4_pntr, *a_p5_pntr, *a_p6_pntr, *a_p7_pntr;

    a_p0_pntr = &A(0, 0);
    a_p1_pntr = &A(1, 0);
    a_p2_pntr = &A(2, 0);
    a_p3_pntr = &A(3, 0);
    a_p4_pntr = &A(4, 0);
    a_p5_pntr = &A(5, 0);
    a_p6_pntr = &A(6, 0);
    a_p7_pntr = &A(7, 0);

    c_0_vreg.v = _mm256_setzero_ps();
    c_1_vreg.v = _mm256_setzero_ps();
    c_2_vreg.v = _mm256_setzero_ps();
    c_3_vreg.v = _mm256_setzero_ps();
    c_4_vreg.v = _mm256_setzero_ps();
    c_5_vreg.v = _mm256_setzero_ps();
    c_6_vreg.v = _mm256_setzero_ps();
    c_7_vreg.v = _mm256_setzero_ps();

    for (int i = 0; i < k; i++)
    {
        b_p_vreg.v = _mm256_load_ps((float *)&B(i, 0));

        a_p0_vreg.v = _mm256_broadcast_ss((float *)a_p0_pntr++);
        c_0_vreg.v += a_p0_vreg.v * b_p_vreg.v;

        a_p1_vreg.v = _mm256_broadcast_ss((float *)a_p1_pntr++);
        c_1_vreg.v += a_p1_vreg.v * b_p_vreg.v;

        a_p2_vreg.v = _mm256_broadcast_ss((float *)a_p2_pntr++);
        c_2_vreg.v += a_p2_vreg.v * b_p_vreg.v;

        a_p3_vreg.v = _mm256_broadcast_ss((float *)a_p3_pntr++);
        c_3_vreg.v += a_p3_vreg.v * b_p_vreg.v;

        a_p4_vreg.v = _mm256_broadcast_ss((float *)a_p4_pntr++);
        c_4_vreg.v += a_p4_vreg.v * b_p_vreg.v;

        a_p5_vreg.v = _mm256_broadcast_ss((float *)a_p5_pntr++);
        c_5_vreg.v += a_p5_vreg.v * b_p_vreg.v;

        a_p6_vreg.v = _mm256_broadcast_ss((float *)a_p6_pntr++);
        c_6_vreg.v += a_p6_vreg.v * b_p_vreg.v;

        a_p7_vreg.v = _mm256_broadcast_ss((float *)a_p7_pntr++);
        c_7_vreg.v += a_p7_vreg.v * b_p_vreg.v;
    }

    C(0, 0) += c_0_vreg.d[0];
    C(0, 1) += c_0_vreg.d[1];
    C(0, 2) += c_0_vreg.d[2];
    C(0, 3) += c_0_vreg.d[3];
    C(0, 4) += c_0_vreg.d[4];
    C(0, 5) += c_0_vreg.d[5];
    C(0, 6) += c_0_vreg.d[6];
    C(0, 7) += c_0_vreg.d[7];

    C(1, 0) += c_1_vreg.d[0];
    C(1, 1) += c_1_vreg.d[1];
    C(1, 2) += c_1_vreg.d[2];
    C(1, 3) += c_1_vreg.d[3];
    C(1, 4) += c_1_vreg.d[4];
    C(1, 5) += c_1_vreg.d[5];
    C(1, 6) += c_1_vreg.d[6];
    C(1, 7) += c_1_vreg.d[7];

    C(2, 0) += c_2_vreg.d[0];
    C(2, 1) += c_2_vreg.d[1];
    C(2, 2) += c_2_vreg.d[2];
    C(2, 3) += c_2_vreg.d[3];
    C(2, 4) += c_2_vreg.d[4];
    C(2, 5) += c_2_vreg.d[5];
    C(2, 6) += c_2_vreg.d[6];
    C(2, 7) += c_2_vreg.d[7];

    C(3, 0) += c_3_vreg.d[0];
    C(3, 1) += c_3_vreg.d[1];
    C(3, 2) += c_3_vreg.d[2];
    C(3, 3) += c_3_vreg.d[3];
    C(3, 4) += c_3_vreg.d[4];
    C(3, 5) += c_3_vreg.d[5];
    C(3, 6) += c_3_vreg.d[6];
    C(3, 7) += c_3_vreg.d[7];

    C(4, 0) += c_4_vreg.d[0];
    C(4, 1) += c_4_vreg.d[1];
    C(4, 2) += c_4_vreg.d[2];
    C(4, 3) += c_4_vreg.d[3];
    C(4, 4) += c_4_vreg.d[4];
    C(4, 5) += c_4_vreg.d[5];
    C(4, 6) += c_4_vreg.d[6];
    C(4, 7) += c_4_vreg.d[7];

    C(5, 0) += c_5_vreg.d[0];
    C(5, 1) += c_5_vreg.d[1];
    C(5, 2) += c_5_vreg.d[2];
    C(5, 3) += c_5_vreg.d[3];
    C(5, 4) += c_5_vreg.d[4];
    C(5, 5) += c_5_vreg.d[5];
    C(5, 6) += c_5_vreg.d[6];
    C(5, 7) += c_5_vreg.d[7];

    C(6, 0) += c_6_vreg.d[0];
    C(6, 1) += c_6_vreg.d[1];
    C(6, 2) += c_6_vreg.d[2];
    C(6, 3) += c_6_vreg.d[3];
    C(6, 4) += c_6_vreg.d[4];
    C(6, 5) += c_6_vreg.d[5];
    C(6, 6) += c_6_vreg.d[6];
    C(6, 7) += c_6_vreg.d[7];

    C(7, 0) += c_7_vreg.d[0];
    C(7, 1) += c_7_vreg.d[1];
    C(7, 2) += c_7_vreg.d[2];
    C(7, 3) += c_7_vreg.d[3];
    C(7, 4) += c_7_vreg.d[4];
    C(7, 5) += c_7_vreg.d[5];
    C(7, 6) += c_7_vreg.d[6];
    C(7, 7) += c_7_vreg.d[7];
}

void matmul(float *a, float *b, float *c, int m, int n, int k)
{
    for (int p = 0; p < k; p += in_k)
    {
        int partial_k = std::min({in_k, k - p});
        for (int j = 0; j < n; j += 8)
        {
            for (int i = 0; i < m; i += 8)
            {
                add_dot_4x4_reg_reduce_k(&(A(i, 0)), &(B(0, j)), &(C(i, j)), m, n, partial_k);
            }
        }
    }
}
