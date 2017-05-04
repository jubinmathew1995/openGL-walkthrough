/*

CPP Program to make a graphic window
using openGL graphics library.

Program to load a png images in the glut window.

*/
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

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
// vector in which the image is loaded.
std::vector <unsigned char> img;
// set the png image resolution.
unsigned logoWidth=542;
unsigned logoHeight=550;

void load_images()
{
    // use the name of the image in this logoname
    const char* logoName="abcd.png";
    int error;
    if((error=lodepng::decode(img,logoWidth,logoHeight,logoName)))
    {
        printf("%s %s %s",logoName,":",lodepng_error_text(error));
        exit(1);
    }
}
// NOTE: always the resolution of the image must be less than the
//       resolution of the glut window which you created.
//
// NOTE: image must be in the same directory as that of the source
//       file or MUST be relative to that of the location of the
//       source program file.
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

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
    glutDisplayFunc(displayFunction);
    glClearColor((23.0/255),(32.0/255),(42.0/255),0);
    gluOrtho2D(0,windowWidth,0,windowHeight);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glutMainLoop();

    return 1;
}

static void displayFunction(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    /////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////
    // setting the **LOWER LEFT BOTTON coodinate where the image must be loaded.
    // image will be loaded from the lower left bottom coodinate.
    glRasterPos2i(windowWidth/2-(logoWidth/2),windowHeight/2-(logoHeight/2));
    // this function draw the image, must pass pointer to the image vector which
    // it created.
    glDrawPixels(logoWidth,logoHeight, GL_RGBA, GL_UNSIGNED_BYTE, &img[0]);
    /////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////

    glColor3ub(255,255,255);
    glutSwapBuffers();
}

static void idleFunction(void)
{
    glutPostRedisplay();
}
