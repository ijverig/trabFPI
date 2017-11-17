#include <stdio.h>

#include "image.h"

int main(int argc, char const *argv[]) {
    image_t image = image_create_from_file(argv[1]);
    image_t image_buffer = image_create_from_image(image);

    // alias to list of [width][channel] arrays (scanlines)
    byte (*img)[image.width][image.depth] = (byte (*)[image.width][image.depth]) image.data;
    byte (*img_buffer)[image.width][image.depth] = (byte (*)[image.width][image.depth]) image_buffer.data;

    for (int row = 0, last_pixel = image.width - 1; row < image.height; row++) {
        for (int col = 0; col < image.width; col++) {
            img_buffer[row][col][R] = img[row][last_pixel - col][R];
            img_buffer[row][col][G] = img[row][last_pixel - col][G];
            img_buffer[row][col][B] = img[row][last_pixel - col][B];
        }
    }

    image_save(image_buffer, "build/output_vflipped.jpg");

    image_destroy(image);
    image_destroy(image_buffer);

    printf("in: %s  \n", argv[1]);
    printf("out: %s \n", argv[2]);
    printf("        \n");
    printf("done…   \n");
}
