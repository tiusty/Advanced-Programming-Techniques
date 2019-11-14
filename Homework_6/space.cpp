/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 11/12/2019
Description: 
*/

#include <GL/glut.h>

#include "space.h"

GLfloat lightTeamColor[] = { 100.0/255, 100.0/255, 100.0/255};
GLfloat darkTeamColor[] = { 150/255, 75/255, 0/255 };
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
        setColor();
        glTranslatef(-.5,.5,0);
        glScalef(4, 4, 4);
        glRotatef(90,1,0,0);
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
    float scale = 3.72*4.0;
    float x=0, y=0;
    GLUquadricObj* object;
    object = gluNewQuadric();
    gluQuadricDrawStyle(object, GLU_FILL);
    gluQuadricNormals(object, GL_SMOOTH);
    gluQuadricTexture(object, GL_TRUE);
    //head
    //A-B
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 5.6/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .35/scale, 0, .16/scale, 10, 10);
    setColor();
    glPopMatrix();
    //B-C
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 5.38/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .30/scale, .35/scale, .22/scale, 10, 10);
    setColor();
    glPopMatrix();
    //C-D
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 5.11/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .52/scale, .30/scale, .27/scale, 10, 10);
    setColor();
    glPopMatrix();
    //D-E
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 4.72/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .72/scale, .52/scale, .39/scale, 10, 15);
    setColor();
    glPopMatrix();
    //E-F
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 4.37/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .80/scale, .72/scale, .35/scale, 10, 15);
    setColor();
    glPopMatrix();
    //F-G
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 4.11/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .82/scale, .80/scale, .26/scale, 10, 10);
    setColor();
    glPopMatrix();
    //G-H
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 4.11/scale, (y+.5)/4.0);
    glRotatef(90, -1,  0, 0);
    gluDisk(object, .69/scale, .82/scale, 10, 10);
    setColor();
    glPopMatrix();
    //H-I
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 4.06/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .69/scale, .69/scale, .05/scale, 10, 10);
    setColor();
    glPopMatrix();
    //I-J
    glPushMatrix();
    setColor();
    glTranslatef((x+.5)/4.0, 3.95/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0,  0);
    gluCylinder(object, .82/scale, .69/scale, .11/scale, 10, 10);
    glPopMatrix();
    //J-J2
    glPushMatrix();
    setColor();
    glTranslatef((x+.5)/4.0, 3.71/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .6/scale, .82/scale, .24/scale, 10, 10);
    glPopMatrix();
    //J2-K
    glPushMatrix();
    setColor();
    glTranslatef((x+.5)/4.0, 3.52/scale, (y+.5)/4.00);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .6/scale, .6/scale, .19/scale, 10, 10);
    glPopMatrix();
    //K-L
    glPushMatrix();
    setColor();
    glTranslatef((x+.5)/4.0, 3.46/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .82/scale, .6/scale, .06/scale, 10, 10);
    glPopMatrix();
    //L-M
    glPushMatrix();
    setColor();
    glTranslatef((x+.5)/4.0, 3.29/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .65/scale, .82/scale, .17/scale, 10, 10);
    glPopMatrix();
    //M-N
    glPushMatrix();
    setColor();
    glTranslatef((x+.5)/4.0, 3.07/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0,  0);
    gluCylinder(object, 1.05/scale, .65/scale, .22/scale, 15, 10);
    glPopMatrix();
    //N-O
    glPushMatrix();
    setColor();
    glTranslatef((x+.5)/4.0, 2.88/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .93/scale, 1.05/scale, .19/scale, 10, 10);
    glPopMatrix();
    //O-P
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 2.3/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .54/scale, .93/scale, .05/scale, 10, 10);
    glPopMatrix();
    //P-Q
    glPushMatrix();
    setColor();
    glTranslatef((x+.5)/4.0, 1.35/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .79/scale, .54/scale, 1.48/scale, 15, 30);
    setColor();
    glPopMatrix();
    //Q-R
    glPushMatrix();
    setColor();
    glTranslatef((x+.5)/4.0, 1.35/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluDisk(object, .79/scale, .96/scale, 10, 10);
    setColor();
    glPopMatrix();
    //R-S
    glPushMatrix();
    setColor();
    glTranslatef((x+.5)/4.0, .91/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, 1.01/scale, .96/scale, .44/scale, 10, 20);
    setColor();
    glPopMatrix();
    //S-T
    glPushMatrix();
    glTranslatef((x+.5)/4.0, .49/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, 1.42/scale, 1.01/scale, .42/scale, 10, 20);
    glPopMatrix();
    //T-U
    glPushMatrix();
    setColor();
    glTranslatef((x+.5)/4.0, .39/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, 1.31/scale, 1.42/scale, .1/scale, 10, 10);
    setColor();
    glPopMatrix();
    //U-V
    glPushMatrix();
    setColor();
    glTranslatef((x+.5)/4.0, .19/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, 1.42/scale, 1.31/scale, .2/scale, 10, 15);
    setColor();
    glPopMatrix();
    //V-W
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 0, (y+.5)/4.0);
    glRotatef(90, -1, 0,  0);
    gluCylinder(object, 1.42/scale, 1.42/scale, .19/scale, 10, 15);
    glPopMatrix();
    //bottom disk
    glPushMatrix();
    setColor();
    glTranslatef((x+.5)/4.0, 0, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluDisk(object, 0, 1.42/scale, 10, 10);
    setColor();
    glPopMatrix();

    gluDeleteQuadric(object);
    setColor();
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
//        glColor3f(lightTeamColor[0], lightTeamColor[1], lightTeamColor[2]); // set drawing color to white
glColor3f(1,0,0);
    }
    else
    {
//        glColor3f(darkTeamColor[0], darkTeamColor[1], darkTeamColor[2]); // set drawing color to white
        glColor3f(0,1,0);
    }
}