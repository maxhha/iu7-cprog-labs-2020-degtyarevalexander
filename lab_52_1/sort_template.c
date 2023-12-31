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

void TEMPLATE(sort, TYPE) (IN_TYPE students, int n)
{
    struct s_student a, b;
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < n - i; j++)
        {
            a = TEMPLATE(get_from, TYPE) (students, j);
            b = TEMPLATE(get_from, TYPE) (students, j + 1);

            int w1 = strcmp(a.last_name, b.last_name);
            int w2 = strcmp(a.first_name, b.first_name);

            if (w1 > 0 || (w1 == 0 && w2 > 0))
            {
                TEMPLATE(set_in, TYPE) (students, a, j + 1);
                TEMPLATE(set_in, TYPE) (students, b, j);
            }
        }
    }
}

#endif // IN_TYPE
#endif // TYPE
