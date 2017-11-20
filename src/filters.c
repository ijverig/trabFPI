#include "filters.h"

void filter_grayscale(image_t *image) {
    for (int i = 0; i < image->size; i += 3) {
        byte luminance = .299 * image->data[i + R] +
                         .587 * image->data[i + G] +
                         .114 * image->data[i + B];
        image->data[i + R] = image->data[i + G] = image->data[i + B] = luminance;
    }
}
