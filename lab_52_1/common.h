
#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>

#define XSTR(A) STR(A)
#define STR(A) #A

#define OK 0
#define EPARSE 1

#define MAX_STUDENTS 100
#define MAXLEN_LAST_NAME 25
#define MAXLEN_FIRST_NAME 10

struct Student
{
    char last_name[MAXLEN_LAST_NAME + 1];
    char first_name[MAXLEN_FIRST_NAME + 1];
    unsigned int marks[4];
};

struct Student get_from_file(FILE *f, int i);
struct Student get_from_array(struct Student *array, int i);
void set_in_file(FILE *f, struct Student student, int i);
void set_in_array(struct Student *array, struct Student student, int i);

int main_create(int argc, char **argv);
int main_sort_text(int argc, char **argv);
int main_sort_bin(int argc, char **argv);
int main_find_text(int argc, char **argv);
int main_find_bin(int argc, char **argv);
int main_delete_text(int argc, char **argv);
int main_delete_bin(int argc, char **argv);

int parse_file(FILE *f, int max_size, struct Student *array, int *array_len);
void printf_student(FILE *f, struct Student student);

#endif // __COMMON_H__
