#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define max_amount(x) ((int) (sizeof(x) / sizeof((x)[0])))

int actual_lenght(int* array, int array_max_amount)
{
    int amount = 0;
    for(int i = 0; i < array_max_amount; i++)
    {
        if(array[i] < 0)
        {
            break;
        }
        amount++;
    }
    return amount;
}

void print_array(int* array, int array_lenght)
{
    printf("[");
    for(int i = 0; i < array_lenght - 1; i++)
    {
        printf("%d, ", array[i]);
    }
    printf("%d]\n", array[array_lenght - 1]);
}

void remove_first_zero(int* array, int array_lenght)
{
    int zero_found = 0;

    for(int i = 0; i < array_lenght; i++)
    {
        if(zero_found)
        {
            array[i - 1] = array[i];
        }
        else if(array[i] == 0)
        {
            zero_found = 1;
        }
    } 
}

void tweak_array(int* array, int array_lenght)
{
    int tweak_coeff = 0;

    for(int i = 0; i < array_lenght; i++)
    {
        if(i % 2 != 1)
        {
            continue;
        }

        for(int g = array_lenght + tweak_coeff; g > i; g--)
        {
            array[g + 1] = array[g];
        }
        tweak_coeff++;
        array[i + 1] = array[i - 1] + 2; 
    }
}

int main()
{
    srand(time(NULL));

    int array[40];

    for(int i = 0; i < 10; i++)
    {
        array[i] = rand() % 10;
    }

    printf("We are printing the array: ");
    print_array(array, actual_lenght(array, max_amount(array)));
    printf("\n");

    remove_first_zero(array, actual_lenght(array, actual_lenght(array, max_amount(array))));
    
    printf("We removed zeroes: ");
    print_array(array, actual_lenght(array, max_amount(array)));
    printf("\n");
    
    tweak_array(array, actual_lenght(array, max_amount(array)));

    printf("We are printing the final array: ");
    print_array(array, actual_lenght(array, max_amount(array)));
    printf("\n");
}