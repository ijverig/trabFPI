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

void handle_selection(int option)
{
    switch (option) {
        case OPTION_NOTHING:
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
    glutAddSubMenu("Flip", flip_menu);
    glutAddMenuEntry(SEPARATOR, OPTION_NOTHING);
    glutAddMenuEntry("Grayscale (g)", OPTION_GRAYSCALE);
    glutAddMenuEntry(SEPARATOR, OPTION_NOTHING);
    glutAddMenuEntry("Exit (e)", OPTION_EXIT);

    glutSetMenu(main_menu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void handle_key_press(unsigned char key, int _, int __)
{
    switch (key) {
        case 'h':
            handle_selection(OPTION_FLIP_H);
            break;
        case 'v':
            handle_selection(OPTION_FLIP_V);
            break;
        case 'g':
            handle_selection(OPTION_GRAYSCALE);
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
