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
    int main_menu = glutCreateMenu(handle_selection);
    glutAddMenuEntry("Exit (e)", OPTION_EXIT);

    glutSetMenu(main_menu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void handle_key_press(unsigned char key, int _, int __)
{
    switch (key) {
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
