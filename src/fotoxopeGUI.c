#if defined(__APPLE__)
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif

#include "GUI/session.h"

session_t session;

void draw_image_session(image_session_t *image_session)
{
    glRasterPos2i(image_session->positions.center_x - image_session->image.width/2,
                  image_session->positions.center_y - image_session->image.height/2);
    glDrawPixels(image_session->image.width, image_session->image.height,
                 GL_RGB, GL_UNSIGNED_BYTE, image_session->image.data);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    draw_image_session(&session.source);
    draw_image_session(&session.buffer);

    glutSwapBuffers();
}

void reshape(int width, int height)
{
    session.window.width  = width;
    session.window.height = height;

    session_compute_image_positions(&session);

    glViewport(0, 0, session.window.width, session.window.height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, session.window.width, 0.0, session.window.height);
    glMatrixMode(GL_MODELVIEW);
}

void createWindow()
{
    int margin = 60, titlebar = 20;

    session.window.width = glutGet(GLUT_SCREEN_WIDTH) - 2*margin;
    session.window.height = glutGet(GLUT_SCREEN_HEIGHT) - 2*margin - titlebar;

    session_compute_image_positions(&session);

    glutInitWindowPosition(margin, margin + titlebar);
    glutInitWindowSize(session.window.width, session.window.height);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutCreateWindow("Fotoxope");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glClearColor(42/255.0, 41/255.0, 43/255.0, 1.0);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    session_init(&session, argv[1]);

    createWindow();

    glutMainLoop();
}
