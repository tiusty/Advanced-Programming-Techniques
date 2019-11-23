/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 11/22/2019
Description: 
*/

#include "footballField.h"
#include <GL/glut.h>

// Define constexpr variables
constexpr float FootballField::lenFootballField;
constexpr float FootballField::widthFootballField;

void FootballField::drawField()
{
    glPushMatrix();
        glColor3f(0.0, 1.0, 0.0); // set drawing color to white
        glBegin(GL_QUADS);
        glVertex3f(0, 0, 0.0);
        glVertex3f(lenFootballField, 0, 0.0);
        glVertex3f(lenFootballField, widthFootballField, 0.0);
        glVertex3f(0, widthFootballField, 0.0);
        glEnd();
    glPopMatrix();
}
