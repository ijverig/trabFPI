#include <stdio.h>
#include <stdlib.h>

#include "CLI/cli_options.h"
#include "core/image.h"

int main(int argc, char *const argv[])
{
    command_t command_queue[COMMAND_QUEUE_SIZE + 1] = { NOTHING };
    int parameter_queue[COMMAND_QUEUE_SIZE + 1] = { 0 };
    char *in, *out;

    parse_options(argc, argv, command_queue, parameter_queue, &in, &out);

    image_t image = image_create_from_file(in);
    image_t image_buffer = image_create_from_image(image);

    int i = -1;
    while (command_queue[++i]) {
        switch (command_queue[i]) {
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
                filter_quantize(&image_buffer, (byte)parameter_queue[i]);
                break;
            case NOTHING:
            default:
                fprintf(stderr, "Error: something bad happened. \n");
                exit(EXIT_FAILURE);
        }
    }

    image_save(image_buffer, out);

    image_destroy(image);
    image_destroy(image_buffer);

    exit(EXIT_SUCCESS);
}
