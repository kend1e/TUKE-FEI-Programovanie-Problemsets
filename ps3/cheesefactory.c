#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define SPHERE_INPUT_MODIFIER 1000.0

#define CUBE_SIDE_SIZE 100.0
#define CUBE_VOLUME (CUBE_SIDE_SIZE * CUBE_SIDE_SIZE * CUBE_SIDE_SIZE)

#define PRECISION 0.0000001

#define PI 3.14159265358979323846

struct sphere {
    double x, y, z;
    double radius;
};

bool is_enough_precision(double x, double x_next, double x_prev);
double piece_calc_newton_iteration(double shift_z, double size_z, int spheres_count, struct sphere sphere_arr[spheres_count], double target_volume);
double piece_calc_volume(double shift_z, double size_z, int spheres_count, struct sphere sphere_arr[spheres_count], bool deriv);
double sphere_calc_overlap_volume(double shift_z, double size_z, const struct sphere *sphere, bool deriv);
double sphere_calc_cap_volume(const struct sphere *sphere, double h, bool deriv);
double sphere_calc_volume(const struct sphere *sphere);

int main()
{
    int spheres_count, pieces_count;
    scanf("%d %d", &spheres_count, &pieces_count);

    struct sphere sphere_arr[spheres_count];

    double total_volume = CUBE_VOLUME;

    for(int i = 0; i < spheres_count; ++i)
    {
        scanf("%lf %lf %lf %lf", &sphere_arr[i].radius, &sphere_arr[i].x, &sphere_arr[i].y, &sphere_arr[i].z);

        sphere_arr[i].radius /= SPHERE_INPUT_MODIFIER;
        sphere_arr[i].x /= SPHERE_INPUT_MODIFIER;
        sphere_arr[i].y /= SPHERE_INPUT_MODIFIER;
        sphere_arr[i].z /= SPHERE_INPUT_MODIFIER;

        total_volume -= sphere_calc_volume(sphere_arr + i);
    }

    double piece_volume = total_volume / (double)pieces_count;
    double piece_size_z = CUBE_SIDE_SIZE / (double)pieces_count;

    double x, x_next, x_prev;
    double cur_pos = 0.0;

    for(int i = 0; i < pieces_count; ++i)
    {
        x_prev = piece_calc_newton_iteration(cur_pos, piece_size_z, spheres_count, sphere_arr, piece_volume);
        x = piece_calc_newton_iteration(cur_pos, x_prev, spheres_count, sphere_arr, piece_volume);
        x_next = piece_calc_newton_iteration(cur_pos, x, spheres_count, sphere_arr, piece_volume);

        while(!is_enough_precision(x, x_next, x_prev))
        {
            x_prev = x;
            x = x_next;
            x_next = piece_calc_newton_iteration(cur_pos, x, spheres_count, sphere_arr, piece_volume);
        }

        printf("%lf\n", x_next);

        cur_pos += x_next;
    }
}

bool is_enough_precision(double x, double x_next, double x_prev)
{
    if(x - x_prev == 0.0 || x - x_next == 0.0)
        return true;
    double abs_v = fabs((x_next - x) / (1.0 - (x_next - x) / (x - x_prev)));
    return abs_v < PRECISION;
}

double piece_calc_newton_iteration(double shift_z, double size_z, int spheres_count, struct sphere sphere_arr[spheres_count], double target_volume)
{
    double d = (piece_calc_volume(shift_z, size_z, spheres_count, sphere_arr, false) - target_volume) / piece_calc_volume(shift_z, size_z, spheres_count, sphere_arr, true);
    return size_z - d;
}

double piece_calc_volume(double shift_z, double size_z, int spheres_count, struct sphere sphere_arr[spheres_count], bool deriv)
{
    double volume = CUBE_SIDE_SIZE * CUBE_SIDE_SIZE * (deriv ? 1.0 : size_z);

    for(int i = 0; i < spheres_count; ++i)
        volume -= sphere_calc_overlap_volume(shift_z, size_z, sphere_arr + i, deriv);

    return volume;
}

double sphere_calc_overlap_volume(double shift_z, double size_z, const struct sphere *sphere, bool deriv)
{
    double max_z = shift_z + size_z;

    if(sphere->z + sphere->radius <= shift_z)
        return 0.0;
    
    if(sphere->z - sphere->radius >= max_z)
        return 0.0;

    double cap_volume = 0.0;

    bool right_cut = sphere->z + sphere->radius > max_z;
    bool left_cut = sphere->z - sphere->radius < shift_z;

    if(!deriv)
        cap_volume += sphere_calc_volume(sphere);

    if(right_cut)
        cap_volume -= sphere_calc_cap_volume(sphere, sphere->z + sphere->radius - max_z, deriv);
    if(left_cut)
        cap_volume -= sphere_calc_cap_volume(sphere, shift_z - sphere->z + sphere->radius, deriv);

    return cap_volume;
}

double sphere_calc_cap_volume(const struct sphere *sphere, double h, bool deriv)
{
    if(deriv)
        return PI * h * (2.0 * sphere->radius - h);
    return (PI * h * h * (3.0 * sphere->radius - h)) / 3.0;
}

double sphere_calc_volume(const struct sphere *sphere)
{
    return (4.0 * PI * pow(sphere->radius, 3.0)) / 3.0;
}