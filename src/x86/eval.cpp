
#include "inc.h"


int main()
{
    int mkn = 32;
    float *a, *b, *c;
    a = new float[mkn * mkn];
    b = new float[mkn * mkn];
    c = new float[mkn * mkn];
    matmul(a, b, c, mkn, mkn, mkn);
    delete a;
    delete b;
    delete c;
}