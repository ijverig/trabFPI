#include "filters.h"

byte clip_to_ubyte(int value)
{
    return (value < 0) ? 0 : (value > 255) ? 255 : value;
}

void filter(void (*component_function)(byte *, byte (*)(byte *, float), float),
            image_t *image,
            byte (*filter_function)(byte *, float),
            float info)
{
    for (int i = 0; i < image->size; i += 3) {
        component_function(&image->data[i], filter_function, info);
    }
}

void each_pixel(byte *pixel,
            byte (*filter_function)(byte *, float),
            float info)
{
    pixel[R] = pixel[G] = pixel[B] = filter_function(pixel, info);
}

void each_channel(byte *pixel,
            byte (*filter_function)(byte *, float),
            float info)
{
    pixel[R] = filter_function(&pixel[R], info);
    pixel[G] = filter_function(&pixel[G], info);
    pixel[B] = filter_function(&pixel[B], info);
}

byte luminance(byte *pixel, float _)
{
    byte luminance = .299 * pixel[R] +
                     .587 * pixel[G] +
                     .114 * pixel[B];
    return luminance;
}

void filter_grayscale(image_t *image)
{
    filter(each_pixel, image, luminance, 0);
}

byte quantize(byte *pixel, float levels)
{
    byte level = (float)*pixel/256 * levels;
    return level * 256/levels + 128/levels; // level * 256/levels + 1/2 * 256/levels
}

void filter_quantize(image_t *image, float levels)
{
    filter(each_channel, image, quantize, levels);
}

byte contrast(byte *value, float gain)
{
    return clip_to_ubyte(gain * *value);
}

void filter_contrast(image_t *image, float gain)
{
    filter(each_channel, image, contrast, gain);
}

byte negative(byte *value, float _)
{
    return 255 - *value;
}

void filter_negative(image_t *image)
{
    filter(each_channel, image, negative, 0);
}
