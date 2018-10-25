#include <stdio.h>
#include <math.h> // We depend on math to get pow().

#define TRUE 1
#define FALSE 0

#define SENTINEL 2147483647 // int array terminator. Is the max int number to be honest.

#define SET_MIN -2147483648
#define SET_MAX SENTINEL - 1 // We don't want to be any bigger than SENTINEL.

int get_len(int* array)
{
    // Sometimes this could work better, on arrays that were lazy_init_list-ed.
    int i = 0;

    while(1)
    {
        if(array[i] == SENTINEL)
        {
            return i;
        }
        i++;
    }
}

int get_int(char* message, int min, int max)
{
    // Gets the int input, and displays message.
    int i = 0;

    int abnormal = TRUE;

    while(abnormal)
    {
        printf("%s", message);
        scanf("%d", &i);
        if(i % 1 != 0)
        {
            printf("Entered number is not integer, try again.\n");
        }
        else if(i > max)
        {
            printf("Entered number is too big, try again.\n");
        }
        else if(i < min)
        {
            printf("Entered number is too small, try again.\n");
        }
        else
        {
            abnormal = FALSE;
        }
    }

    return i;
}

void lazy_list_init(int* array, int array_size)
{
    // Sets all the elements of an array to SENTINEL, for future use.
    for(int i = 0; i < array_size; i++)
    {
        array[i] = SENTINEL;
    }
}

int is_in_array(int el, int* array, int array_size)
{
    // Checks whether el is in array.
    for(int i = 0; i < array_size; i++)
    {
        if(el == array[i])
        {
            return TRUE;
        }
    }
    return FALSE;
}

int get_pos_in_set(int el, int* array, int array_size)
{
    for(int i = 0; i < array_size; i++)
    {
        if(el == array[i])
        {
            return i;
        }
    }
    return -1; // Special case handling for el not being in array.
}

int get_int_for_set(char* message, int* array, int array_size)
{
    // get_int() but checks whether element is already in array.
    int i = get_int(message, SET_MIN, SET_MAX);
    while(is_in_array(i, array, array_size))
    {
        printf("The entered value is already in set.\n");
        i = get_int(message, SET_MIN, SET_MAX);
    }

    return i;
}

int add_to_set(int el, int* array, int array_size, int position)
{
    // Outputs TRUE if element was not yet in array, and FALSE else.
    if(!is_in_array(el, array, array_size))
    {
        array[position] = el;
        return TRUE;
    }
    return FALSE;
}

int get_uni_size(int* array_A, int size_A, int* array_B, int size_B)
{
    // Universum size getter.
    int uni_size = 0;
    int temp_set[size_A + size_B];
    int temp_pos = 0;
    lazy_list_init(temp_set, size_A + size_B);

    for(int i = 0; i < size_A; i++)
    {
        if(!is_in_array(array_A[i], temp_set, size_A + size_B))
        {
            uni_size++;
            temp_set[temp_pos] = array_A[i];
            temp_pos++;
        }
    }

    for(int i = 0; i < size_B; i++)
    {
        if(!is_in_array(array_B[i], temp_set, size_A + size_B))
        {
            uni_size++;
            temp_set[temp_pos] = array_B[i];
            temp_pos++;
        }
    }
    return uni_size;
}

void create_universum(int* uni, int uni_size, int* array_A, int size_A, int* array_B, int size_B)
{
    // Creates an array of all unique values from array_A and array_B.
    int uni_pos = 0;

    for(int i = 0; i < size_A; i++)
    {
        if(add_to_set(array_A[i], uni, uni_size, uni_pos))
        {
            uni_pos++;
        }
    }

    for(int i = 0; i < size_B; i++)
    {
        if(add_to_set(array_B[i], uni, uni_size, uni_pos))
        {
            uni_pos++;
        }
    }
}

void print_array(int* array, int array_size)
{
    printf("{");
    for(int i = 0; i < array_size; i++)
    {
        if(i == array_size - 1)
        {
            printf("%d", array[i]);
        }
        else
        {
            printf("%d, ", array[i]);
        }
    }
    printf("}");
}

int list2bitmap(int* array, int array_size, int* universum, int uni_size)
{
    int bitmap = 0;

    for(int i = 0; i < array_size; i++)
    {
        bitmap += pow(2, get_pos_in_set(array[i], universum, uni_size));
    }

    return bitmap;
}

int get_bitmap_size(int bitmap, int* universum, int uni_size)
{
    int bitmap_len = 0;

    for(int i = 0; i < uni_size; i++)
    {
        if(bitmap & ((int) (pow(2, i))))
        {
            bitmap_len++;
        }
    }
    return bitmap_len;
}

void bitmap2list(int* list, int list_len, int bitmap, int* universum, int uni_size)
{
    // Converts a bitmap value over to an array. Expects the list to be initialized with correct size, see get_bitmap_size().
    int bit_pos = 0;
    for(int i = 0; i < uni_size; i++)
    {
        if(bitmap & ((int) (pow(2, i))))
        {
            add_to_set(universum[i], list, list_len, bit_pos);
            bit_pos++;
        }
    }
}

int main()
{
    int size_A = get_int("Please input size of the first array: ", 1, 16);
    int A[size_A];
    lazy_list_init(A, size_A);

    for(int i = 0; i < size_A; i++)
    {
        A[i] = get_int_for_set("Please input element: ", A, size_A);
    }
    
    int size_B = get_int("Please input size of the second array: ", 1, 16);
    int B[size_B];
    lazy_list_init(B, size_B);

    for(int i = 0; i < size_B; i++)
    {
        B[i] = get_int_for_set("Please input element: ", B, size_B);
    }

    int uni_size = get_uni_size(A, size_A, B, size_B);
    int universum[uni_size];
    lazy_list_init(universum, uni_size);

    create_universum(universum, uni_size, A, size_A, B, size_B);

    printf("First entered array: ");
    print_array(A, size_A);
    printf("\n");

    printf("Second entered array: ");
    print_array(B, size_B);
    printf("\n");

    // The task is below.

    int A_bitmap = list2bitmap(A, size_A, universum, uni_size);
    int B_bitmap = list2bitmap(B, size_B, universum, uni_size);

    // This is the intersection.
    int C_bitmap = A_bitmap & B_bitmap;

    int size_C = get_bitmap_size(C_bitmap, universum, uni_size);
    int C[size_C];
    lazy_list_init(C, size_C);

    bitmap2list(C, size_C, C_bitmap, universum, uni_size);
    printf("Result of intersection. between first and second arrays: ");
    print_array(C, size_C);
    printf("\n");
    // End intersection.

    // This is the subtraction operation.
    int D_bitmap = A_bitmap & ~B_bitmap;

    int size_D = get_bitmap_size(D_bitmap, universum, uni_size);
    int D[size_D];
    lazy_list_init(D, size_D);

    bitmap2list(D, size_D, D_bitmap, universum, uni_size);
    printf("Result of subtraction between first and second arrays: ");
    print_array(D, size_D);
    printf("\n");
    // End subtraction operation.
}