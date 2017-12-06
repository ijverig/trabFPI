#include "session.h"

void session_init(session_t *session, char *input_filename)
{
    session->input_filename = input_filename;

    image_flip_vertically_on_load();
    session->source.image = image_create_from_file(input_filename);

    session->buffer.image = image_create_from_image(session->source.image);
}

void session_compute_image_positions(session_t *session)
{
    session->source.positions.center_x = session->window.width/4;
    session->source.positions.center_y = session->window.height/2;
    session->buffer.positions.center_x = 3*session->window.width/4;
    session->buffer.positions.center_y = session->window.height/2;
}
