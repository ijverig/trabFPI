#include "image.h"

#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../lib/stb_image_write.h"

void image_save(image_t image, const char *filename) {
    stbi_write_jpg(filename, image.width, image.height, STBI_rgb, image.data, 90);
}

image_t image_create_from_file(const char *filename) {
    image_t image;

    image.data = stbi_load(filename, &image.width, &image.height, NULL, STBI_rgb);
    image.depth = 3;
    image.size = image.width * image.height * image.depth;

    return image;
}

image_t image_create_from_image(image_t image) {
    image_t copy = image;

    copy.data = malloc(image.size);
    memcpy(copy.data, image.data, image.size);

    return copy;
}

void image_destroy(image_t image) {
    free(image.data);
}
