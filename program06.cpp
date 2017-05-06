/*

CPP Program to make a graphic window
using openGL graphics library.

Program to detect objects clicked in the screen using the mouse clicks.

*/
#include <stdio.h>
#include <GL/glut.h>
#define SIZE 512

// window TITLE, WIDTH and HEIGHT
#define WINDOW_TITLE_PREFIX "picking objects"
int windowWidth=800,windowHeight=600;

// function prototype
static void displayFunction(void);
static void ResizeFunction(int, int);
static void mouseButton(int, int, int, int);

// this mode must be set to default argument GL_RENDER 
// used to set the mode to GL_RENDER if it is not triggered with
// mouseFunc otherwise it is GL_SELECT when triggered with a 
// mouse event.
void draw(GLenum mode=GL_RENDER)
{
    // just write a new load name before each object
    // you render, THIS LOAD NAME MUST BE UNIQUE for 
    // each object you make, if you want to identify
    // that object uniquely.
    glLoadName(1);
    glColor3f(1.0,0.0,0.0);
    glRectf(100, 200, 300, 400);

    glLoadName(2);
    glColor3f(0.0,1.0,0.0);
    glRectf(200, 300, 400, 500);

    glLoadName(3);
    glColor3f(0.0,0.0,1.0);
    glRectf(600, 500, 650, 550);

    glLoadName(4);
    glColor3f(1.0,1.0,1.0);
    glRectf(500, 400, 600, 200);

    glLoadName(5);
    glColor3f(0.5,0.5,0.5);
    glBegin(GL_TRIANGLES);
        glVertex2f(400,300);
        glVertex2f(450,350);
        glVertex2f(350,350);
    glEnd();

}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutInitWindowSize(windowWidth,windowHeight);
    glutInitWindowPosition(0,0);
    glutCreateWindow(WINDOW_TITLE_PREFIX);
    glutReshapeFunc(ResizeFunction);
    glutMouseFunc(mouseButton);
    glutDisplayFunc(displayFunction);
    glClearColor((23.0/255),(32.0/255),(42.0/255),0);
    gluOrtho2D(0,windowWidth,0,windowHeight);
    glutMainLoop();

    return 0;
}

static void displayFunction()
{
    glClear(GL_COLOR_BUFFER_BIT);
    draw();
    glutSwapBuffers();
}

static void ResizeFunction(int width, int height)
{
    //////////////////////////////////////////////////////
    ////// NEVER DELETE THIS SECTION - SINCE OBJECT //////
    ////// SELECTION DOESN'T WORK !!!!!!!!!!!!!!!!! //////
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D (0, windowWidth, 0, windowHeight);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    /////////////////////////////////////////////////////
}

// this function is used to detect which object is hit,
void processHits (GLint hits, GLuint buffer[])
{
   unsigned int i, j;
   GLuint names, *ptr;
   if(hits == 0)
        printf("No square is hit & ");
   ptr = (GLuint *) buffer;
   for (i = 0; i < hits; i++)
   { /*  for each hit  */
      names = *ptr;
      ptr+=3;
      for (j = 0; j < names; j++)
      { /*  for each name */
        // printf ("%d\n",*ptr);
        if(*ptr == 1)
            printf("Red square is hit & ");
        else if(*ptr == 2)
            printf("Green square is hit & ");
        else if(*ptr == 3)
            printf("Blue square is hit & ");
        else if(*ptr == 4)
            printf("White square is hit & ");
        else if(*ptr == 5)
            printf("Triangle is hit & ");
        ptr++;
      }
   }
   printf("\n");
}

static void mouseButton(int button, int state, int x, int y)
{
    GLuint selectBuf[SIZE];
    GLint hits;
    GLint viewport[4];

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        glGetIntegerv (GL_VIEWPORT, viewport);

        glSelectBuffer (SIZE, selectBuf);
        glRenderMode(GL_SELECT);

        glInitNames();
        glPushName(0);

        glMatrixMode (GL_PROJECTION);
        glPushMatrix ();
        glLoadIdentity ();
        /* create 5x5 pixel picking region near cursor location */
        gluPickMatrix ((GLdouble) x, (GLdouble) (viewport[3] - y),
                      5.0, 5.0, viewport);
        gluOrtho2D (0, windowWidth, 0, windowHeight);
        draw(GL_SELECT);


        glMatrixMode (GL_PROJECTION);
        glPopMatrix ();
        glFlush ();

        hits = glRenderMode (GL_RENDER);
        processHits (hits, selectBuf);

        glutPostRedisplay();
        glutSwapBuffers();
    }
}
