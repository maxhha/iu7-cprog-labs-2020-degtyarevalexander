#include <stdlib.h>
#include <string.h>

char* my_strpbrk(const char *s, const char *accept)
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
    const char *i;

    for (;*s != '\0'; s++, len++)
    {
        for (i = accept; *i != '\0'; i++)
            if (*s == *i)
                break;
        if (*s != *i)
            return len;
    }
    return len;
}

size_t my_strcspn(const char *s, const char *accept)
{
    size_t len = 0;
    const char *i;
    for (; *s != '\0'; s++, len++)
    {
        for (i = accept; *i != '\0'; i++)
            if (*s == *i)
                break;
        if (*i != '\0')
            return len;
    }
    return len;
}

char* my_strchr(const char *s, int c)
{
    for (; *s != '\0'; s++)
        if (*s == c)
            return (char *) s;

    if (*s == c)
        return (char *) s;

    return NULL;
}

char* my_strrchr(const char *s, int c)
{
    const char *i = NULL;
    for (; *s != '\0'; s++)
        if (*s == c)
            i = s;

    if (*s == c)
        return (char *) s;
    return (char *) i;
}
