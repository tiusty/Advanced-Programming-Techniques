/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 11/22/2019
Description:
 Main function that executes the program
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "iomanip"
#include <cmath>
#include <math.h>
#include <cstdlib>
#include <GL/glut.h>
#include <chrono>
#include <thread>

#include "footballField.h"

#include "uav.h"
#include "ECE_Bitmap.h"

typedef struct Image Image;
GLuint texture[1];
BMP inBitmap;

// Define an instance of a football field
FootballField field;
unsigned int colorOscillations{0};
bool decrease{false};

// Camera Parameters
float eye_x = 0, eye_y = 50, eye_z = 50;
float center_x = field.widthFootballField/2, center_y = field.lenFootballField/2, center_z = 25;


//----------------------------------------------------------------------
// Reshape callback
//
// Window size has been set/changed to w by h pixels. Set the camera
// perspective to 45 degree vertical field of view, a window aspect
// ratio of w/h, a near clipping plane at depth 1, and a far clipping
// plane at depth 100. The viewport is the entire window.
//
//----------------------------------------------------------------------
void changeSize(int w, int h)
{
    float ratio = ((float)w) / ((float)h); // window aspect ratio
    glMatrixMode(GL_PROJECTION); // projection matrix is active
    glLoadIdentity(); // reset the projection
    gluPerspective(120.0, ratio, 0.1, 1000.0); // perspective transformation
    glMatrixMode(GL_MODELVIEW); // return to modelview mode
    glViewport(0, 0, w, h); // set viewport (drawing area) to entire window
}

/**
 * Processes changes made by normal keys from the keyboard
 */
void processNormalKeys(unsigned char key, int xx, int yy)
{
    if (key == 'r' || key == 'R')
    {
        // We want it to circle around the point (4,4) which is the center of the chess board
        double theta = atan2((eye_z-center_z),(eye_x-center_x));
        // Add 10 degree to the angle
        theta = theta - (10.0/180)*3.14;
        // Find the distance from the center
        double r = sqrt((eye_x-center_x)*(eye_x-center_x) + (eye_y-center_y)*(eye_y-center_y));
        // Calculate the new position of the camera
        eye_x = r*cos(theta) + center_x;
        eye_y = r*sin(theta) + center_y;
    }
}

//----------------------------------------------------------------------
// Draw the entire scene
//
// We first update the camera location based on its distance from the
// origin and its direction.
//----------------------------------------------------------------------
void renderScene()
{

    // Clear color and depth buffers
    glClearColor(0.0, 0.0, 1.0, 1.0); // background color to blue??
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();


    if(field.checkAllUavsAtSphere())
    {
        gluLookAt(eye_x, eye_y, eye_z+10,
                  field.sphereLocation().x, field.sphereLocation().y, field.sphereLocation().z,
                  0.0, 0.0, 1.0);
    }
    else
    {
        gluLookAt(eye_x, eye_y, eye_z,
                  center_x, center_y, center_z,
                  0.0, 0.0, 1.0);
    }

    glMatrixMode(GL_MODELVIEW);

    field.drawField(texture);
    field.drawSphere();

    for(auto &uav : field.uavs)
    {
            uav.evolveSystem();
    }
    field.checkCollisions();
    field.drawUAVS(colorOscillations);

    if(colorOscillations == 128)
    {
        decrease = true;
    }
    else if (colorOscillations == 0)
    {
        decrease = false;
    }

    if(decrease)
    {
        colorOscillations--;
    }
    else
    {
        colorOscillations++;
    }

    glutSwapBuffers(); // Make it all visible
}
//----------------------------------------------------------------------
// timerFunction  - called whenever the timer fires
//----------------------------------------------------------------------
void timerFunction(int id)
{
    glutPostRedisplay();
    glutTimerFunc(100, timerFunction, 0);
}

void initTexture()
{
    glClearColor(0.5, 0.5, 0.5, 0.0);

    glEnable(GL_DEPTH_TEST);

    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    inBitmap.read("AmFBfield.bmp");


    // Create Textures
    glGenTextures(1, texture);

    // Setup first texture
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, inBitmap.bmp_info_header.width, inBitmap.bmp_info_header.height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, &inBitmap.data[0]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //scale linearly when image smalled than texture

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glEnable(GL_TEXTURE_2D);

}
//----------------------------------------------------------------------
// mainOpenGL  - standard GLUT initializations and callbacks
//----------------------------------------------------------------------
void mainOpenGL(int argc, char**argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);

    glutCreateWindow(argv[0]);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    initTexture();

    // Setup lights as needed
    // ...

    glutReshapeFunc(changeSize);
    glutDisplayFunc(renderScene);
    glutTimerFunc(100, timerFunction, 0);
    glutKeyboardFunc(processNormalKeys);
    glutMainLoop();
}
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// Main entry point determines rank of the process and follows the
// correct program path
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
int main(int argc, char**argv)

{
    mainOpenGL(argc, argv);
    return 0;
}
