#include "ft_printf.h"
//flags to handle #0-+
//conversions : csp
//conversions with l ll h hh : diouxX
//conversions with l L: f
//width and precision - handle int overflow

typedef struct s_s {
    int count;
    int error;
} s_utils;

void clear_format(s_format *f)
{
    f->width = -1;
    f->precision = -1;
    f->length = 0;
    f->flags_set = 0;
    f->data = NULL;
    f->conversion = 0;
}

char    *handle_flag(char *c, s_format *format)
{
    if (*c == '#')
        format->flags_set |= FLAGS_HASH;
    else if (*c == '+')
        format->flags_set |= FLAGS_PLUS;
    else if (*c == '-')
        format->flags_set |= FLAGS_MINUS;
    else if (*c == ' ')
        format->flags_set |= FLAGS_SPACE;
    else if (*c == '0')
        format->flags_set |= FLAGS_ZERO;
    return (++c);
}

char    *handle_width(char *c, s_format *format)
{
    if (*c == '*')
        format->width = va_arg(*(format->data), int);
    else if (*c >= '0' && *c <= '9')
    {
        //temp solution
        format->width = ft_atoi(c);
        while (*c >= '0' && *c <= '9')
            ++c;
        return (c);
    }
    return (++c);
}

char    *handle_precision(char *c, s_format *format)
{
    if (*c >= '0' && *c <= '9')
    {
        //temp solution
        format->precision = ft_atoi(c);
        while (*c >= '0' && *c <= '9')
            ++c;
        return (c);
    }
    return (++c);
}

char    *handle_conversion(char *c, s_format *format, int *error, int *count)
{
    char *start;
    char *len;

    start = c;
    if (strchr("lhu", *c))
    {
        while (strchr("lhu", *c))
            ++c;
        len = ft_strnew(c - start);
        ft_strncpy(len, start, c - start);
    }
    if(!strchr("cspdiouxX", *c))
    {
        *error = 1;
        return (++c);
    }
    format->length = len;
    format->conversion = *c;
    if (*c == 'd')
        *count += print_int(format);
    return (++c);
}

char *pre_parse(char *to_parse, s_format *format, int *count, int *error)
{
    if (*to_parse == '%')
    {
        (*count)++;
        *error = 1;
        write(1, to_parse++, 1);
        return (to_parse);
    }
    while (1)
        if (*to_parse == '#' || *to_parse == '-' || *to_parse == '+' || *to_parse == ' ')
            to_parse = handle_flag(to_parse, format);
        else
            break ;
    if (*to_parse == '0')
        to_parse = handle_flag(to_parse, format);
    if ((*to_parse >= '0' && *to_parse <= '9') || *to_parse == '*')
        to_parse = handle_width(to_parse, format);
    if (*to_parse == '.')
        to_parse = handle_precision(++to_parse, format);
    return (to_parse);
}
int parse(char *to_parse, s_format *format, va_list *va, s_utils *utils)
{
    char *start;

    while (*to_parse)
    {
        utils->error = 0;
        clear_format(format);
        if (*to_parse != '%')
        {
            ++(utils->count);
            write(1, to_parse++, 1);
            continue ;
        }
        format->data = va;
        start = (char *)to_parse++;
        to_parse = pre_parse(to_parse, format, &(utils->count), &(utils->error));
        if (utils->error)
            continue ;
        to_parse = handle_conversion(to_parse, format, &(utils->error), &(utils->count));
        if (utils->error)
        {
            write(1, start, to_parse - start);
            utils->count += to_parse - start;
        }
    }
    return (utils->count);
}

size_t ft_strnlen(const char *str, size_t maxlen)
{
    const char *p;

    p = str;

    while (maxlen-- > 0 && *p)
        p++;
    return (p - str);
}

int ft_printf(const char* format, ...)
{
    va_list va;
    int ret;
    s_format f;
    s_utils utils;

    utils.count = 0;
    utils.error = 0;
    va_start(va, format);
    if (ft_strnlen(format, 2) == 1 && *format == '%')
        ret = -1;
    else
        ret = parse((char *)format, &f, &va, &utils);
    va_end(va);
    return (ret);
}


