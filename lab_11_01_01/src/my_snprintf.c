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

        if (*c == 'c')
        {
            char cc = va_arg(args, int);
            ADDCHAR(s, len, maxlen, cc);
            c++;
            continue;
        }

        if (*c == 'x' || ((*c == 'l' || *c == 'h') && *(c + 1) == 'x'))
        {
            unsigned long i;

            if (*c == 'l')
            {
                i = va_arg(args, unsigned long);
                c += 2;
            }
            else if (*c == 'h')
            {
                i = (unsigned short) va_arg(args, int);
                c += 2;
            }
            else
            {
                i = va_arg(args, unsigned int);
                c += 1;
            }

            char convert[] = "0123456789abcdef";

            if (i == 0)
            {
                ADDCHAR(s, len, maxlen, '0');
                continue;
            }

            printhex(&s, maxlen, &len, convert, i);

            continue;
        }

        if (*c == 's')
        {
            c++;
            char *str = va_arg(args, char *);

            if (str == NULL)
            {
                str = "(null)";
            }

            while (*str != '\0')
            {
                ADDCHAR(s, len, maxlen, *str);
                str++;
            }

            continue;
        }
    }

    if ((s) != NULL && len < maxlen)
    {
        *s = '\0';
    }

    va_end(args);

    return len;
}
