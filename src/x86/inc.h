

#define A(i, j) a[i  + j* m] // m * k
#define B(i, j) a[i  + j* k] // k * n
#define C(i, j) a[i  + j* m] // m * n

void matmul(float *a, float *b, float *c, int m, int n, int k);
