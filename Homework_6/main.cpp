/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 11/7/2019
Description:
 Main function that serves as the entry point
*/

#include <iostream>

// Camera position
float x = 100.0, y = 100.0; // initially 5 units south of origin
float deltaMove = 0.0; // initially camera doesn't move

// Camera direction
float lx = 0.0, ly = 1.0; // camera points initially along y-axis
float angle = 0.0; // angle of rotation for the camera direction
float deltaAngle = 0.0; // additional angle change when dragging

#include <GL/glut.h>
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

void update(void)
{
    if (deltaMove) { // update camera position
        x += deltaMove * lx * 0.1;
        y += deltaMove * ly * 0.1;
    }
    glutPostRedisplay(); // redisplay everything
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


void renderScene()
    {
        // Clear color and depth buffers
        glClearColor(0.0, 0.7, 1.0, 1.0); // sky color is light blue
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Reset transformations
        glLoadIdentity();

        // Set the camera centered at (x,y,1) and looking along directional
        // vector (lx, ly, 0), with the z-axis pointing up
        gluLookAt(
                x, y, 1.0,
                x + lx, y + ly, 0.0,
                0.0, 0.0, 1.0);

        // Draw ground - 200x200 square colored green
        bool color = true;
        for(int i=0; i<8; i++)
        {
            if(i%2 == 0)
            {
                color = false;
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
                glBegin(GL_QUADS);
                glVertex3f(0+100*i, 0+100*j, 0.0);
                glVertex3f(100+100*i, 0 + 100*j, 0.0);
                glVertex3f(100.0+100*i, 100.0+100*j, 0.0);
                glVertex3f(0 + 100*i, 100.0 + 100*j, 0.0);
                glEnd();
                glPopMatrix();
                color = !color;
            }
        }

        glutSwapBuffers(); // Make it all visible
}

int main(int argc, char **argv)
{
    int mode = GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH;
    glutInit(&argc, argv);
    glutInitDisplayMode(mode);
    glutInitWindowSize(600, 600);
    glutCreateWindow(argv[0]);
    glutIdleFunc(update); // incremental update
    glutSpecialFunc(pressSpecialKey); // process special key pressed
    // Warning: Nonstandard function! Delete if desired.
    glutSpecialUpFunc(releaseSpecialKey); // process special key release
    glutDisplayFunc(renderScene);
    glutMainLoop();
}

