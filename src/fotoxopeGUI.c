#if defined(__APPLE__)
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif

#include "GUI/session.h"
#include "GUI/interface.h"

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    session_init(argv[1]);
    interface_init();

    glutMainLoop();
}
