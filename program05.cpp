#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include <iostream>
#include "program05-lodepng.h"
#include "program05-lodepng.cpp"

// window TITLE, WIDTH and HEIGHT
#define WINDOW_TITLE_PREFIX "load png images."
int windowWidth=800,windowHeight=600;

// function prototype
static void displayFunction(void);
static void idleFunction(void);
static void keyFunction(unsigned char, int, int);
static void processSpecialKeys(int, int, int);

std::vector <unsigned char> img;
unsigned logoWidth=542;
unsigned logoHeight=550;
void load_images()
{
    const char* logoName="abcd.png";
    int error;
    if((error=lodepng::decode(img,logoWidth,logoHeight,logoName)))
    {
        printf("%s %s %s",logoName,":",lodepng_error_text(error));
        exit(1);
    }
}
int main(int argc, char *argv[])
{
    // init GLUT and create Window
    load_images();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    windowWidth = glutGet(GLUT_SCREEN_WIDTH);
    windowHeight = glutGet(GLUT_SCREEN_HEIGHT);

    glutInitWindowSize(windowWidth,windowHeight);
    glutInitWindowPosition(0,0);
    glutCreateWindow(WINDOW_TITLE_PREFIX);

    // register callbacks
    glutDisplayFunc(displayFunction);

    // keyFunction is called whenever an keyboard event is encountered.
    glutKeyboardFunc(keyFunction);

    // added special keyboard keys like up,down,left and right arroe keys.
    glutSpecialFunc(processSpecialKeys);

    // this IDLE tells the glut to keep calling render function
    // to allow animations.
    glutIdleFunc(idleFunction);

    // sets the background color RED:GREEN:BLUE:ALPHA
    glClearColor((23.0/255),(32.0/255),(42.0/255),0);

    gluOrtho2D(0,windowWidth,0,windowHeight);

    // Enabling transparency for the color buffer.
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // enter GLUT event processing cycle/
    glutMainLoop();

    return 1;
}

static void displayFunction(void)
{
    // clear previous colors.
    glClear(GL_COLOR_BUFFER_BIT);
    glRasterPos2i(windowWidth/2-(logoWidth/2),windowHeight/2-(logoHeight/2));
    glDrawPixels(logoWidth,logoHeight, GL_RGBA, GL_UNSIGNED_BYTE, &img[0]);
    glColor3ub(255,255,255);
    // swaps the front and back buffers.
    glutSwapBuffers();
}

static void idleFunction(void)
{
    // tells GULT to continously redisplay/call the
    // display function continously, so that animations
    // can be possible.
    glutPostRedisplay();
}

static void keyFunction(unsigned char key, int x, int y)
{
    glutPostRedisplay();
}

static void processSpecialKeys(int key, int x, int y)
{
    glutPostRedisplay();
}
