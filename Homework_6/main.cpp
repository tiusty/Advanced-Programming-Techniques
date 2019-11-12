/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 11/7/2019
Description:
 Main function that serves as the entry point
*/

#include <iostream>
#include <GL/glut.h>

#define ESC 27

// Camera position
float x = 30, y = 30; // initially 5 units south of origin
float deltaMove = 0.0; // initially camera doesn't move
double squareLen = 10;

// Camera direction
float lx = 1.0, ly = 0; // camera points initially along y-axis
float angle = 0.0; // angle of rotation for the camera direction
float deltaAngle = 0.0; // additional angle change when dragging

GLfloat light0_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat light0_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light0_position[] = { 1.0, 1.0, 1.0, 0.0 };

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor4f(1, 1, 0, 1);
    glBegin(GL_POLYGON);
    glVertex2f(-0.5, -0.5);
    glVertex2f(-0.5, 0.5);
    glVertex2f(0.5, 0.5);
    glVertex2f(0.5, -0.5);
    glEnd();
    glutSwapBuffers();
}

void changeSize(int w, int h)
{
    float ratio = ((float)w) / ((float)h); // window aspect ratio
    glMatrixMode(GL_PROJECTION); // projection matrix is active
    glLoadIdentity(); // reset the projection
    gluPerspective(45.0, ratio, 0.1, 200.0); // perspective transformation
    glMatrixMode(GL_MODELVIEW); // return to modelview mode
    glViewport(0, 0, w, h); // set viewport (drawing area) to entire window
}

void update(void)
{
    if (deltaMove) { // update camera position
        x += deltaMove * lx * 0.1;
        y += deltaMove * ly * 0.1;
    }
    glutPostRedisplay(); // redisplay everything
}
void processNormalKeys(unsigned char key, int xx, int yy)
{
    if (key == ESC || key == 'q' || key == 'Q')
    {
        exit(0);
    }
}


void pressSpecialKey(int key, int xx, int yy)
{
    switch (key)
    {
        std::cout << "Pressed" << std::endl;
        case GLUT_KEY_UP: deltaMove = 1.0; break;
        case GLUT_KEY_DOWN: deltaMove = -1.0; break;
    }
}

void releaseSpecialKey(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_UP: deltaMove = 0.0; break;
        case GLUT_KEY_DOWN: deltaMove = 0.0; break;
    }
}

void drawSquare()
{
    glBegin(GL_QUADS);
    glVertex3f(0, 0, 0.0);
    glVertex3f(squareLen, 0, 0.0);
    glVertex3f(squareLen, squareLen, 0.0);
    glVertex3f(0, squareLen, 0.0);
    glEnd();
}


void renderScene()
{
    // Clear color and depth buffers
    glClearColor(0.0, 0.7, 1.0, 1.0); // sky color is light blue
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();

    // Enable lighting
    glEnable(GL_LIGHTING);
    // Enable material color since lighting without material color looks black
    glEnable(GL_COLOR_MATERIAL);
    // Enable light 0
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

    // Enable depth test so things are rendered based on depth
    glEnable(GL_DEPTH_TEST);


    // Set the camera centered at (x,y,1) and looking along directional
    // vector (lx, ly, 0), with the z-axis pointing up
    gluLookAt(
            x, y, 150,
            x + lx, y + ly, 0.0,
            0.0, 1.0, 0.0);

    // Draw ground - 200x200 square colored green
    bool color = true;
    for(int i=0; i<8; i++)
    {
        if(i%2 == 0)
        {
            color = false;
        }
        else
        {
            color = true;
        }
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
            glPushMatrix();
            glTranslatef(i*squareLen, j*squareLen, 0);
            drawSquare();
            glPopMatrix();
            color = !color;
        }
    }

    // Use swap buffer to prevent flickering
    glutSwapBuffers(); // Make it all visible
}

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
//    glMatrixMode(GL_PROJECTION);
//    gluPerspective(180.0, 4.5, 1.0,10.0);
//    glMatrixMode(GL_MODELVIEW);

    // Start blocking glut main loop
    glutMainLoop();
}

