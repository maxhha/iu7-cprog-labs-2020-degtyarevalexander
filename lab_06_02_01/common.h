#ifndef __COMMON_H__
#define __COMMON_H__

#define OK 0
#define ERR 1
#define MAX_NAME_LEN 25
#define MAX_OBJECTS 3000
#define EPS 0.000001

struct s_object
{
    char name[MAX_NAME_LEN + 1];
    double weight;
    double volume;
};

typedef struct s_object t_object;

#endif // __COMMON_H__
