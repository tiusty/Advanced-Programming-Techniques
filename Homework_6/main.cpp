/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 11/7/2019
Description: 
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
    glutInitWindowSize(800, 800);
    glutCreateWindow("hello");
    glutDisplayFunc(display);
    glutMainLoop();
}
