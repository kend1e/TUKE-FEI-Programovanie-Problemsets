#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdbool.h>

#include "bmp.h"
#include "transformations.h"

int main(int argc, char **argv)
{
    bool rot_right = 0, rot_left = 0;
    bool flip_x = 0, flip_y = 0;
    bool crop_f = 0;
    uint32_t crop_params[4];
    float scale_factor = 1.0f;
    bool colors_f = 0;
    char colors[4] = { 0 };
    char *file_input = NULL, *file_output = NULL;

    int opt; 
    while((opt = getopt(argc, argv, ":rlhvc:s:e:o:i:")) != -1)  
    {  
        switch(opt)  
        {
            case 'r':
                rot_right = 1;
                break;
            case 'l':
                rot_left = 1;
                break;
            case 'h':
                flip_x = 1;
                break;
            case 'v':
                flip_y = 1;
                break;
            case 'c':
            {
                size_t opt_size = strlen(optarg);
                if(opt_size <= 0)
                    break;

                crop_f = 1;

                size_t num_start_pos = 0;
                size_t param_index = 0;
                for(size_t i = 0; i < opt_size; ++i)
                {
                    if(optarg[i] == ',' || i == opt_size - 1)
                    {
                        if(i != opt_size - 1)
                            optarg[i] = 0;
                        crop_params[param_index++] = atoi(optarg + num_start_pos);
                        num_start_pos = i + 1;
                    }
                }

                break;  
            }
            case 's':
                scale_factor = (float) atof(optarg);
                break;
            case 'e':
                colors_f = 1;
                strcpy(colors, optarg);
                break;
            case 'o':
            {
                size_t opt_size = strlen(optarg);
                if(opt_size <= 0)
                    break;   

                file_output = malloc(opt_size + 1);

                strcpy(file_output, optarg);
                break;
            }
            case 'i':
            {
                size_t opt_size = strlen(optarg);
                if(opt_size <= 0)
                    break;   

                file_input = malloc(opt_size + 1);

                strcpy(file_input, optarg);
                break;
            }
        }
    }

    FILE *input = stdin;
    FILE *output = stdout;

    /*file_input = "file.bmp";
    file_output = "test.bmp";
    crop_f = 1;
    crop_params[0] = 1;
    crop_params[1] = 1;
    crop_params[2] = 2;
    crop_params[3] = 2;*/
    
    if(file_input != NULL)
        input = fopen(file_input, "r");

    if(file_output != NULL)
        output = fopen(file_output, "w+");

    struct bmp_image *image = read_bmp(input);
    struct bmp_image *image_tmp;

    if(rot_right)
    {
        image_tmp = rotate_right(image);
        free_bmp_image(image);
        image = image_tmp;
    }
    else if(rot_left)
    {
        image_tmp = rotate_left(image);
        free_bmp_image(image);
        image = image_tmp;
    }

    if(flip_x)
    {
        image_tmp = flip_horizontally(image);
        free_bmp_image(image);
        image = image_tmp;
    }
    if(flip_y)
    {
        image_tmp = flip_vertically(image);
        free_bmp_image(image);
        image = image_tmp;
    }

    if(crop_f)
    {
        image_tmp = crop(image, crop_params[0], crop_params[1], crop_params[2], crop_params[3]);
        free_bmp_image(image);
        image = image_tmp;
    }

    if(scale_factor != 1.0f)
    {
        image_tmp = scale(image, scale_factor);
        free_bmp_image(image);
        image = image_tmp;
    }

    if(colors_f)
    {
        image_tmp = extract(image, colors);
        free_bmp_image(image);
        image = image_tmp;
    }

    bool flag = write_bmp(output, image);

    free_bmp_image(image);

    if(input != stdin)
        fclose(input);

    if(output != stdout)
        fclose(output);

    return flag;
}