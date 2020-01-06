#include "ft_printf.h"
//flags to handle #0-+
//conversions : csp
//conversions with l ll h hh : diouxX
//conversions with l L: f
//width and precision - handle int overflow
int main() {
    int a = -1;
    int *b = &a;
    int number = 123;
    printf(" %0-10d \n", sizeof(double));
    printf(" %010d \n", number);
    printf(" %-#10x \n", number);
    printf(" %#x \n", number);
    printf("%.200f\n", 0.33);

    char *pointer = "little";

    printf("%10d\n", 1);
    return 0;
}

