#include "filters.h"

void filter_grayscale(image_t *image) {
    for (int i = 0; i < image->size; i += 3) {
        byte luminance = .299 * image->data[i + R] +
                         .587 * image->data[i + G] +
                         .114 * image->data[i + B];
        image->data[i + R] = image->data[i + G] = image->data[i + B] = luminance;
    }
}

void filter_quantize(image_t *image, byte levels) {
    for (int i = 0; i < image->size; i += 3) {
        byte level = (float)image->data[i] / 256 * levels;
        byte new_value = level * 256/levels + 128/levels;
        image->data[i + R] = image->data[i + G] = image->data[i + B] = new_value;
    }
}
