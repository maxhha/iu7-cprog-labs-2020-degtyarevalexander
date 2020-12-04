#include "../inc/transaction.h"

transaction_t *create_transaction_from_line(char *line)
{
    LOG_DEBUG("create from \"%s\"", line);
    transaction_t *tr = malloc(sizeof(transaction_t));

    if (tr == NULL)
        return NULL;

    line = strdup(line);

    if (!(tr->date = strtok(line, ";")) || tr->date != line)
    {
        LOG_ERROR("cant read date%s", "");
        free(tr);
        free(line);
        return NULL;
    }
    LOG_DEBUG("date = %s", tr->date);


    char *amount_str = strtok(NULL, ";");

    if (!amount_str)
    {
        LOG_ERROR("cant read amount%s", "");
        free(tr);
        free(line);
        return NULL;
    }

    if (sscanf(amount_str, "%d", &tr->amount) != 1)
    {
        LOG_ERROR("cant convert amount%s", "");
        free(tr);
        free(line);
        return NULL;
    }
    LOG_DEBUG("amount = %d", tr->amount);

    if (!(tr->message = strtok(NULL, ";")))
    {
        LOG_ERROR("cant read date%s", "");
        free(tr);
        free(line);
        return NULL;
    }
    LOG_DEBUG("message = %s", tr->message);

    if (strtok(NULL, ";"))
    {
        LOG_ERROR("there is more fields%s", "");
        free(tr);
        free(line);
        return NULL;
    }

    return tr;
}

void free_transaction(transaction_t *tr)
{
    free(tr->date);
    free(tr);
}
