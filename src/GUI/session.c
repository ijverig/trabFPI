#include "session.h"

extern session_t session;

void session_init(char *input_filename)
{
    session.input_filename = input_filename;

    image_flip_vertically_on_load();
    session.source.image = image_create_from_file(input_filename);

    session.buffer.image = image_create_from_image(session.source.image);
}
