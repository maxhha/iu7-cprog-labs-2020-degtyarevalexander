#include "../inc/file.h"

node_t *read_csv(char *filename)
{
    FILE *f = fopen(filename, "r");

    if (!f)
    {
        LOG_ERROR("cant open file%s", "");
        return NULL;
    }

    node_t *head = NULL;
    node_t *tail = NULL;

    char *buf = NULL;
    size_t buf_size = 0;
    int readed;

    while ((readed = getline(&buf, &buf_size, f)) > 0)
    {
        buf[readed - 1] = '\0';
        LOG_DEBUG("readed \"%s\"", buf);
        transaction_t *tr = create_transaction_from_line(buf);

        if (!tr)
        {
            LOG_ERROR("fail create transaction%s", "");
            free_list(head, (void (*)(void *)) free_transaction);
            head = NULL;
            break;
        }

        node_t *p = malloc(sizeof(node_t));

        if (!p)
        {
            LOG_ERROR("fail to malloc%s", "");
            free_transaction(tr);
            free_list(head, (void (*)(void *)) free_transaction);
            head = NULL;
            break;
        }

        p->data = tr;
        p->next = NULL;

        if (tail)
        {
            tail->next = p;
            tail = p;
        }
        else
        {
            head = tail = p;
        }
    }

    fclose(f);

    return head;
}

void write_csv(char *filename, node_t *head)
{
    FILE *f = fopen(filename, "w");

    if (!f)
    {
        LOG_ERROR("cant open file%s", "");
        return;
    }

    for (node_t *p = head; p; p = p->next)
    {
        transaction_t *tr = p->data;
        fprintf(f, "%s;%d;%s\n", tr->date, tr->amount, tr->message);
    }

    fclose(f);
}
