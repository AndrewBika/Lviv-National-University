#include <stdio.h>

#define lenght(x) ((int) (sizeof(x) / sizeof((x)[0])))

// These defines just make the code easier to read.
#define TRUE 1
#define FALSE 0

// Implication function.
int imp(int a, int b)
{
    return !a || b;
}

// Equivavelnt function.
int equ(int a, int b)
{
    return imp(a, b) && imp(b, a);
}

// Gathers input from the person writing.
void gather_input(int values[], int lenght)
{
    for(int i = 0; i < lenght; i++)
    {
        int val = FALSE;
        do
        {
            printf("Please input a boolean value[%d]: \n", i);
            scanf("%d", &val);
        }
        while(val != TRUE && val != FALSE); // We check whether the input is valid.
        values[i] = val;
    }
}

int main()
{   
    int vals[3];

    gather_input(vals, lenght(vals));
   
    int *x = &vals[0];
    int *y = &vals[1]; 
    int *z = &vals[2];  

    int result = imp((*x || *y), imp((*y && *z), (*x || equ(*y, *z))));
    printf("The result is %d\n", result);
}