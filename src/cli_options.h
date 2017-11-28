#include <unistd.h>

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
                   command_t *command, int *parameter,
                   char **in, char **out);
