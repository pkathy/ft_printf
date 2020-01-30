#include "ft_printf.h"
//flags to handle #0-+
//conversions : csp
//conversions with l ll h hh : diouxX
//conversions with l L: f
//width and precision - handle int overflow

unsigned long int_len(unsigned long long n, int base)
{
    unsigned long long len;

    len = 0;
    while (n > 0)
    {
        len++;
        n /= base;
    }
    return (len);
}

void int_to_base(unsigned long long n, char base, t_str *res)
{
    int len;
    char *base_str;

    base_str = "0123456789ABCDEF";
    len = int_len(n, base);
    res->str = ft_strnew(len);
    res->length = len;
    while(n > 0)
    {
        res->str[len - 1] = base_str[n % base];
        len--;
        n /= base;
    }
}

int set_base(char c)
{
    if (c == 'x' || c == 'X')
        return (16);
    else if (c == 'o')
        return (8);
    else
        return (10);
}

void *handle_unsigned_length(s_format *format)
{
    void *ret;
    unsigned long long u_n;

    ret = ft_memalloc(sizeof(long long));
    if (ft_strequ(format->length, "l"))
        u_n = (unsigned long)va_arg(*(format->data), unsigned long);
    else if (ft_strequ(format->length, "ll"))
        u_n = (unsigned long long)va_arg(*(format->data), unsigned long long);
    else if (ft_strequ(format->length, "h"))
        u_n = (unsigned short)va_arg(*(format->data), unsigned int);
    else if (ft_strequ(format->length, "hh"))
        u_n = (unsigned char)va_arg(*(format->data), unsigned int);
    else
        u_n = (unsigned int)va_arg(*(format->data), unsigned int);
    ft_memmove(ret, &u_n, sizeof(long long));
    return (ret);
}

void *handle_length(s_format *format)
{
    void *ret;
    long long n;

    ret = ft_memalloc(sizeof(long long));
    if (ft_strequ(format->length, "l"))
        n = (long)va_arg(*(format->data), long);
    else if (ft_strequ(format->length, "ll"))
        n = (long long)va_arg(*(format->data), long long);
    else if (ft_strequ(format->length, "h"))
        n = (short)va_arg(*(format->data), int);
    else if (ft_strequ(format->length, "hh"))
        n = (char)va_arg(*(format->data), int);
    else
        n = (int)va_arg(*(format->data), int);
    ft_memmove(ret, &n, sizeof(long long));
    return (ret);
}

//does not work now

void append_int_precision(s_format *format, t_str *in)
{
    long d;

    d = format->precision - ft_strlen(in->str);
    if (d > 0)
    {
        clean_strjoin_left(&(in->str), 1, make_str(d, '0'));
        in->length += d;
    }
}

t_str print_unsigned(s_format *format)
{
    unsigned long long to_print;
    t_str ret;

    to_print = *(unsigned long long *)handle_unsigned_length(format);
    ret.sign = '+';
    int_to_base(to_print, 10, &ret);
    append_int_precision(format, &ret);
    return (ret);
}

t_str print_int(s_format *format)
{
    long long to_print;
    int base;
    t_str ret;

    if (format->conversion == 'u')
        return (print_unsigned(format));
    base = set_base(format->conversion);
    to_print = *(long long *)handle_length(format);
    ret.sign = to_print > 0 ? '+' : '-';
    int_to_base(to_print > 0 ? to_print : -1*to_print, base, &ret);
    if (format->conversion == 'x')
        to_lower_str(ret.str);
    append_int_precision(format, &ret);
    if (format->flags_set & FLAGS_HASH && ft_strchr("oxX", format->conversion))
    {
        if (format->conversion == 'o')
            clean_strjoin_left(&(ret.str), 1, ft_strdup("0"));
        else
            clean_strjoin_left(&(ret.str), 1, ft_strdup("0x"));
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