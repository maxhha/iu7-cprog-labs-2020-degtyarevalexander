#include "../inc/my_snprintf.h"

#define ADDCHAR(s, len, maxlen, ch) do { \
    if ((s) != NULL && (len) + 1 < (maxlen)) \
    { \
        *((s)++) = (ch); \
    } \
    (len)++; \
} while(0)

void printint(char **s, size_t maxlen, int *len, char *convert, unsigned int i)
{
    if (i == 0)
        return;
    printint(s, maxlen, len, convert, i / 16);
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

    if (**fmt == 'x')
    {
        (*fmt)++;
        unsigned int i = va_arg(*args, int);
        char convert[] = "0123456789abcdef";

        if (i == 0)
        {
            ADDCHAR(*s, *len, maxlen, '0');
            return;
        }

        printint(s, maxlen, len, convert, i);
        
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
