#include "interaction.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__APPLE__)
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif

extern session_t session;

void file_dialog(char *dialog, char **io_filename)
{
    char filename[500];
    printf("%s", dialog);
    fgets(filename, 500, stdin);
    filename[strcspn(filename, "\n")] = '\0';
    *io_filename = strdup(filename);
}

void open_dialog()
{
    file_dialog("Image file to open: ", &session.input_filename);
}

void save_dialog()
{
    file_dialog("Image file to save: ", &session.output_filename);
}

void value_dialog(char *dialog, float *value)
{
    printf("%s", dialog);
    scanf("%f", value);
    getc(stdin); // eats \n
}

void handle_selection(int option)
{
    switch (option) {
        case OPTION_NOTHING:
            break;

        case OPTION_OPEN:
            open_dialog();
            image_destroy(session.source.image);
            image_destroy(session.buffer.image);
            session_reload();
            break;
        case OPTION_SAVE:
            save_dialog();
            transform_flip_v(&session.buffer.image);
            image_save(session.buffer.image, session.output_filename);
            transform_flip_v(&session.buffer.image);
            break;

        case OPTION_HISTOGRAM:
            session.histogram.width = session.histogram.height = session.histogram.is_visible ? 0 : 256;
            session.histogram.is_visible = !session.histogram.is_visible;
            break;

        case OPTION_FLIP_H:
            transform_flip_h(&session.buffer.image);
            break;
        case OPTION_FLIP_V:
            transform_flip_v(&session.buffer.image);
            break;

        case OPTION_GRAYSCALE:
            filter_grayscale(&session.buffer.image);
            break;
        case OPTION_QUANTIZE:
            {
                float levels;
                value_dialog("Number of levels: ", &levels);
                filter_quantize(&session.buffer.image, levels);
            }
            break;
        case OPTION_BRIGHTNESS:
            {
                float bias;
                value_dialog("Bias: ", &bias);
                filter_brightness(&session.buffer.image, bias);
            }
            break;
        case OPTION_CONTRAST:
            {
                float gain;
                value_dialog("Gain: ", &gain);
                filter_contrast(&session.buffer.image, gain);
            }
            break;
        case OPTION_NEGATIVE:
            filter_negative(&session.buffer.image);
            break;

        case OPTION_EXIT:
            exit(EXIT_SUCCESS);
            break;

        default:
            fprintf(stderr, "Error: something bad happened. \n");
            exit(EXIT_FAILURE);
    }

    glutPostRedisplay();
}

void create_menu()
{
    char *const SEPARATOR = "————————";

    int flip_menu = glutCreateMenu(handle_selection);
    glutAddMenuEntry("Horizontally (h)", OPTION_FLIP_H);
    glutAddMenuEntry("Vertically (v)", OPTION_FLIP_V);

    int main_menu = glutCreateMenu(handle_selection);
    glutAddMenuEntry("Open (o)", OPTION_OPEN);
    glutAddMenuEntry("Save (s)", OPTION_SAVE);
    glutAddMenuEntry(SEPARATOR, OPTION_NOTHING);
    glutAddMenuEntry("Histogram (H)", OPTION_HISTOGRAM);
    glutAddMenuEntry(SEPARATOR, OPTION_NOTHING);
    glutAddSubMenu("Flip", flip_menu);
    glutAddMenuEntry(SEPARATOR, OPTION_NOTHING);
    glutAddMenuEntry("Grayscale (g)", OPTION_GRAYSCALE);
    glutAddMenuEntry("Quantize (q)", OPTION_QUANTIZE);
    glutAddMenuEntry("Brightness (b)", OPTION_BRIGHTNESS);
    glutAddMenuEntry("Contrast (c)", OPTION_CONTRAST);
    glutAddMenuEntry("Negative (n)", OPTION_NEGATIVE);
    glutAddMenuEntry(SEPARATOR, OPTION_NOTHING);
    glutAddMenuEntry("Exit (e)", OPTION_EXIT);

    glutSetMenu(main_menu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void handle_key_press(unsigned char key, int _, int __)
{
    switch (key) {
        case 'o':
            handle_selection(OPTION_OPEN);
            break;
        case 's':
            handle_selection(OPTION_SAVE);
            break;

        case 'H':
            handle_selection(OPTION_HISTOGRAM);
            break;

        case 'h':
            handle_selection(OPTION_FLIP_H);
            break;
        case 'v':
            handle_selection(OPTION_FLIP_V);
            break;

        case 'g':
            handle_selection(OPTION_GRAYSCALE);
            break;
        case 'q':
            handle_selection(OPTION_QUANTIZE);
            break;
        case 'b':
            handle_selection(OPTION_BRIGHTNESS);
            break;
        case 'c':
            handle_selection(OPTION_CONTRAST);
            break;
        case 'n':
            handle_selection(OPTION_NEGATIVE);
            break;

        case 'e':
            handle_selection(OPTION_EXIT);
            break;

        default:
            ;
    }
}

void interaction_init()
{
    create_menu();

    glutKeyboardFunc(handle_key_press);
}
