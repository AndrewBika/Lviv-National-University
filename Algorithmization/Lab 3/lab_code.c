#include <stdio.h>
#include <math.h>
#define M_PI 3.14159265358979323846

double y(double x)
{
    return -log( fabs(2 * sin(x / 2) ) );
}

double formula(int n, double x)
{
    return ( (cos( (double) n * x) ) / (double) n);
}

double gen_for_n(int n, double x)
{
    double sum = 0;

    for(int i = 1; i <= n; i++)
    {
        sum += formula(i, x);
    }

    return sum;
}

double gen_for_prec(double precision, double x)
{
    int n = 1;

    while(1)
    {
        double temp_gen = formula(n, x);
        if(fabs(temp_gen) < precision)
        {
            return gen_for_n(n, x);
        }
        n++;
    }
}

int main()
{
    double min_x = M_PI / 5.0;
    double max_x = (9.0 * M_PI) / 5.0;

    double step = (max_x - min_x) / 10.0;

    for(double x = min_x; x < max_x; x += step)
    {
        printf("x = %lf, y = %lf, y by n = %lf, y by eps = %lf\n", x, y(x), gen_for_n(40, x), gen_for_prec(0.0001, x));
    }
}