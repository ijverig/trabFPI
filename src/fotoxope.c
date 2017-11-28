#include <stdio.h>
#include <stdlib.h>

#include "cli_options.h"
#include "image.h"

int main(int argc, char *const argv[])
{
    command_t command;
    int parameter;
    char *in, *out;

    parse_options(argc, argv, &command, &parameter, &in, &out);

    image_t image = image_create_from_file(in);
    image_t image_buffer = image_create_from_image(image);

    switch (command) {
        case NOTHING:
            exit(EXIT_SUCCESS);
            break;
        case FLIP_H:
            transform_flip_h(&image_buffer);
            break;
        case FLIP_V:
            transform_flip_v(&image_buffer);
            break;
        case GRAY:
            filter_grayscale(&image_buffer);
            break;
        case QUANTIZE:
            filter_quantize(&image_buffer, parameter);
            break;
    }

    image_save(image_buffer, out);

    image_destroy(image);
    image_destroy(image_buffer);

    exit(EXIT_SUCCESS);
}
