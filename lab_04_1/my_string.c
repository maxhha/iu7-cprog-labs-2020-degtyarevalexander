#include <stdlib.h>
#include <string.h>
#include "my_string.h"

char *my_strpbrk(const char *s, const char *accept)
{
    for (;*s != '\0';s++)
        for (const char *i = accept; *i != '\0'; i++)
            if (*s == *i)
                return (char *) s;
    return NULL;
}

size_t my_strspn(const char *s, const char *accept)
{
    size_t len = 0;

    while (*s != '\0' && my_strchr(accept, *s++) != NULL)
        len++;

    return len;
}

size_t my_strcspn(const char *s, const char *accept)
{
    size_t len = 0;

    while (*s != '\0' && my_strchr(accept, *s++) == NULL)
        len++;

    return len;
}

char *my_strchr(const char *s, int c)
{
    while (*s != (char) c)
        if (*s++ == '\0')
            return NULL;

    return (char *) s;
}

char *my_strrchr(const char *s, int c)
{
    const char *i = NULL;

    do
    {
        if (*s == c)
            i = s;
    } while (*s++ != '\0');

    return (char *) i;
}
