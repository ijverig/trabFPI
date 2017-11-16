#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../lib/stb_image_write.h"

#define R 0
#define G 1
#define B 2

typedef unsigned char byte;

int main(int argc, char const *argv[]) {
    int image_width, image_height;
    int pixels_in_image, channels_per_pixel = 3;

    printf("in: %s \n", argv[1]);
    byte *image_data = stbi_load(argv[1], &image_width, &image_height, NULL, STBI_rgb);
    pixels_in_image = image_width * image_height;

    byte *image_data_copy = malloc(image_height * image_width * channels_per_pixel);

    // alias to list of [image_width][channel] arrays (scanlines)
    byte (*image)[image_width][channels_per_pixel] = (byte (*)[image_width][channels_per_pixel]) image_data;
    byte (*image_copy)[image_width][channels_per_pixel] = (byte (*)[image_width][channels_per_pixel]) image_data_copy;

    for (int row = 0, last_pixel = image_width - 1; row < image_height; row++) {
        for (int col = 0; col < image_width; col++) {
            image_copy[row][col][R] = image[row][last_pixel - col][R];
            image_copy[row][col][G] = image[row][last_pixel - col][G];
            image_copy[row][col][B] = image[row][last_pixel - col][B];
        }
    }

    printf("out: %s \n", argv[2]);
    stbi_write_jpg(argv[2], image_width, image_height, STBI_rgb, image_data_copy, 90);

    printf("      \n");
    printf("done… \n");
    stbi_image_free(image_data);
    free(image_data_copy);
}
