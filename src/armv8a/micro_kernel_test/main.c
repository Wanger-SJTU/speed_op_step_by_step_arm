
#include <stdio.h>

// aarch64-linux-android30-clang main.c -o main -march=armv8a+sve

void print_cnth() 
{
    register int x asm("x0");
    x = 0;
    printf("%d\n", x);
    
    asm volatile(
        "cntb x0"
        : "=x"(x)
        : "0"(x)
        :
    );

    printf("%d\n", x);
}

int main() {
    print_cnth();
}