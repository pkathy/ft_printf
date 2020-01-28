#include "ft_printf.h"
unsigned long int_len(unsigned long n, int base)
{
    unsigned long len;

    len = 0;
    while (n > 0)
    {
        len++;
        n /= base;
    }
    return (len);
}

void int_to_base(long n, char base, t_str *res)
{
    int len;
    int sign;
    unsigned long n_1;
    char *base_str;

    base_str = "0123456789ABCDEF";
    sign = 0;
    sign += (n < 0 ? 1 : 0);
    n_1 = sign ? n * -1 : n;
    len = int_len(n_1, base);
    res->str = ft_strnew(len);
    res->length = len;
    res->sign = sign ? '-' : '+';
    while(n_1 > 0)
    {
        res->str[len - 1] = base_str[n_1 % base];
        len--;
        n_1 /= base;
    }
}


//does not work now
t_str print_int(s_format *format)
{
    long long to_print;
    unsigned long long to_print1;
    int base;
    t_str ret;

    if (format->conversion == 'x' || format->conversion == 'X')
        base = 16;
    else if (format->conversion == 'o')
        base = 8;
    else
        base = 10;
    if (format->conversion == 'u')
        to_print1 = va_arg(*(format->data), unsigned int);
    else
        to_print = va_arg(*(format->data), int);
    int_to_base(to_print, base, &ret);
    if (format->conversion == 'x')
        to_lower_str(ret.str);
    if (format->flags_set & FLAGS_HASH && ft_strchr("oxX", format->conversion))
    {
        if (format->conversion == 'o')
            clean_strjoin_left(&(ret.str), 1, "0");
        else
            clean_strjoin_left(&(ret.str), 1, "0x");
        ret.length += format->conversion == 'o' ? 1 : 2;
    }

    return (ret);
}
t_str print_string(s_format *format)
{
    char *to_print;
    t_str ret;
    if (format->conversion == 'c')
    {
        to_print = ft_strnew(1);
        to_print[0] = va_arg(*(format->data), int);
        ret.str = to_print;
    }
    else
    {
        to_print = va_arg(*(format->data), char *);
        ret.str = ft_strdup(to_print);
    }
    ret.length = ft_strlen(ret.str);
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