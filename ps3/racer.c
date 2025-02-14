#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define PRECISION 0.0000001

#define INITIAL_OFFSET 0.0000001

bool is_enough_precision(double x, double x_next, double x_prev);
double calc_newton_iteration(double x, int parts_count, int distance_arr[parts_count], int speed_arr[parts_count], double t);
double calc_func_value(double x, int parts_count, int distance_arr[parts_count], int speed_arr[parts_count]);
double calc_func_derivative_value(double x, int parts_count, int distance_arr[parts_count], int speed_arr[parts_count]);

int main()
{
    int parts_count, total_time;
    scanf("%d %d", &parts_count, &total_time);

    int distance_arr[parts_count];
    int speed_arr[parts_count];

    double x0 = 0;

    for(int i = 0; i < parts_count; ++i)
    {
        scanf("%d %d", distance_arr + i, speed_arr + i);

        if(i == 0 || -speed_arr[i] > x0)
            x0 = -speed_arr[i] + INITIAL_OFFSET;
        else if(-speed_arr[i] == x0)
            x0 += INITIAL_OFFSET;
    }

    double x, x_next, x_prev;

    x_prev = calc_newton_iteration(x0, parts_count, distance_arr, speed_arr, total_time);
    x = calc_newton_iteration(x_prev, parts_count, distance_arr, speed_arr, total_time);
    x_next = calc_newton_iteration(x, parts_count, distance_arr, speed_arr, total_time);

    while(!is_enough_precision(x, x_next, x_prev))
    {
        x_prev = x;
        x = x_next;
        x_next = calc_newton_iteration(x, parts_count, distance_arr, speed_arr, total_time);
    }

    printf("%lf", x_next);
}

bool is_enough_precision(double x, double x_next, double x_prev)
{
    if(x - x_prev == 0.0 || x - x_next == 0.0)
        return true;
    double abs_v = fabs((x_next - x) / (1.0 - (x_next - x) / (x - x_prev)));
    return abs_v < PRECISION;
}

double calc_newton_iteration(double x, int parts_count, int distance_arr[parts_count], int speed_arr[parts_count], double t)
{
    return x - (calc_func_value(x, parts_count, distance_arr, speed_arr) - t) / calc_func_derivative_value(x, parts_count, distance_arr, speed_arr);
}

double calc_func_value(double x, int parts_count, int distance_arr[parts_count], int speed_arr[parts_count])
{
    double sum = 0.0;

    for(int i = 0; i < parts_count; ++i)
        sum += distance_arr[i] / ((double)speed_arr[i] + x);

    return sum;
}

double calc_func_derivative_value(double x, int parts_count, int distance_arr[parts_count], int speed_arr[parts_count])
{
    double sum = 0.0;

    for(int i = 0; i < parts_count; ++i)
        sum -= distance_arr[i] / pow(speed_arr[i] + x, 2);

    return sum;
}