#include "transformations.h"

#include <stdlib.h>

void transform_flip(image_t *image, byte (*flip_function)()) {
    IMAGE_DATA_AS_3D_MATRIX(old_data, image);
    DATA_AS_3D_MATRIX(new_data, image, image->data = malloc(image->size));

    for (int row = 0; row < image->height; row++) {
        for (int col = 0; col < image->width; col++) {
            new_data[row][col][R] = flip_function(image, col, row, R, old_data);
            new_data[row][col][G] = flip_function(image, col, row, G, old_data);
            new_data[row][col][B] = flip_function(image, col, row, B, old_data);
        }
    }

    free(old_data);
}

byte flipped_h(image_t *i, int x, int y, int z, byte m[i->height][i->width][i->depth]) {
    return m[y][i->width - 1 - x][z];
}

byte flipped_v(image_t *i, int x, int y, int z, byte m[i->height][i->width][i->depth]) {
    return m[i->height - 1 - y][x][z];
}

void transform_flip_h(image_t *image) {
    transform_flip(image, &flipped_h);
}

void transform_flip_v(image_t *image) {
    transform_flip(image, &flipped_v);
}
