#include <stdio.h>

#define OK 0
#define INPUT_ERR 1

void print_factor(int n)
{
    int i = 2;
    while (n != 1)
    {
        if (n % i == 0)
        {
            printf("%d ", i);
            n /= i;
        }
        else
        {
            i += 1;
        }
    }
    printf("\n");
}

int main()
{
    int n, rc;

    setbuf(stdout, NULL);
    printf("N:\n");

    rc = scanf("%d", &n);

    if (rc != 1 || rc == EOF || n <= 0)
    {
        printf("no no no\n");
        return INPUT_ERR;
    }
    
    print_factor(n);
 
    return OK;
}

