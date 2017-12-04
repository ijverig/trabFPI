#define COMMAND_QUEUE_SIZE 16

typedef enum command command_t;

enum command
{
    NOTHING,
    FLIP_H,
    FLIP_V,
    GRAY,
    QUANTIZE,
};

void parse_options(int argc, char *const argv[],
                   command_t command_queue[], int parameter_queue[],
                   char **in, char **out);
