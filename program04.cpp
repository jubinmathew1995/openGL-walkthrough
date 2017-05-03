/*

CPP Program to make a graphic window
using openGL graphics library.

Program to show the use of rotate function of openGL.

*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glut.h>

// window TITLE, WIDTH and HEIGHT
#define WINDOW_TITLE_PREFIX "Rotate"
int windowWidth = 800,
    windowHeight = 600;

int angle = 45;
int totalAngle = 0;
int rotateFlag=0;

// function prototype
static void ResizeFunction(int, int);
static void displayFunction(void);
static void idleFunction(void);
static void keyFunction(unsigned char, int, int);
static void mouseMove(int, int);
static void mouseButton(int, int, int, int);

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(windowWidth,windowHeight);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow(WINDOW_TITLE_PREFIX);
    glutReshapeFunc(ResizeFunction);
    glutDisplayFunc(displayFunction);
    glutKeyboardFunc(keyFunction);
    glutIdleFunc(idleFunction);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);
    glClearColor(0,0,0,0);
    glutMainLoop();

    return 1;
}

static void ResizeFunction(int width, int height)
{
    windowHeight=height;
    windowWidth=width;
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

static void displayFunction(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(rotateFlag==1)
    {
        glRotatef(angle,0.0f,0.0f,1.0f);
        rotateFlag=0;
    }
    glBegin(GL_TRIANGLES);
        glVertex3f(-0.5,-0.5,0.0);
        glVertex3f(0.5,0.0,0.0);
        glVertex3f(0.0,0.5,0.0);
    glEnd();
    glutSwapBuffers();
}


static void idleFunction(void)
{
    glutPostRedisplay();
}

static void keyFunction(unsigned char key, int x, int y)
{
    printf("keyboard--%d->%c\n",key,char(key));
    switch (key)
    {
        case 27 :
        case 'q':
            printf("quit\n");
            exit(0);
            break;
        case '+':
            totalAngle+=angle;
            totalAngle%=360;
            rotateFlag=1;
            printf("anle ++ = %d\n",totalAngle);
            break;
        case '-':
            totalAngle-=angle;
            totalAngle%=360;
            rotateFlag=1;
            printf("angle-- = %d\n",totalAngle );
            break;
    }
    glutPostRedisplay();
}

static void mouseMove(int x, int y) {
    printf("Mouse-Coodinates:(%d,%d)\n",x,y );
}

static void mouseButton(int button, int state, int x, int y) {

	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {

		// when the button is released
		if (state == GLUT_UP) {
			printf("Mouse--LEFT--onKeyUp--(%d,%d)\n",x,y );
		}
		else  {// state = GLUT_DOWN
            printf("Mouse--LEFT--onKeyDown--(%d,%d)\n",x,y );
		}
	}
    else if (button == GLUT_RIGHT_BUTTON) {

        // when the button is released
        if (state == GLUT_UP) {
            printf("Mouse--RIGHT--onKeyUp--(%d,%d)\n",x,y );
        }
        else  {// state = GLUT_DOWN
            printf("Mouse--RIGHT--onKeyDown--(%d,%d)\n",x,y );
        }
    }
    else {

        // when the button is released
        if (state == GLUT_UP) {
            printf("Mouse--MIDDLE--onKeyUp--(%d,%d)\n",x,y );
        }
        else  {// state = GLUT_DOWN
            printf("Mouse--MIDDLE--onKeyDown--(%d,%d)\n",x,y );
        }
    }
}
