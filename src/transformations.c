#include "transformations.h"

#include <stdlib.h>

void transform_flip(image_t *image, void (*flip_function)()) {
    IMAGE_DATA_AS_3D_MATRIX(old_data, image);
    DATA_AS_3D_MATRIX(new_data, image, image->data = malloc(image->size));

    flip_function(image, old_data, new_data);

    free(old_data);
}

void transform_flip_h_core(image_t *i, byte old[i->height][i->width][i->depth], byte new[i->height][i->width][i->depth]) {
    for (int row = 0, last_pixel = i->width - 1; row < i->height; row++) {
        for (int col = 0; col < i->width; col++) {
            new[row][col][R] = old[row][last_pixel - col][R];
            new[row][col][G] = old[row][last_pixel - col][G];
            new[row][col][B] = old[row][last_pixel - col][B];
        }
    }
}

void transform_flip_v_core(image_t *i, byte old[i->height][i->width][i->depth], byte new[i->height][i->width][i->depth]) {
    for (int row = 0, last_row = i->height - 1; row < i->height; row++) {
        for (int col = 0; col < i->width; col++) {
            new[row][col][R] = old[last_row - row][col][R];
            new[row][col][G] = old[last_row - row][col][G];
            new[row][col][B] = old[last_row - row][col][B];
        }
    }
}

void transform_flip_h(image_t *image) {
    transform_flip(image, &transform_flip_h_core);
}

void transform_flip_v(image_t *image) {
    transform_flip(image, &transform_flip_v_core);
}
