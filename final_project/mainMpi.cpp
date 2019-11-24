/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 11/24/2019
Description: 
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include "iomanip"
#include <cmath>
#include <math.h>
#include <cstdlib>
#include <GL/glut.h>
#include <chrono>
#include <thread>

#include "footballField.h"

// Define an instance of a football field
FootballField field;
unsigned int colorOscillations{0};
bool decrease{false};


const int rcvSize = 16 * field.numElements; // (Main task + 15 UAVs) * numElements

double* rcvbuffer = new double[rcvSize];

double sendBuffer[field.numElements];

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

    field.drawField();
    field.drawSphere();
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

    MPI_Allgather(sendBuffer, field.numElements, MPI_DOUBLE, rcvbuffer, field.numElements, MPI_DOUBLE, MPI_COMM_WORLD);
    field.setFieldData(rcvbuffer);
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
    int numTasks, rank;

    int rc = MPI_Init(&argc, &argv);

    if (rc != MPI_SUCCESS)
    {
        printf("Error starting MPI program. Terminating.\n");
        MPI_Abort(MPI_COMM_WORLD, rc);
    }

    MPI_Comm_size(MPI_COMM_WORLD, &numTasks);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int gsize = 0;

    MPI_Comm_size(MPI_COMM_WORLD, &gsize);


    if (rank == 0)
    {
        mainOpenGL(argc, argv);
    }
    else
    {
        unsigned int uavNum = rank-1;
        // Sleep for 5 seconds
        std::this_thread::sleep_for(std::chrono::seconds(5));
        for (int ii = 0; ii < 600 ; ii++)
        {
            field.checkCollisions();
            field.uavs.at(uavNum).evolveSystem();
            field.getUavData(sendBuffer, uavNum);
            MPI_Allgather(sendBuffer, field.numElements, MPI_DOUBLE, rcvbuffer, field.numElements, MPI_DOUBLE, MPI_COMM_WORLD);
            field.setFieldData(rcvbuffer);
        }
    }
    return 0;
}