#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../lib/stb_image_write.h"

int main(int argc, char const *argv[]) {
    int width, height, n_components;

    unsigned char *data = stbi_load(argv[1], &width, &height, &n_components, STBI_rgb);

    stbi_write_jpg(argv[2], width, height, STBI_rgb, data, 100);
    stbi_image_free(data);

    printf("in: %s  \n", argv[1]);
    printf("out: %s \n", argv[2]);
    printf("        \n");
    printf("done…   \n");
}
