#ifndef _FT_PRINTF
# define _FT_PRINTF
# define FLAGS_ZERO      (1U <<  0U)
# define FLAGS_MINUS     (1U <<  1U)
# define FLAGS_PLUS      (1U <<  2U)
# define FLAGS_SPACE     (1U <<  3U)
# define FLAGS_HASH      (1U <<  4U)
# define FLAGS_UPPERCASE (1U <<  5U)
# define FLAGS_CHAR      (1U <<  6U)
# define FLAGS_SHORT     (1U <<  7U)
# define FLAGS_LONG      (1U <<  8U)
# define FLAGS_LONG_LONG (1U <<  9U)
# define FLAGS_PRECISION (1U << 10U)
# define FLAGS_STAR      (1U << 11U)
# include "./libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <string.h>

typedef struct t_s {
    int  width;
    int  precision;
    char conversion;
    char *length;
    va_list *data;
    unsigned int flags_set;
} s_format;


int ft_printf(const char* format, ...);
int print_int(s_format *format);
int print_float(s_format *format);
int print_string(s_format *format);

#endif
