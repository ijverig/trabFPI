#include <stdio.h>

#include "image.h"
#include "transformations.h"
#include "filters.h"

int main(int argc, char const *argv[]) {
    image_t image = image_create_from_file(argv[1]);
    image_t image_buffer = image_create_from_image(image);

    // transform_flip_h(&image_buffer);
    // transform_flip_v(&image_buffer);
    filter_grayscale(&image_buffer);

    image_save(image_buffer, argv[2]);

    image_destroy(image);
    image_destroy(image_buffer);

    printf("in: %s  \n", argv[1]);
    printf("out: %s \n", argv[2]);
    printf("        \n");
    printf("done…   \n");
}
