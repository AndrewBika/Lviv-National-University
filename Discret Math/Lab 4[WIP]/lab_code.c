#include <stdio.h>
#include <math.h> // We depend on math to get pow().
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

#define SENTINEL 2147483647 // int array terminator. Is the max int number to be honest.

#define SET_SIZE 16 // Max amount of bits in our bitvector.
#define SET_MIN -2147483648
#define SET_MAX SENTINEL - 1 // We don't want to be any bigger or equal to SENTINEL.

#define relation(a, b) ((a < b) ? TRUE : FALSE)

int get_len(int* array)
{
    // Returns amount of elements in lazy_list_init-ed array.
    // Sometimes this could work better, on arrays that were lazy_init_list-ed.
    int i = 0;

    while(TRUE)
    {
        if(array[i] == SENTINEL)
        {
            return i;
        }
        i++;
    }
}

void lazy_list_init(int* array, int array_size)
{
    // Sets all the elements of an array to SENTINEL, for future use.
    for(int i = 0; i < array_size; i++)
    {
        array[i] = SENTINEL;
    }
}

int strisbin(char *str)
{
    // Returns FALSE if the given string contains letters or [^0-9]
    while(*str)
        if(!isdigit(*str++))
            return FALSE;
    return TRUE;
}

int gather_bitmap(char *msg){
    // Returns bitmap as decimal.
    char inp[SET_SIZE], *ptr;
    int res;
    do
    {
        printf("%s", msg);
        scanf("%s", inp);
        res = strtol(inp, &ptr + SET_SIZE, 2); // No greater than 16 bits of info, as that is our SET_SIZE.`
    }
    while(!strisbin(inp));
    return res & 65535;
}

// Set manipulation.
int is_in_array(int el, int* array)
{
    // Checks whether el is in array.
    for(int i = 0, len = get_len(array); i < len; i++)
    {
        if(el == array[i])
        {
            return TRUE;
        }
    }
    return FALSE;
}

int get_pos_in_set(int el, int* array)
{
    for(int i = 0, len = get_len(array); i < len; i++)
    {
        if(el == array[i])
        {
            return i;
        }
    }
    return -1; // Special case handling for el not being in array.
}

int add_to_set(int el, int* array)
{
    // Outputs TRUE if element was not yet in array, and FALSE else.
    if(!is_in_array(el, array))
    {
        array[get_len(array)] = el;
        return TRUE;
    }
    return FALSE;
}

void print_set(int* array)
{
    printf("{");
    for(int i = 0, len = get_len(array); i < len; i++)
    {
        if(i == len - 1)
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

int list2bitmap(int* array, int* universum)
{
    int bitmap = 0;

    for(int i = 0, len = get_len(array); i < len; i++)
    {
        bitmap += pow(2, get_pos_in_set(array[i], universum));
    }

    return bitmap;
}

int get_bitmap_size(int bitmap, int* universum)
{
    int bitmap_len = 0;
    int universum_len = get_len(universum);

    for(int i = 0; i < universum_len; i++)
    {
        if(bitmap & ((int) (pow(2, i))))
        {
            bitmap_len++;
        }
    }
    return bitmap_len > universum_len ? universum_len : bitmap_len;
}

void bitmap2list(int* list, int bitmap, int* universum)
{
    // Converts a bitmap value over to an array. Expects the list to be initialized with correct size, see get_bitmap_size().
    for(int i = 0, len = get_len(universum); i < len; i++)
    {
        if(bitmap & ((int) (pow(2, i))))
        {
            add_to_set(universum[i], list);
        }
    }
}

// to_compare parameter is either TRUE or FALSE, and checks whether func is reflexive or anti-reflexive.
int is_reflexive(int* list_A, int* list_B, int to_compare)
{
    if(to_compare != TRUE && to_compare != FALSE)
    {
        printf("Unknown reflexivity type.");
        return -1; // Error code.
    }

    int len_A = get_len(list_A);
    int len_B = get_len(list_B);
    if(len_A != len_B)
    {
        printf("The two sets are incompatible for reflexivity evaluation.\n");
        return -1;
    }

    for(int i = 0; i < len_A; i++)
    {
        if(relation(list_A[i], list_B[i]) != to_compare)
        {
            return FALSE;
        }
    }
    return TRUE;
}

int is_symmetrical(int* list_A, int* list_B, int to_compare)
{
    if(to_compare != TRUE && to_compare != FALSE)
    {
        printf("Unknown symmetry type.");
        return -1; // Error code.
    }

    int len_A = get_len(list_A);
    int len_B = get_len(list_B);
    if(len_A != len_B)
    {
        printf("The two sets are incompatible for symmetricity evaluation.\n");
        return -1;
    }
    if(len_A == 1)
    {
        printf("Can't evaluate symmetricity, as relativity matrix only contains one element.\n");
        return -1;
    }

    for(int i = 0; i < len_A; i++)
    {
        for(int j = 0; j < len_A; j++)
        {
            if(i == j)
            {
                continue;
            }
            if((relation(list_A[i], list_B[j]) * relation(list_A[j], list_B[i])) != to_compare)
            {
                return FALSE;
            }
        }
    }
    return TRUE;
}

int is_transitive(int* list_A, int* list_B, int to_compare)
{
    if(to_compare != TRUE && to_compare != FALSE)
    {
        printf("Unknown transitivity type.");
        return -1; // Error code.
    }

    int len_A = get_len(list_A);
    int len_B = get_len(list_B);
    int smaller_len = len_A > len_B ? len_B : len_A;

    for(int i = 0; i < len_A; i++)
    {
        for(int j = 0; j < len_B; j++)
        {
            for(int k = 0; k < smaller_len; k++)
            {
                if((relation(list_A[i], list_B[j]) * relation(list_A[j], list_B[k])) != (to_compare * relation(list_A[i], list_B[k])))
                {
                    return FALSE;
                }
            }
        }
    }
    return TRUE;
}

int main()
{
    int universum[SET_SIZE + 1]; // Bits in int limitation.
    lazy_list_init(universum, SET_SIZE + 1);
    for(int i = 0; i < SET_SIZE; i++)
    {
        universum[i] = i;
    }

    printf("Universum used is: ");
    print_set(universum);
    printf("\n");

    int bitmap_A = gather_bitmap("Enter A: ");
    int bitmap_B = gather_bitmap("Enter B: ");

    int Arr_A_len = get_bitmap_size(bitmap_A, universum);
    int Arr_A[Arr_A_len + 1];
    lazy_list_init(Arr_A, Arr_A_len + 1);
    bitmap2list(Arr_A, bitmap_A, universum);

    int Arr_B_len = get_bitmap_size(bitmap_B, universum);
    int Arr_B[Arr_B_len + 1];
    lazy_list_init(Arr_B, Arr_B_len + 1);
    bitmap2list(Arr_B, bitmap_B, universum);

    // This prints out the relation matrix.
    for(int i = 0; i < Arr_A_len; i++)
    {
        for(int j = 0; j < Arr_B_len; j++)
        {
            printf("%d ", relation(Arr_A[i], Arr_B[j]));
        }
        printf("\n");
    }
    // </> end relation matrix print.
    
    // Checking for reflexivity, we check if the main matrix diagonal is TRUE.
    int ref = is_reflexive(Arr_A, Arr_B, TRUE);
    if(ref != -1) // -1 is an error code, it will output error message instead.
    {
        printf(ref ? "The relation is reflexive.\n" : "The relation is not reflexive.\n");
    }

    // Checking for antireflexivity, we check if the main matrix diagonal is FALSE.
    int anti_ref = is_reflexive(Arr_A, Arr_B, FALSE);
    if(anti_ref != -1)
    {
        printf(anti_ref ? "The relation is antireflexive.\n" : "The relation is not antireflexive.\n");
    }

    // Checking for symmetry.
    int sym = is_symmetrical(Arr_A, Arr_B, TRUE);
    if(sym != -1)
    {
        printf(sym ? "The relation is symmetric.\n" : "The relation is not symmetric.\n");
    }

    // Checking for antisymmetry.
    int anti_sym = is_symmetrical(Arr_A, Arr_B, FALSE);
    if(anti_sym != -1)
    {
        printf(anti_sym ? "The relation is antisymmetrical.\n" : "The relation is not antisymmetrical.\n");
    }

    // Checking for transitivity.
    int tran = is_transitive(Arr_A, Arr_B, TRUE);
    if(tran != -1)
    {
        printf(tran ? "The relation is transitive.\n" : "The relation is not transitive.\n");
    }

    // Checking for antitransitivity.
    int anti_tran = is_transitive(Arr_A, Arr_B, FALSE);
    if(anti_tran != -1)
    {
        printf(anti_tran ? "The relation is antitransitive.\n" : "The relation is not antitransitive.\n");
    }
}