#include "../inc/transaction.h"

transaction_t *create_transaction_from_line(char *line)
{
    LOG_DEBUG("create from \"%s\"", line);
    transaction_t *tr = malloc(sizeof(transaction_t));

    if (tr == NULL)
    {
        return NULL;
    }

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

transaction_t *copy_transaction(transaction_t *tr)
{
    transaction_t *t = malloc(sizeof(transaction_t));

    if (!t)
        return t;

    int line_len = (tr->message - tr->date) + strlen(tr->message) + 1;

    t->date = malloc(line_len);

    if (!t->date)
    {
        free(t);
        return NULL;
    }

    memcpy(t->date, tr->date, line_len);

    t->amount = tr->amount;
    t->message = tr->message - tr->date + t->date;

    return t;
}

void free_transaction(transaction_t *tr)
{
    free(tr->date);
    free(tr);
}
