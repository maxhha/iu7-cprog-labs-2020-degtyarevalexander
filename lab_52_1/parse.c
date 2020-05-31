#include <stdio.h>
#include "common.h"

/* Input format:
 *   last_name first_name mark1 mark2 mark3 mark4
 * last_name - string[25]
 * first_name - string[10]
 * mark1..4 - unsigned int
**/
int parse_file(FILE *f, int max_size, struct s_Student *array, int *array_len)
{
    struct s_Student student;

    *array_len = 0;

    while (*array_len < max_size)
    {
        int rc = fscanf(f,
            "%"XSTR(MAXLEN_LAST_NAME)"s"
            "%"XSTR(MAXLEN_LAST_NAME)"s"
            "%u %u %u %u",
            student.last_name,
            student.first_name,
            student.marks,
            student.marks + 1,
            student.marks + 2,
            student.marks + 3);

        if (rc == EOF)
        {
            break;
        }

        if (rc != 6)
        {
            return EPARSE;
        }

        *array_len += 1;
        *(array++) = student;
    }

    return OK;
}
