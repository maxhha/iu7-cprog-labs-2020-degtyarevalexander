#include <string.h>
#include "common.h"
#include <stdio.h>

/* Params:
 *   TYPE - file / array
 *   IN_TYPE - FILE * / struct s_student *
**/

#ifdef TYPE
#ifdef IN_TYPE

#include "templates.h"

int TEMPLATE(find, TYPE) (IN_TYPE students_in, IN_TYPE students_out, int n, char *last_name)
{
    struct s_student a;
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        a = TEMPLATE(get_from, TYPE) (students_in, i);
        if (strstr(a.last_name, last_name) == a.last_name)
        {
            TEMPLATE(set_in, TYPE) (students_out, a, k);
            k += 1;
        }
    }
    return k;
}

#endif // IN_TYPE
#endif // TYPE
