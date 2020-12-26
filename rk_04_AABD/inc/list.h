#ifndef __LIST_H__
#define __LIST_H__

#include <stdlib.h>
#include <stdio.h>

typedef struct char_list_s char_list_t;

struct char_list_s
{
    char c;
    char_list_t *next;
};

char_list_t *read_list_from_file(char *filename);
char_list_t *reverse(char_list_t *head);
int write_list_to_file(char *filename, char_list_t *head);
void free_char_list(char_list_t *head);

#endif // __LIST_H__
