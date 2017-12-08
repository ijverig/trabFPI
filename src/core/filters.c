#include "filters.h"

void filter(image_t *image,
            byte (*filter_function)(byte *, byte),
            byte info)
{
    for (int i = 0; i < image->size; i += 3) {
        image->data[i + R] = image->data[i + G] = image->data[i + B] = filter_function(&image->data[i], info);
    }
}

byte luminance(byte *pixel, byte _)
{
    byte luminance = .299 * pixel[R] +
                     .587 * pixel[G] +
                     .114 * pixel[B];
    return luminance;
}

void filter_grayscale(image_t *image)
{
    filter(image, luminance, 0);
}

byte quantize(byte *pixel, byte levels)
{
    byte level = (float)*pixel/256 * levels;
    return level * 256/levels + 128/levels; // level * 256/levels + 1/2 * 256/levels
}


void filter_quantize(image_t *image, byte levels)
{
    filter(image, quantize, levels);
}
