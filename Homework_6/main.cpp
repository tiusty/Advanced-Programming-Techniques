/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 11/14/2019
Description:
 Main function that serves as the entry point
*/

#include <iostream>
#include <GL/glut.h>
#include <cmath>

#include "board.h"

#define ESC 27

// Global board class
Board board;

bool gl0Enable{true};
bool gl1Enable{true};
bool enhanced{true};

// Camera position
float x = 4, y = -10, z = 10; // initially 5 units south of origin

// Set light properties
GLfloat light_off[] = {0,0,0,0};
GLfloat light0_ambient[] = { 0.2, 0.2, 0.2, 1.0 };

GLfloat light1_diffuse[] = { .5, .5, .5, 1.0 };
GLfloat light1_specular[] = { 0.3, 0.3, 0.3, 1.0 };
GLfloat light1_position[] = { 5, 5, 8};

/**
 * Changes the size of the window based on if the window is resized
 */
void changeSize(int w, int h)
{
    float ratio = ((float)w) / ((float)h); // window aspect ratio
    glMatrixMode(GL_PROJECTION); // projection matrix is active
    glLoadIdentity(); // reset the projection
    gluPerspective(45.0, ratio, 0.1, 200.0); // perspective transformation
    glMatrixMode(GL_MODELVIEW); // return to modelview mode
    glViewport(0, 0, w, h); // set viewport (drawing area) to entire window
}

/**
 * Given changes to the window, updates the screen
 */
void update(void)
{
    glutPostRedisplay(); // redisplay everything
}

/**
 * Processes changes made by normal keys from the keyboard
 */
void processNormalKeys(unsigned char key, int xx, int yy)
{
    if (key == ESC || key == 'q' || key == 'Q')
    {
        exit(0);
    }
    else if (key == 'r' || key == 'R')
    {
        // We want it to circle around the point (4,4) which is the center of the chess board
        double theta = atan2((y-4),(x-4));
        // Add 10 degree to the angle
        theta = theta - (10.0/180)*3.14;
        // Find the distance from the center
        double r = sqrt((x-4)*(x-4) + (y-4)*(y-4));
        // Calculate the new position of the camera
        x = r*cos(theta) + 4;
        y = r*sin(theta) + 4;
    }
    else if(key == 'd' || key == 'D')
    {
        // Move camera position down
        z = z - .25;
    }
    else if(key == 'u' || key == 'P')
    {
        // Move camera position up
        z = z + .25;
    }
    else if(key == '0')
    {
        // Disable/Enable light0
        gl0Enable = !gl0Enable;
    }
    else if(key == '1')
    {
        //Disable/Enable light 1
        gl1Enable = !gl1Enable;
    }
    else if(key == 'e' || key == 'E')
    {
        // Determine if enhanced mode should be used or not
        enhanced = !enhanced;
    }
    else if(key == 'p' || key == 'P')
    {
        // Moves a random pawn
        board.movePawn();
    }
    else if(key == 'k' || key == 'K')
    {
        // Moves a random knight
        board.moveKnight();
    }
}

// Handles any special key presses
void pressSpecialKey(int key, int xx, int yy)
{
}

/**
 * Handles any special key releases
 */
void releaseSpecialKey(int key, int x, int y)
{
}

/**
 * Draws a single square of the chess board
 */
void drawSquare()
{
    // Draws a single square
    glBegin(GL_QUADS);
    glVertex3f(0, 0, 0.0);
    glVertex3f(Board::boardLen, 0, 0.0);
    glVertex3f(Board::boardLen, Board::boardLen, 0.0);
    glVertex3f(0, Board::boardLen, 0.0);
    glEnd();
}

/**
 * Renders the whole scene of the chess game
 */
void renderScene()
{
    // Clear color and depth buffers
    glClearColor(0.0, 0.7, 1.0, 1.0); // sky color is light blue
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();

    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);

    // Enable material color since lighting without material color looks black
    glEnable(GL_COLOR_MATERIAL);
    // Enable/Disable light 0
    if(gl0Enable)
    {
        glEnable(GL_LIGHT0);
    }
    else
    {
        glDisable(GL_LIGHT0);
    }
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_off);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_off);

    // Enable/Disable light 1
    if(gl1Enable)
    {
        glEnable(GL_LIGHT1);
    }
    else
    {
        glDisable(GL_LIGHT1);
    }
    // set light 1 properties
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_off);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

    // Enable depth test so things are rendered based on depth
    glEnable(GL_DEPTH_TEST);
    // Set Shade model
    glShadeModel(GL_SMOOTH);

    // Set the camera centered at (x,y,1) and looking along directional
    // vector (lx, ly, 0), with the z-axis pointing up
    gluLookAt(
            x, y, z,
            4, 4, 0.0,
            0.0, 0.0, 1.0);

    // Draw board
    bool color = true;
    // Draw all the squares
    for(int i=0; i<8; i++)
    {
        // Alternate colors for white and black squares
        color = i % 2 != 0;
        for(int j=0; j<8; j++)
        {
            if(color)
            {
                glColor3f(1, 1, 1);
            }
            else
            {
                glColor3f(0,0,0);
            }
            // Draw the square piece
            glPushMatrix();
            glNormal3f(0.0f, 0.0f, 1.0f);
            // Move the square to the right spot
            glTranslatef(i*Board::boardLen, j*Board::boardLen, 0);
            drawSquare();
            glPopMatrix();
            color = !color;
        }
    }

    // Draw all the pieces on the board
    board.drawPieces(enhanced);

    // Use swap buffer to prevent flickering
    glutSwapBuffers(); // Make it all visible
}

/**
 * main function that initializes the scene etc
 * Becomes blocked by the glut main program
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char **argv)
{

    // Initialize glut
    glutInit(&argc, argv);

    // Turn on RGB color, double buffering and depth testing
    int mode = GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH;
    glutInitDisplayMode(mode);

    // Set the initial window size
    glutInitWindowSize(600, 600);

    // Create the window, with the program name as the window name
    glutCreateWindow(argv[0]);

    glutIdleFunc(update); // incremental update
    glutSpecialFunc(pressSpecialKey); // process special key pressed
    // Warning: Nonstandard function! Delete if desired.
    glutSpecialUpFunc(releaseSpecialKey); // process special key release
    glutDisplayFunc(renderScene); // Renders the scene
    glutReshapeFunc(changeSize); // window reshape callback
    glutKeyboardFunc(processNormalKeys);

    // Start blocking glut main loop
    glutMainLoop();
}

