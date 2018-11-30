#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

#define BIG_NUMBER 256

int factorial(int);
void build_sequence(int*, int);
int get_next_lex(int*, int);
void print_lex(int);
void print_binom(int);

int main()
{
    int n = 0;
    printf("Please enter your \"n\": ");
    scanf("%d", &n);

    print_lex(n);

    int power = 0;
    printf("Please enter the power you would like to put equation (x - y) to: ");
    scanf("%d", &power);

    print_binom(power);
}

int factorial(int n)
{
    if(n == 0)
    {
        return 1;
    }
    return n * factorial(n - 1);
}

void build_sequence(int* sequence, int len)
{
    for(int i = 0; i < len; i++)
    {
        sequence[i] = i + 1;
    }
}

int get_next_lex(int* seq, int len)
{
    if(len == 0)
    {
        return FALSE;
    }

    // Currently i plays role of a pivot we will turn on.
    int i = len - 1;
    while(i > 0 && seq[i - 1] >= seq[i])
    {
        i--;
    }
    if(i == 0)
    {
        return FALSE;
    }

    // Currently j is a successor of pivot, which the twol we will replace.
    int j = len - 1;
    while(j > 0 && seq[j] <= seq[i - 1])
    {
        j--;
    }

    int temp = seq[i - 1];
    seq[i - 1] = seq[j];
    seq[j] = temp;

    // Inversing everything after pivot.
    j = len - 1;
    while(i < j)
    {
        temp = seq[i];
        seq[i] = seq[j];
        seq[j] = temp;
        i++;
        j--;
    }
    return TRUE;
}

void print_lex(int n)
{
    int* sequence = malloc(sizeof(int) * n);
    build_sequence(sequence, n);

    // Printing first made sequence.
    for(int i = 0; i < n; i++)
    {
        printf("%d ", sequence[i]);
    }
    printf("\n");

    while(TRUE)
    {
        if(get_next_lex(sequence, n))
        {
            // Printing next possible sequence.
            for(int i = 0; i < n; i++)
            {
                printf("%d ", sequence[i]);
            }
            printf("\n");
        }
        else
        {
            // If not possible, ending the function.
            break;
        }
    }

    free(sequence);
}

void print_binom(int power)
{
    printf("(x - y) ^ %d = ", power);
    int power_fact = factorial(power);

    for(int i = 0; i <= power; i++)
    {
        int coeff = power_fact / (factorial(i) * factorial(power - i));

        if((power - i) != 0 && i != 0)
        {
            if(coeff != 1)
            {
                printf("%dx^%dy^%d", coeff, power - i, i);
            }
            else
            {
                printf("x^%dy^%d", power - i, i);
            }
        }
        else if((power - i) != 0)
        {
            if(coeff != 1)
            {
                printf("%dx^%d", coeff, power - i);
            }
            else
            {
                printf("x^%d", power - i);
            }
        }
        else if(i != 0)
        {
            if(coeff != 1)
            {
                printf("%dy^%d", coeff, i);
            }
            else
            {
                printf("y^%d", i);
            }
        }

        if(i != power)
        {
            if(i % 2 == 0)
            {
                printf(" - ");
            }
            else
            {
                printf(" + ");
            }
        }
    }
    printf("\n");
}