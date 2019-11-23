/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 11/22/2019
Description:
 Main function that executes the program
*/

//#define MPI

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

#include <footballField.h>
#include "uav.h"

// Send location and velocity vector in each direction
const int numElements = 6; // x, y, z, vx, vy, vz

const int rcvSize = 16 * 6; // (Main task + 15 UAVs) * numElements

double* rcvbuffer = new double[rcvSize];

double sendBuffer[numElements];

// Define an instance of a football field
FootballField field;

// Camera Parameters
float eye_x = 0, eye_y = 50, eye_z = 40;
float center_x = field.widthFootballField/2, center_y = field.lenFootballField/2, center_z = 0;


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


    gluLookAt(eye_x, eye_y, eye_z,
              center_x, center_y, center_z,
              0.0, 0.0, 1.0);

    glMatrixMode(GL_MODELVIEW);

    field.drawField();

    field.drawUAVS();

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
//----------------------------------------------------------------------
// mainOpenGL  - standard GLUT initializations and callbacks
//----------------------------------------------------------------------
void mainOpenGL(int argc, char**argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
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
    std::thread t1(mainOpenGL, argc, argv);

    printf("hiii\n");
    // Sleep for 5 seconds
    std::this_thread::sleep_for(std::chrono::seconds(5));
    for (int ii = 0; ii < 600 ; ii++)
    {
        for(auto &uav : field.uavs)
        {
//            uav.
        }
    }
    printf("Done\n");
    t1.join();
    return 0;
}
