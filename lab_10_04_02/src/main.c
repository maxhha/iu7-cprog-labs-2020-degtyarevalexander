#include "../inc/main.h"

int main(void)
{
    char *buf = NULL;
    size_t buf_size = 0;
    int readed = getline(&buf, &buf_size, stdin);

    if (readed < 1)
    {
        LOG_ERROR("fail to read line %s", "");
        if (buf)
            free(buf);
        return EXIT_FAILURE;
    }

    buf[readed - 1] = '\0';

    int rc = EXIT_FAILURE;

    if (strcmp(buf, OPERATION_OUT) == 0)
    {
        rc = perform_operation_out();
    }
    if (strcmp(buf, OPERATION_MUL) == 0)
    {
        rc = perform_operation_mul();
    }
    if (strcmp(buf, OPERATION_SQR) == 0)
    {
        rc = perform_operation_sqr();
    }
    if (strcmp(buf, OPERATION_DIV) == 0)
    {
        rc = perform_operation_div();
    }

    free(buf);

    return rc;
}
