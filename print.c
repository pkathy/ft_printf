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
//does not work now
t_str print_int(s_format *format)
{
    long to_print;
    t_str ret;
    to_print = va_arg(*(format->data), int);
    if (to_print < 0)
    {
        ret.sign = '-';
        to_print *= -1;
    } else
        ret.sign = '+';
    ret.str = ft_itoa(to_print);
    ret.length = ft_strlen(ret.str);
    return (ret);
}
t_str print_string(s_format *format)
{
    long to_print;
    t_str ret;

    to_print = va_arg(*(format->data), int);
    ft_putnbr(to_print);
    return (ret);
}
t_str print_pointer(s_format *format)
{
    long to_print;
    t_str ret;

    to_print = va_arg(*(format->data), int);
    ft_putnbr(to_print);
    return (ret);
}
t_str print_float(s_format *format)
{
    long to_print;
    t_str ret;

    to_print = va_arg(*(format->data), int);
    ft_putnbr(to_print);
    return (ret);
}