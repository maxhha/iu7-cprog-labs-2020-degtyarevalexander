#include "../inc/list.h"

char_list_t *create_char_list(char c)
{
    char_list_t *l = malloc(sizeof(char_list_t));

    if (l == NULL)
        return NULL;

    l->c = c;
    l->next = NULL;

    return l;
}

char_list_t *read_list_from_file(char *filename)
{
    FILE *f = fopen(filename, "r");

    if (f == NULL)
    {
        return NULL;
    }

    char_list_t *head = NULL, **pp = &head;
    int c = 0;

    while ((c = getc(f)) > 0 && c != '\n')
    {
        *pp = create_char_list(c);

        if (*pp == NULL)
        {
            free_char_list(head);
            fclose(f);
            return NULL;
        }

        pp = &(*pp)->next;
    }

    fclose(f);

    return head;
}

void free_char_list(char_list_t *head)
{
    char_list_t *p = head;

    while (p != NULL)
    {
        char_list_t *t = p->next;
        free(p);
        p = t;
    }
}

char_list_t *reverse(char_list_t *head)
{
    char_list_t *p = head, *pr = NULL;

    while (p != NULL)
    {
        char_list_t *next = p->next;

        p->next = pr;
        pr = p;

        p = next;
    }

    return pr;
}

int write_list_to_file(char *filename, char_list_t *head)
{
    FILE *f = fopen(filename, "w");

    if (f == NULL)
    {
        return EXIT_FAILURE;
    }

    for (; head != NULL; head = head->next)
    {
        fprintf(f, "%c", head->c);
    }

    fprintf(f, "\n");

    fclose(f);

    return EXIT_SUCCESS;
}
