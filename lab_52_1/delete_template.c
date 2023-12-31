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

int TEMPLATE(delete, TYPE) (IN_TYPE students_in, IN_TYPE students_out, int n)
{
    struct s_student a;
    double sum = 0;

    for (int i = 0; i < n; i++)
    {
        a = TEMPLATE(get_from, TYPE) (students_in, i);
        sum += a.marks[0];
        sum += a.marks[1];
        sum += a.marks[2];
        sum += a.marks[3];
    }

    double mean = sum / n;
    int k = 0;

    for (int i = 0; i < n; i++)
    {
        a = TEMPLATE(get_from, TYPE) (students_in, i);
        if ((double) a.marks[0] + a.marks[1] + a.marks[2] + a.marks[3] >= mean)
        {
            TEMPLATE(set_in, TYPE) (students_out, a, k);
            k += 1;
        }
    }

    return k;
}

#endif // IN_TYPE
#endif // TYPE
