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
#ifdef MPI
    #include "mpi.h"
#endif
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


FootballField field;
UAV uav1;

// Camera Parameters
float eye_x = 40, eye_y = -40, eye_z = 20;
float center_x = field.lenFootballField/2, center_y = field.widthFootballField/2, center_z = 0;


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
    gluPerspective(60.0, ratio, 0.1, 1000.0); // perspective transformation
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
    glClearColor(0.0, 0.0, 1.0, 1.0); // background color to green??
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

#ifdef MPI
    MPI_Allgather(sendBuffer, numElements, MPI_DOUBLE, rcvbuffer, numElements, MPI_DOUBLE, MPI_COMM_WORLD);
#endif
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
    int numTasks, rank=0;

#ifdef MPI
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
#endif


    if (rank == 0)
    {
        mainOpenGL(argc, argv);
    }
    else
    {
        // Sleep for 5 seconds
        std::this_thread::sleep_for(std::chrono::seconds(5));
        for (int ii = 0; ii < 600 ; ii++)
        {
//            CalcualteUAVsLocation(rank);
#ifdef MPI
            MPI_Allgather(sendBuffer, numElements, MPI_DOUBLE, rcvbuffer, numElements, MPI_DOUBLE, MPI_COMM_WORLD);
#endif
        }
    }
    return 0;
}
