/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 11/7/2019
Description:
 Main function that serves as the entry point
*/

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

int main(int argc, char **argv)
{
    int mode = GLUT_RGB | GLUT_DOUBLE;
    glutInit(&argc, argv);
    glutInitDisplayMode(mode);
    glutInitWindowSize(600, 600);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutMainLoop();
}

