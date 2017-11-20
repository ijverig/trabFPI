#include "transformations.h"

#include <stdlib.h>
#include <string.h>

void transform_flip(image_t *image, void (*flip_function)()) {
    IMAGE_DATA_AS_3D_MATRIX(old_data, image);
    DATA_AS_3D_MATRIX(new_data, image, image->data = malloc(image->size));

    flip_function(image, old_data, new_data);

    free(old_data);
}

void transform_flip_h_core(image_t *i, byte old[i->height][i->width][i->depth], byte new[i->height][i->width][i->depth]) {
    for (int row = 0, last_pixel = i->width - 1; row < i->height; row++) {
        for (int col = 0; col < i->width; col++) {
            memcpy(new[row][col], old[row][last_pixel - col], i->depth);
        }
    }
}

void transform_flip_v_core(image_t *i, byte old[i->height][i->width][i->depth], byte new[i->height][i->width][i->depth]) {
    for (int row = 0, last_row = i->height - 1; row < i->height; row++) {
        memcpy(new[row][0], old[last_row - row][0], i->width * i->depth);
    }
}

void transform_flip_h(image_t *image) {
    transform_flip(image, &transform_flip_h_core);
}

void transform_flip_v(image_t *image) {
    transform_flip(image, &transform_flip_v_core);
}
