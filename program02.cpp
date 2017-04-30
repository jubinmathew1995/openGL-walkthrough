/*

      CPP Program to make a graphic window
      using openGL graphics library.

      Program to show the use of openGL primitives.

*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glut.h>

// window TITLE, WIDTH and HEIGHT
#define WINDOW_TITLE_PREFIX "OpenGL-primitives"
int CurrentWidth = 800,
  CurrentHeight = 600;

void Initialize(int, char*[]);
void InitWindow(int, char*[]);
void ResizeFunction(int, int);	// maintains and resize the object in case of window resize.
void RenderFunction(void);	// responsible for window displaying object
void drawPoints (float,float,float);	// Draws points using points primitive
void drawAxes (void);	// draw lines using line primitive
void drawTriangle(void);	// draws triangle using triangle primitive.
void drawQuads(void);	// draws quad using quads primitive.
void drawLineLoop(void); 	// draws loop of lines

int main(int argc, char* argv[])
{
  Initialize(argc, argv);
  glutMainLoop();
}

void Initialize(int argc, char* argv[])
{
  InitWindow(argc, argv);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void InitWindow(int argc, char* argv[])
{
  glutInit(&argc, argv);
  glutInitWindowSize(CurrentWidth, CurrentHeight);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutCreateWindow(WINDOW_TITLE_PREFIX);
  glutReshapeFunc(ResizeFunction);
  glutDisplayFunc(RenderFunction);
}

void ResizeFunction(int Width, int Height)
{
  CurrentWidth = Width;
  CurrentHeight = Height;
  glViewport(0, 0, CurrentWidth, CurrentHeight);
}

void RenderFunction(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
    drawPoints(100,200,10);
    drawPoints(-300,-300,5);
    drawTriangle();
    drawQuads();
    drawLineLoop();
  glutSwapBuffers();
  glutPostRedisplay();
}

void drawPoints (float x,float y,float size=5.0)
{
    glPointSize(size);	// sers the width of the point
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_POINTS);
	    glVertex3f((2*x/CurrentWidth), (2*y/CurrentHeight), 0.0);
    glEnd();
}

void drawAxes (void)
{
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_LINES);
	    glVertex3f(-1.0f, 0.0f, 0.0f);
	    glVertex3f(1.0f, 0.0f, 0.0f);
	    glVertex3f(0.0f,-1.0f, 0.0f);
	    glVertex3f(0.0f,1.0f,0.0f);
    glEnd();
}

void drawTriangle(void)
{
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_TRIANGLES);
	    glVertex3f(-0.3f, 0.0f, 0.0f);
	    glVertex3f(0.1f, 0.3f, 0.0f);
	    glVertex3f(0.2f,-0.3f, 0.0f);
    glEnd();
}

void drawQuads(void)
{
	glColor3f(0.0,0.0,1.0);
    glBegin(GL_QUADS);
	    glVertex3f(0.3f,-0.1f, 0.0f);
	    glVertex3f(0.6f,-0.1f, 0.0f);
	    glVertex3f(0.6f,-0.3f, 0.0f);
	    glVertex3f(0.3f,-0.3f, 0.0f);
    glEnd();
}

void drawLineLoop(void)
{
	glLineWidth(3.0);	// sets the width fo the line which it is going to make
    glColor3f(1.0,1.0,0.0);
    glBegin(GL_LINE_LOOP);
	    glVertex3f(0.0f,1.0f , 0.0);
    	glVertex3f(1.0f,0.0f , 0.0);
    	glVertex3f(0.0f,-1.0f , 0.0);
    	glVertex3f(-1.0f,0.0f , 0.0);
    glEnd();
}
