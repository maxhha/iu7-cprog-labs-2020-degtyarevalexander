#include "../inc/my_snprintf.h"

#define ADDCHAR(s, len, maxlen, ch) do { \
    if ((s) != NULL && (len) + 1 < (maxlen)) \
    { \
        *((s)++) = (ch); \
    } \
    (len)++; \
} while(0)

void printarg(char **s, size_t maxlen, const char **fmt, int *len, va_list *args)
{
    if (**fmt == 'c')
    {
        char c = (char) va_arg(*args, int);
        ADDCHAR(*s, *len, maxlen, c);
        (*fmt)++;
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
        if (*c == '%')
        {
            c++;
            printarg(&s, maxlen, &c, &len, &args);
        }
        else
        {
            ADDCHAR(s, len, maxlen, *c);
            c++;
        }
    }

    if ((s) != NULL && len < maxlen)
    {
        *s = '\0';
    }

    va_end(args);

    return len;
}
