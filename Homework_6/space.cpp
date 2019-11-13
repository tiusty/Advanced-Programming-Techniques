/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 11/12/2019
Description: 
*/

#include <GL/glut.h>

#include "space.h"

GLfloat lightTeamColor[] = { 100.0, 100.0, 100.0};
GLfloat darkTeamColor[] = { 150, 75, 0 };
float mat_specular[] = {0.992157, 0.941176, 0.807843, 1.0};
float shininess = 10;



void Space::draw()
{
    if(type == Piece::pawn)
    {
        drawPawn();
    }
    else if(type == Piece::rook)
    {
        drawRook();
    }
    else if(type == Piece::knight)
    {
        drawKnight();
    }
    else if(type == Piece::bishop)
    {
        drawBishop();
    }
    else if(type == Piece::queen)
    {
        drawQueen();
    }
    else if(type == Piece::king)
    {
        drawKing();
    }
}

void Space::drawPawn()
{
    glPushMatrix();
    setColor();
    glTranslatef(0, 0, .5);
    glutSolidSphere(.5, 20, 20);
    glPopMatrix();
}

void Space::drawRook()
{
    glPushMatrix();
    setColor();
    glTranslatef(0,0,.5);
    glutSolidCube(1);
    glPopMatrix();
}

void Space::drawKnight()
{

    glPushMatrix();
    setColor();
    glTranslatef(0,0,.4);
    glutSolidTeapot(.4);
    glPopMatrix();
}

void Space::drawBishop()
{

    glPushMatrix();
    setColor();
    glutSolidCone(.5, 1, 20, 20);
    glPopMatrix();
}

void Space::drawQueen()
{

    glPushMatrix();
    setColor();
    glTranslatef(0,0,.7);
    glRotatef(50, 0,.5,.5);
    glutSolidTetrahedron();
    glPopMatrix();
}

void Space::drawKing()
{
    glPushMatrix();
    setColor();
    glTranslatef(0,0,.7);
    glRotatef(50, 0,.5,.5);
    glutSolidOctahedron();
    glPopMatrix();
}

void Space::setColor()
{
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    if(team)
    {
        glColor3i(lightTeamColor[0], lightTeamColor[1], lightTeamColor[2]); // set drawing color to white
    }
    else
    {
        glColor3i(darkTeamColor[0], darkTeamColor[1], darkTeamColor[2]); // set drawing color to white
    }
}