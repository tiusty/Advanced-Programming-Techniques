/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 11/22/2019
Description:
 Implements the uav class
*/

#include "uav.h"
#include <GL/glut.h>

// Determine piece material properties
GLfloat mat_specular[] = {0.5, 0.5, 0.5, 1.0};
GLfloat shininess[] = {50.0};
unsigned char uavColor[] = {255,0,0};

void UAV::drawUAV() const
{
    glPushMatrix();
    setColor();
    glTranslatef(location.x, location.y, location.z);
    glTranslatef(0, 0, .5);
    glutSolidSphere(.5, 20, 20);
    glPopMatrix();
}

void UAV::setColor() const
{
    // Set material properties
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

    // Clear the color
    glClearColor(0.0, 0.0, 0, 1.0);

    // Set color of the UAV
    glColor3ub(uavColor[0], uavColor[1], uavColor[2]); // set drawing color to white
}
