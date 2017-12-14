#include "image.h"

void filter_grayscale(image_t *image);
void filter_quantize(image_t *image, float levels);
void filter_contrast(image_t *image, float gain);
void filter_negative(image_t *image);
