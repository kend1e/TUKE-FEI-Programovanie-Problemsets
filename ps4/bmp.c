#include <stdlib.h>

#include "bmp.h"

size_t round_to_4(size_t n);

struct bmp_image* read_bmp(FILE* stream)
{
    if(stream == NULL)
        return NULL;

    struct bmp_header *bmp_header = read_bmp_header(stream);

    if(bmp_header == NULL)
    {
        fprintf(stderr, "Error: This is not a BMP file.\n");
        return NULL;
    }

    struct pixel *bmp_data = read_data(stream, bmp_header);

    if(bmp_data == NULL)
    {
        fprintf(stderr, "Error: Corrupted BMP file.\n");
        free(bmp_header);
        return NULL;
    }

    struct bmp_image *image = malloc(sizeof(struct bmp_image));

    image->header = bmp_header;
    image->data = bmp_data;

    return image;
}

struct bmp_header* read_bmp_header(FILE* stream)
{
    if(stream == NULL)
        return NULL;

    size_t bmp_header_size = sizeof(struct bmp_header);
    struct bmp_header *bmp_header = calloc(1, bmp_header_size);

    fseek(stream, 0, SEEK_SET);

    if(fread(bmp_header, bmp_header_size, 1, stream) != 1)
    {
        free(bmp_header);
        return NULL;
    }

    if(bmp_header->type != 0x4D42)
    {
        free(bmp_header);
        return NULL;
    }

    return bmp_header;
}

struct pixel* read_data(FILE* stream, const struct bmp_header* header)
{
    if(stream == NULL || header == NULL)
        return NULL;

    size_t pixel_size = sizeof(struct pixel);
    size_t row_size = round_to_4(pixel_size * header->width);

    struct pixel *bmp_data = calloc(1, pixel_size * header->width * header->height);

    fseek(stream, header->offset, SEEK_SET);
    
    for(int i = 0; i < header->height; ++i)
    {
        if(fread(bmp_data + i * header->width, pixel_size * header->width, 1, stream) != 1)
        {
            free(bmp_data);
            return NULL;
        }
        fseek(stream, row_size - pixel_size * header->width, SEEK_CUR);
    }

    /*fseek(stream, header->offset, SEEK_SET);

    struct pixel *bmp_data = calloc(1, header->image_size);

    if(fread(bmp_data, header->image_size, 1, stream) != 1)
    {
        free(bmp_data);
        return NULL;
    }*/

    return bmp_data;
}

bool write_bmp(FILE* stream, const struct bmp_image* image)
{
    if(stream == NULL || image == NULL)
        return 0;

    size_t flag = 1;

    flag &= fwrite(image->header, sizeof(struct bmp_header), 1, stream);

    size_t pixel_size = sizeof(struct pixel);
    size_t row_size = round_to_4(pixel_size * image->header->width);

    fseek(stream, image->header->offset, SEEK_SET);

    for(int i = 0; i < image->header->height; ++i)
    {
        fwrite(image->data + i * image->header->width, pixel_size * image->header->width, 1, stream);
        fseek(stream, row_size - pixel_size * image->header->width, SEEK_CUR);
    }

    flag &= fwrite(image->data, image->header->image_size, 1, stream);

    return flag;
}

void free_bmp_image(struct bmp_image* image)
{
    if(image == NULL)
        return;
        
    free(image->header);
    free(image->data);
    free(image);
}