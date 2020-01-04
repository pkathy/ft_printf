#include "ft_printf.h"
int	int_len(long n)
{
    int		len;

    len = (!n ? 1 : 0);
    if (n < 0)
        n *= -1;
    while (n > 0)
    {
        len++;
        n /= 10;
    }
    return (len);
}

int print_int(s_format *format)
{
    long to_print;

    to_print = va_arg(*(format->data), int);
    ft_putnbr(to_print);
    return (int_len(to_print));
}