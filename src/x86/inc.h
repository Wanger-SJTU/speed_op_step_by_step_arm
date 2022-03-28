

#define A(i, j) a[i * k + j] // m * k
#define B(i, j) b[i * n + j] // k * n
#define C(i, j) c[i * n + j] // m * n

void matmul(float *a, float *b, float *c, int m, int n, int k);
