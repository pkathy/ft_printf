#include "ft_printf.h"
//flags to handle #0-+
//conversions : csp
//conversions with l ll h hh : diouxX
//conversions with l L: f
//width and precision - handle int overflow
int main() {
    int a = -1;
    int *b = &a;
    char *test = "aaaaaaaaaa";
    int number = 1234567;
    /*printf(" %0-10d \n", sizeof(double));
    printf(" %010d \n", number);
    printf(" %-#10x \n", number);
    printf(" %#x \n", number);
   // printf("%.200f\n", 0.33);
    printf(" %5u\n", -500000);
     */
    int ret = ft_printf("%+000010d\n", 5, 10);
    int ret1 = printf("%+000010d\n", 5, 10);
    printf("ret: %d\n", ret);
    printf("ret1: %d\n", ret1);
    return 0;
}

