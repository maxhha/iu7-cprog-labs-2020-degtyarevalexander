#include "../inc/my_snprintf.h"

#define ADDCHAR(s, len, maxlen, ch) do { \
    if ((s) != NULL && (len) + 1 < (maxlen)) \
    { \
        *((s)++) = (ch); \
    } \
    (len)++; \
} while(0)

void printhex(char **s, size_t maxlen, int *len, char *convert, unsigned long i)
{
    if (i == 0)
        return;
    printhex(s, maxlen, len, convert, i / 16);
    ADDCHAR(*s, *len, maxlen, convert[i % 16]);
}

void printarg(char **s, size_t maxlen, const char **fmt, int *len, va_list *args)
{
    if (**fmt == 'c')
    {
        char c = va_arg(*args, int);
        ADDCHAR(*s, *len, maxlen, c);
        (*fmt)++;
        return;
    }

    if (**fmt == 'x' || ((**fmt == 'l' || **fmt == 'h') && *(*fmt + 1) == 'x'))
    {
        unsigned long i;

        if (**fmt == 'l')
        {
            i = va_arg(*args, unsigned long);
            *fmt += 2;
        }
        else if (**fmt == 'h')
        {
            i = (unsigned short) va_arg(*args, int);
            *fmt += 2;
        }
        else
        {
            i = va_arg(*args, unsigned int);
            *fmt += 1;
        }

        char convert[] = "0123456789abcdef";

        if (i == 0)
        {
            ADDCHAR(*s, *len, maxlen, '0');
            return;
        }

        printhex(s, maxlen, len, convert, i);

        return;
    }

    if (**fmt == 's')
    {
        (*fmt)++;
        char *str = va_arg(*args, char *);

        if (str == NULL)
        {
            str = "(null)";
        }

        while (*str)
        {
            ADDCHAR(*s, *len, maxlen, *str);
            str++;
        }

        return;
    }
}

int my_snprintf (char *s, size_t maxlen, const char *format, ...)
{
    int len = 0;
    va_list args;
    const char *c = format;

    va_start(args, format);

    while (*c != '\0')
    {
        if (*c != '%')
        {
            ADDCHAR(s, len, maxlen, *c);
            c++;
            continue;
        }

        c++;
        printarg(&s, maxlen, &c, &len, &args);
    }

    if ((s) != NULL && len < maxlen)
    {
        *s = '\0';
    }

    va_end(args);

    return len;
}
