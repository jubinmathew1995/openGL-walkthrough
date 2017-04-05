/*

      CPP Program to make a graphic window
      using openGL graphics library.

      Program to just create a window using openGL library.

*/

#include <GL/glut.h>

void displayFunc()
{
  // Empty function

}

int main(int argc,char **argv)
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutInitWindowSize(400,500);
  glutInitWindowPosition(200,200);
  glutCreateWindow("My first window");
  //glutDisplayFunc(displayFunc);  // COMMENT this function and see what happens.
  glutMainLoop();
}
