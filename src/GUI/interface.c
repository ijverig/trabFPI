#include "interface.h"

#if defined(__APPLE__)
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif

extern session_t session;

void draw_images(image_session_t *image_session)
{
    glRasterPos2i(image_session->positions.center_x - image_session->image.width/2,
                  image_session->positions.center_y - image_session->image.height/2);
    glDrawPixels(image_session->image.width, image_session->image.height,
                 GL_RGB, GL_UNSIGNED_BYTE, image_session->image.data);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    draw_images(&session.source);
    draw_images(&session.buffer);

    glutSwapBuffers();
}

void compute_frame_positions()
{
    session.source.positions.center_x = session.window.width/4;
    session.source.positions.center_y = session.window.height/2;
    session.buffer.positions.center_x = 3*session.window.width/4;
    session.buffer.positions.center_y = session.window.height/2;
}

void reshape(int width, int height)
{
    session.window.width  = width;
    session.window.height = height;

    compute_frame_positions();

    glViewport(0, 0, session.window.width, session.window.height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, session.window.width, 0.0, session.window.height);
    glMatrixMode(GL_MODELVIEW);
}

void create_window()
{
    int margin = 60, titlebar = 20;

    session.window.width = glutGet(GLUT_SCREEN_WIDTH) - 2*margin;
    session.window.height = glutGet(GLUT_SCREEN_HEIGHT) - 2*margin - titlebar;

    glutInitWindowPosition(margin, margin + titlebar);
    glutInitWindowSize(session.window.width, session.window.height);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutCreateWindow("Fotoxope");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glClearColor(42/255.0, 41/255.0, 43/255.0, 1.0);
}

void interface_init()
{
    create_window();
}
