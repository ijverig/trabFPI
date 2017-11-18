#include "transformations.h"

#include <stdlib.h>

void transform_flip_h(image_t *image) {
    IMAGE_DATA_AS_3D_MATRIX(image, old_data);
    DATA_AS_3D_MATRIX(image, new_data) (image->data = malloc(image->size));

    for (int row = 0, last_pixel = image->width - 1; row < image->height; row++) {
        for (int col = 0; col < image->width; col++) {
            new_data[row][col][R] = old_data[row][last_pixel - col][R];
            new_data[row][col][G] = old_data[row][last_pixel - col][G];
            new_data[row][col][B] = old_data[row][last_pixel - col][B];
        }
    }

    free(old_data);
}
