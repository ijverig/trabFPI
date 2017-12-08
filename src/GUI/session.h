#ifndef SESSION_HEADER
#define SESSION_HEADER

#include "../core/image.h"

typedef struct session session_t;
typedef struct image_session image_session_t;

struct image_positions
{
    int center_x, center_y;
};

struct image_session
{
    image_t image;
    struct image_positions positions;
};

struct session_window
{
    int width, height;
};

struct session
{
    char *input_filename;
    struct image_session source, buffer;
    struct session_window window;
};

void session_init(char *input_filename);

session_t session;

#endif
