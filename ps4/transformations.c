#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "transformations.h"

struct bmp_image *image_modify(const struct bmp_image* image, const void(*modify_func)(const struct bmp_image* image_src, struct bmp_image* image_dst));

struct pixel *get_pixel(const struct bmp_image *image, size_t x, size_t y, bool pad);

size_t round_to_4(size_t n);

void flip_horizontally_impl(const struct bmp_image* image_src, struct bmp_image* image_dst)
{
    uint32_t width = image_src->header->width;
    uint32_t height = image_src->header->height;

    for(size_t i = 0; i < width; ++i)
        for(size_t j = 0; j < height; ++j)
            *get_pixel(image_dst, i, j, false) = *get_pixel(image_src, width - i - 1, j, false);
}

struct bmp_image* flip_horizontally(const struct bmp_image* image)
{
    return image_modify(image, &flip_horizontally_impl);
}

void flip_vertically_impl(const struct bmp_image* image_src, struct bmp_image* image_dst)
{
    uint32_t width = image_src->header->width;
    uint32_t height = image_src->header->height;

    for(size_t i = 0; i < width; ++i)
        for(size_t j = 0; j < height; ++j)
            *get_pixel(image_dst, i, j, false) = *get_pixel(image_src, i, height - j - 1, false);
}

struct bmp_image* flip_vertically(const struct bmp_image* image)
{
    return image_modify(image, &flip_vertically_impl);
}

void rotate_right_impl(const struct bmp_image* image_src, struct bmp_image* image_dst)
{
    uint32_t width = image_src->header->width;
    uint32_t height = image_src->header->height;

    image_dst->header->width = height;
    image_dst->header->height = width;

    image_dst->header->image_size = round_to_4(sizeof(struct pixel) * image_dst->header->width) * image_dst->header->height;
    image_dst->header->size = image_dst->header->offset + image_dst->header->image_size;

    for(size_t i = 0; i < width; ++i)
        for(size_t j = 0; j < height; ++j)
            *get_pixel(image_dst, j, i, false) = *get_pixel(image_src, width - i - 1, j, false);
}

struct bmp_image* rotate_right(const struct bmp_image* image)
{
    return image_modify(image, &rotate_right_impl);
}

void rotate_left_impl(const struct bmp_image* image_src, struct bmp_image* image_dst)
{
    uint32_t width = image_src->header->width;
    uint32_t height = image_src->header->height;

    image_dst->header->width = height;
    image_dst->header->height = width;

    image_dst->header->image_size = round_to_4(sizeof(struct pixel) * image_dst->header->width) * image_dst->header->height;
    image_dst->header->size = image_dst->header->offset + image_dst->header->image_size;

    for(size_t i = 0; i < width; ++i)
        for(size_t j = 0; j < height; ++j)
            *get_pixel(image_dst, j, i, false) = *get_pixel(image_src, i, height - j - 1, false);
}

struct bmp_image* rotate_left(const struct bmp_image* image)
{
    return image_modify(image, &rotate_left_impl);
}

struct bmp_image* scale(const struct bmp_image* image, float factor)
{
    if(image == NULL || factor <= 0.0f)
        return NULL;

    struct bmp_image *new_image = malloc(sizeof(struct bmp_image));
    new_image->header = malloc(sizeof(struct bmp_header));
    memcpy(new_image->header, image->header, sizeof(struct bmp_header));

    size_t width = (size_t) round(image->header->width * factor);
    size_t height = (size_t) round(image->header->height * factor);

    size_t pixel_size = sizeof(struct pixel);
    size_t data_size = round_to_4(pixel_size * width) * height;

    new_image->header->width = width;
    new_image->header->height = height;
    new_image->header->image_size = data_size;
    new_image->header->size = new_image->header->offset + new_image->header->image_size;

    size_t width_old = image->header->width;
    size_t height_old = image->header->height;

    new_image->data = calloc(1, data_size);

    for(size_t i = 0; i < width; ++i)
        for(size_t j = 0; j < height; ++j)
        {
            size_t i_n = i * width_old / width;
            size_t j_n = j * height_old / height;
            *get_pixel(new_image, i, j, false) = *get_pixel(image, i_n, j_n, false);
        }
    
    return new_image;
}

struct bmp_image* crop(const struct bmp_image* image, const uint32_t _start_y, const uint32_t start_x, const uint32_t height, const uint32_t width)
{
    if(image == NULL)
        return NULL;

    if(width <= 0 || height <= 0)
        return NULL;

    if(start_x < 0 || _start_y < 0)
        return NULL;

    if((start_x + width) > image->header->width || (_start_y + height) > image->header->height)
        return NULL;

    uint32_t start_y = image->header->height - _start_y - height;

    struct bmp_image *new_image = malloc(sizeof(struct bmp_image));
    new_image->header = malloc(sizeof(struct bmp_header));
    memcpy(new_image->header, image->header, sizeof(struct bmp_header));

    size_t pixel_size = sizeof(struct pixel);
    size_t data_size = round_to_4(pixel_size * width) * height;

    new_image->header->width = width;
    new_image->header->height = height;
    new_image->header->image_size = data_size;
    new_image->header->size = new_image->header->offset + new_image->header->image_size;

    new_image->data = calloc(1, data_size);

    for(size_t i = start_x; i < start_x + width; ++i)
        for(size_t j = start_y; j < start_y + height; ++j)
            *get_pixel(new_image, i - start_x, j - start_y, false) = *get_pixel(image, i, j, false);
    
    return new_image;
}

struct bmp_image* extract(const struct bmp_image* image, const char* colors_to_keep)
{
    if(image == NULL || colors_to_keep == NULL)
        return NULL;

    uint32_t mask = 0;

    size_t len = strlen(colors_to_keep);

    if(len <= 0 || len > 3)
        return NULL;

    for(size_t i = 0; i < len; ++i) {
        char c = colors_to_keep[i];
        switch (c)
        {
        case 'r':
            mask |= 0xFF0000;
            break;
        case 'g':
            mask |= 0x00FF00;
            break;
        case 'b':
            mask |= 0x0000FF;
            break;
        default:
            return NULL;
        }
    }

    struct bmp_image *new_image = malloc(sizeof(struct bmp_image));
    new_image->header = malloc(sizeof(struct bmp_header));
    memcpy(new_image->header, image->header, sizeof(struct bmp_header));

    size_t image_size = image->header->width * image->header->height;
    size_t data_size = sizeof(struct pixel) * image->header->width * image->header->height;

    new_image->data = calloc(1, data_size);
    memcpy(new_image->data, image->data, data_size);

    if(mask != 0xFFFFFF)
    {
        for(size_t i = 0; i < image_size; ++i)
        {
            new_image->data[i].red &= (mask & 0xFF0000) >> 16;
            new_image->data[i].green &= (mask & 0x00FF00) >> 8;
            new_image->data[i].blue &= (mask & 0x0000FF) >> 0;
        }
    }

    return new_image;
}

struct bmp_image *image_modify(const struct bmp_image* image, const void(*modify_func)(const struct bmp_image* image_src, struct bmp_image* image_dst))
{
    if(image == NULL || image->header == NULL || image->data == NULL)
        return NULL;

    struct bmp_image *new_image = malloc(sizeof(struct bmp_image));
    new_image->header = malloc(sizeof(struct bmp_header));
    memcpy(new_image->header, image->header, sizeof(struct bmp_header));

    new_image->data = calloc(1, new_image->header->image_size);

    modify_func(image, new_image);
    
    return new_image;
}

struct pixel *get_pixel(const struct bmp_image *image, size_t x, size_t y, bool pad)
{
    size_t row_size = sizeof(struct pixel) * image->header->width;

    if(pad)
        row_size = round_to_4(row_size);

    uint8_t *data = (uint8_t *) image->data;

    return (struct pixel *) (data + y * row_size + x * sizeof(struct pixel));
}

size_t round_to_4(size_t n)
{
    return n % 4 ? (n - n % 4 + 4) : n;
}