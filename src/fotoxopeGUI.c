#if defined(__APPLE__)
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif

#include "core/image.h"

image_t image;
int window_width, window_height;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glRasterPos2i(window_width/2 - image.width/2, window_height/2 - image.height/2);
    glDrawPixels(image.width, image.height, GL_RGB, GL_UNSIGNED_BYTE, image.data);

    glutSwapBuffers();
}

void reshape(int width, int height)
{
    window_width = width;
    window_height = height;

    glViewport(0, 0, window_width, window_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, window_width, 0.0, window_height);
    glMatrixMode(GL_MODELVIEW);
}

void createWindow()
{
    int margin = 60, titlebar = 20;

    window_width = glutGet(GLUT_SCREEN_WIDTH) - 2*margin;
    window_height = glutGet(GLUT_SCREEN_HEIGHT) - 2*margin - titlebar;

    glutInitWindowPosition(margin, margin + titlebar);
    glutInitWindowSize(window_width, window_height);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutCreateWindow("Fotoxope");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glClearColor(33/255.0, 48/255.0, 47/255.0, 1.0);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    image_flip_vertically_on_load();
    image = image_create_from_file(argv[1]);

    createWindow();

    glutMainLoop();
}
