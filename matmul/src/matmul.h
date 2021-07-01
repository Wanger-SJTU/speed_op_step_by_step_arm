
/* Routine for computing C = A * B + C */
/*
  suppose a b c are col-major
  then A[i,j] = A[(j) * row + i]
*/
void matmul(int m, int n, int k, float *a, float *b, float *c);

void print_matrix(int m, int n, float *a);
void set_matrix_value(int m, int n, float *a);
void test_acc(int m, int k, int n, float *a, float *b, float *c);
