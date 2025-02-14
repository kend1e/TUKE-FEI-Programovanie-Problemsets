#ifndef _TRANSFORMATIONS_H
#define _TRANSFORMATIONS_H

#include "bmp.h"


/**
 * Flips image horizontally.
 *
 * Creates copy of original file, which is horizontally flipped.
 * @arg image the image
 * @return the copy of image flipped horizontally given as argument or null, if there is no image (NULL given)
 */
struct bmp_image* flip_horizontally(const struct bmp_image* image);


/**
 * Flips image vertically.
 *
 * Creates copy of original file, which is vertically flipped.
 * @arg image the image
 * @return the copy of image flipped vertically given as argument or null, if there is no image (NULL given)
 */
struct bmp_image* flip_vertically(const struct bmp_image* image);

/**
 * Rotate image 90 degrees to the right.
 *
 * Creates copy of original file, which is rotated to the right.
 * @arg image the image
 * @return the copy of image rotated by 90 degrees to the right given as argument or null, if there is no image (NULL given)
 */
struct bmp_image* rotate_right(const struct bmp_image* image);

/**
 * Rotate image 90 degrees to the left.
 *
 * Creates copy of original file, which is rotated to the left.
 * @arg image the image
 * @return the copy of image rotated by 90 degrees to the left given as argument or null, if there is no image (NULL given)
 */
struct bmp_image* rotate_left(const struct bmp_image* image);

/**
 * Resize image height and width by scale factor.
 *
 * Creates copy of original file, which is proportionally scaled.
 * @arg image the image
 * @arg factor the ratio of corresponding sides of original and created image, factor > 1 created image is larger, factor < 1 created image is smaller
 * @return the copy of image scaled by factor given as argument or NULL, if there is no image (NULL given) or factor value is not valid
 */
struct bmp_image* scale(const struct bmp_image* image, float factor);


/**
 * Remove unwanted outer area from image.
 *
 * Creates copy of image containing only selected rectangular area.
 *
 * @arg image the image
 * @arg start_y top-left corner position on y-axis of selected area in the range <0, image->height>
 * @arg start_x top-left corner position on x-axis of selected area in the range <0, image->width>
 * @arg height the height of selected area in pixels in the range <1, image->height>
 * @arg width the width of selected area in pixels in the range <1, image->width>
 * @return the copy of image containing only selected area or null, if there is no image (NULL given) or area position is out of range
 */
struct bmp_image* crop(const struct bmp_image* image, const uint32_t start_y, const uint32_t start_x, const uint32_t height, const uint32_t width);


/**
 * Extract one or more color channels of image.
 *
 * Creates copy of image containing only selected color channels.
 *
 * @arg image the image
 * @arg colors_to_keep [bgr],b-blue, g-green, r-red
 * @return the copy of image containing only selected color channels or null, if there is no image (NULL given) or color definition is not valid.
 */
struct bmp_image* extract(const struct bmp_image* image, const char* colors_to_keep);
#endif
