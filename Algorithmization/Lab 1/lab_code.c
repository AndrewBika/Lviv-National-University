#include <stdio.h>
#include <cs50.h>
#include <math.h>

void task1() 
/* This is the first task given by Gasko, as a part of my lab. Where we see the difference with calculating in doubles and floats.*/
{
    float a1 = 1000;
    float b1 = 0.0001;

    double a2 = 1000;
    double b2 = 0.0001;

    float res1 = (pow(a1 - b1, 2) - (pow(a1, 2) - 2 * a1 * b1)) / pow(b1, 2);
    double res2 = (pow(a2 - b2, 2) - (pow(a2, 2) - 2 * a2 * b2)) / pow(b2, 2);

    printf("The results of task 1 are, as follows:\n");
    printf("Calculation in float: %f\n", res1);
    printf("Calculation i double: %f\n", res2);
}

void task2()
/* This is the second task given by Gasko, where we see how unary operations work.*/
{
    printf("Enter first number to compare\n");
    int n = GetInt();
    printf("Enter second number to compare\n");
    int m = GetInt();

    printf("The results of task 2 are, as follows:\n");
    printf("++n * ++m result: %d\n", ++n*++m);
    printf("m++ < n result: %d\n", m++<n);
    printf("n++ > m result: %d\n", n++<m);
}

int main()
{
    task1();
    task2();
}