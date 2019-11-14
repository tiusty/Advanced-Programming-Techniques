/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 11/12/2019
Description: 
*/

// For drawing the 3D pieces, used code from:
// https://github.com/semaslo/3D_Chess/blob/master/

#include <GL/glut.h>
#include <math.h>

#include "space.h"

GLfloat lightTeamColor[] = { 100.0/255, 100.0/255, 100.0/255};
GLfloat darkTeamColor[] = { 150/255, 75/255, 0/255 };
float mat_specular[] = {0.992157, 0.941176, 0.807843, 1.0};
float shininess = 10;


void crossproduct3f(float *first, float *second, float *wheretoreturn)
{
    *wheretoreturn = *(first+1)*(*(second+2)) - *(first+2)*(*(second+1));
    *(wheretoreturn+1) = *first*(*(second+2)) - *(first+2)*(*second);
    *(wheretoreturn+2) = *first*(*(second+1)) - *(first+1)*(*second);
}

void subtract3f(float *first, float *second, float *whereto)
{
    *whereto = *first - *second;
    *(whereto+1) = *(first+1) - *(second+1);
    *(whereto+2) = *(first+2) - *(second+2);
}
void rescalenormals(float* array)
{
    float factor = sqrt(pow(*array, 2) + pow(*(array+1), 2) + pow(*(array+2), 2));
    *array = *array/factor;
    *(array+1) = *(array+1)/factor;
    *(array+2) = *(array+2)/factor;
}



void Space::draw()
{
    if(type == Piece::pawn)
    {
        setColor();
        glTranslatef(-.2,.15,0);
        glScalef(1, 1, 1);
        glRotatef(90,1,0,0);
        drawPawn();
    }
    else if(type == Piece::rook)
    {
        setColor();
        glTranslatef(-.1,.1,0);
        glScalef(1.1, 1.1, .75);
        glRotatef(90,1,0,0);
        drawRook();
    }
    else if(type == Piece::knight)
    {
        drawKnight();
    }
    else if(type == Piece::bishop)
    {
        setColor();
        glTranslatef(-.6,.6,0);
        glScalef(5, 5, 4);
        glRotatef(90,1,0,0);
        drawBishop();
    }
    else if(type == Piece::queen)
    {
        setColor();
        glTranslatef(-0.1,.15,0);
        glScalef(1, 1, .75);
        glRotatef(90,1,0,0);
        drawQueen();
    }
    else if(type == Piece::king)
    {
        setColor();
        glTranslatef(-.1,.15,0);
        glScalef(.9, .9, .75);
        glRotatef(90,1,0,0);
        drawKing();
    }
}

void Space::drawPawn()
{
    float x=0,y=0;
    float scale = 3.72*0.75;
    GLUquadricObj* object;
    object = gluNewQuadric();
    gluQuadricDrawStyle(object, GLU_FILL);
    gluQuadricNormals(object, GL_SMOOTH);
    gluQuadricTexture(object, GL_TRUE);
    //head
    glPushMatrix();
    glTranslatef((x+.5)/4.0f, 3.18/scale, (y+.5)/4.0);
    gluSphere(object, .54/scale, 10, 10);
    glPopMatrix();
    //B-C
    glPushMatrix();
    glTranslatef((x+.5)/4.0f, (2.46f)/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object,.64/scale, .25/scale, .21/scale, 10,10);
    glPopMatrix();
    //C-D
    glPushMatrix();
    glTranslatef((x+.5)/4.0f, 2.19f/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .48/scale, .64/scale, .27/scale, 10, 10);
    glPopMatrix();
    //E-F
    glPushMatrix();
    glTranslatef((x+.5)/4.0f, .98/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .80f/scale, .3/scale, 1.21/scale, 10, 10);
    glPopMatrix();
    //F-G - Disk
    glPushMatrix();
    glTranslatef((x+.5)/4.0f, .98/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluDisk(object, .8/scale, .83/scale, 10, 10);
    glPopMatrix();
    //G-H
    glPushMatrix();
    glTranslatef((x+.5)/4.0f, .41/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, 1.2/scale, .83f/scale, .57/scale, 10, 10);
    glPopMatrix();
    //H-I
    glPushMatrix();
    glTranslatef((x+.5)/4.0f, .32/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, 1.25/scale, 1.2/scale, .09/scale, 10,10);
    glPopMatrix();
    //I-J
    glPushMatrix();
    glTranslatef((x+.5)/4.0f, .22/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, 1.2/scale, 1.25/scale, .1/scale, 10,10);
    glPopMatrix();
    //J-K
    glPushMatrix();
    glTranslatef((x+.5)/4.0f, .18/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, 1.25/scale, 1.2/scale, .04/scale, 10,10);
    glPopMatrix();
    //K-L
    glPushMatrix();
    glTranslatef((x+.5)/4.0f, 0/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, 1.25f/scale, 1.25f/scale, .18/scale, 10,10);
    glPopMatrix();
    //Base
    glPushMatrix();
    glTranslatef((x+.5)/4.0f, 0.0, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluDisk(object, 0, 1.25/scale, 10, 10);
    glPopMatrix();

    gluDeleteQuadric(object);}

void Space::drawRook()
{
    float x=0,y=0;
    float scale = 3.72*.7;
    GLUquadricObj* object;
    object = gluNewQuadric();
    gluQuadricDrawStyle(object, GLU_FILL);
    gluQuadricNormals(object, GL_SMOOTH);
    gluQuadricTexture(object, GL_TRUE);
    //Disk at top
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 4.06/scale, (y+.5)/4.0);
    glRotatef(90, -1.0, 0.0, 0.0);
    gluDisk(object, 0, .92/scale, 10, 10);
    glPopMatrix();
    //A-B
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 3.72/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .85/scale, .96/scale, .53/scale, 10, 10);
    glPopMatrix();
    //B-C
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 3.61/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .88/scale, .85/scale, .09/scale, 10, 10);
    glPopMatrix();
    //C-D
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 3.23/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object,  .62/scale, .88/scale, .38/scale, 10, 10);
    glPopMatrix();
    //D-E (Disk)
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 3.23/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluDisk(object, .56/scale, .62/scale, 10, 10);
    glPopMatrix();
    //E-F
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 1.37/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .81/scale, .56/scale, 1.86/scale, 15, 15);
    glPopMatrix();
    //F-G (disk)
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 1.37/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluDisk(object, .81/scale, .85/scale, 10, 10);
    glPopMatrix();
    //G-H
    glPushMatrix();
    glTranslatef((x+.5)/4.0, .91/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .85/scale, .85/scale, .46/scale, 10, 10);
    glPopMatrix();
    //H-I
    glPushMatrix();
    glTranslatef((x+.5)/4.0, .60/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, 1.09/scale, .85/scale, .31/scale, 10, 10);
    glPopMatrix();
    //I-J
    glPushMatrix();
    glTranslatef((x+.5)/4.0, .33/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .98/scale, 1.09/scale, .27/scale, 10, 10);
    glPopMatrix();
    //J-K
    glPushMatrix();
    glTranslatef((x+.5)/4.0, .28/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, 1.09/scale, .98/scale, .05/scale, 10, 10);
    glPopMatrix();
    //K-L
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 0.0, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, 1.09/scale, 1.09/scale, .28/scale, 10, 10);
    glPopMatrix();
    //Bottom Disk
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 0.0, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluDisk(object, 0, 1.09/scale, 10, 10);
    glPopMatrix();

    gluDeleteQuadric(object);}

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
    glPopMatrix();
    //B-C
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 5.38/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .30/scale, .35/scale, .22/scale, 10, 10);
    glPopMatrix();
    //C-D
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 5.11/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .52/scale, .30/scale, .27/scale, 10, 10);
    glPopMatrix();
    //D-E
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 4.72/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .72/scale, .52/scale, .39/scale, 10, 15);
    glPopMatrix();
    //E-F
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 4.37/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .80/scale, .72/scale, .35/scale, 10, 15);
    glPopMatrix();
    //F-G
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 4.11/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .82/scale, .80/scale, .26/scale, 10, 10);
    glPopMatrix();
    //G-H
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 4.11/scale, (y+.5)/4.0);
    glRotatef(90, -1,  0, 0);
    gluDisk(object, .69/scale, .82/scale, 10, 10);
    glPopMatrix();
    //H-I
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 4.06/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .69/scale, .69/scale, .05/scale, 10, 10);
    glPopMatrix();
    //I-J
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 3.95/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0,  0);
    gluCylinder(object, .82/scale, .69/scale, .11/scale, 10, 10);
    glPopMatrix();
    //J-J2
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 3.71/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .6/scale, .82/scale, .24/scale, 10, 10);
    glPopMatrix();
    //J2-K
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 3.52/scale, (y+.5)/4.00);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .6/scale, .6/scale, .19/scale, 10, 10);
    glPopMatrix();
    //K-L
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 3.46/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .82/scale, .6/scale, .06/scale, 10, 10);
    glPopMatrix();
    //L-M
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 3.29/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .65/scale, .82/scale, .17/scale, 10, 10);
    glPopMatrix();
    //M-N
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 3.07/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0,  0);
    gluCylinder(object, 1.05/scale, .65/scale, .22/scale, 15, 10);
    glPopMatrix();
    //N-O
    glPushMatrix();
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
    glTranslatef((x+.5)/4.0, 1.35/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .79/scale, .54/scale, 1.48/scale, 15, 30);
    glPopMatrix();
    //Q-R
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 1.35/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluDisk(object, .79/scale, .96/scale, 10, 10);
    glPopMatrix();
    //R-S
    glPushMatrix();
    glTranslatef((x+.5)/4.0, .91/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, 1.01/scale, .96/scale, .44/scale, 10, 20);
    glPopMatrix();
    //S-T
    glPushMatrix();
    glTranslatef((x+.5)/4.0, .49/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, 1.42/scale, 1.01/scale, .42/scale, 10, 20);
    glPopMatrix();
    //T-U
    glPushMatrix();
    glTranslatef((x+.5)/4.0, .39/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, 1.31/scale, 1.42/scale, .1/scale, 10, 10);
    glPopMatrix();
    //U-V
    glPushMatrix();
    glTranslatef((x+.5)/4.0, .19/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, 1.42/scale, 1.31/scale, .2/scale, 10, 15);
    glPopMatrix();
    //V-W
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 0, (y+.5)/4.0);
    glRotatef(90, -1, 0,  0);
    gluCylinder(object, 1.42/scale, 1.42/scale, .19/scale, 10, 15);
    glPopMatrix();
    //bottom disk
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 0, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluDisk(object, 0, 1.42/scale, 10, 10);
    glPopMatrix();

    gluDeleteQuadric(object);
    glPopMatrix();
}

void Space::drawQueen()
{
    float x=0,y=0;
    float scale = 3.72*0.75;
    GLUquadricObj* object;
    object = gluNewQuadric();
    gluQuadricDrawStyle(object, GLU_FILL);
    gluQuadricNormals(object, GL_SMOOTH);
    gluQuadricTexture(object, GL_TRUE);
    //A-AA
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 6.82/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .17/scale, 0, .18/scale, 10, 10);
    glPopMatrix();
    //AA-B
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 6.54/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .23/scale, .17/scale, .28/scale, 10, 10);
    glPopMatrix();
    //B-C
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 6.40/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .72/scale, .23/scale, .14/scale, 10, 10);
    glPopMatrix();
    //C-D
    //change the direction of the normals because we'll actually be seeing the inside of the cylinder.
    gluQuadricOrientation(object, GLU_INSIDE);
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 6.40/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .86/scale, .72/scale, .14/scale, 10, 10);
    glPopMatrix();
    gluQuadricOrientation(object, GLU_OUTSIDE);
    //D-E(disk)
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 6.54/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluDisk(object, .86/scale, 1.06/scale, 10, 10);
    glPopMatrix();
    //E-F
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 6.05/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .72/scale, 1.06/scale, .49/scale, 10, 10);
    glPopMatrix();
    //F-G
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 5.22/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .72/scale, .83/scale, .83/scale, 15, 15);
    glPopMatrix();
    //G-H
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 5.12/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .87/scale, .72/scale, .1/scale, 10, 10);
    glPopMatrix();
    //H-I
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 5.02/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .72/scale, .87/scale, .1/scale, 10, 10);
    glPopMatrix();
    //I-J
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 4.69/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .9/scale, .72/scale, .33/scale, 10, 10);
    glPopMatrix();
    //J-K
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 4.16/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, 1.39/scale, .9/scale, .53/scale, 10, 10);
    glPopMatrix();
    //K-L
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 4.08/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, 1.28/scale, 1.39/scale, .08/scale, 10, 10);
    glPopMatrix();
    //L-M
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 3.97/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .69/scale, 1.28/scale, .11/scale, 10, 10);
    glPopMatrix();
    //M-N
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 1.81/scale, (y+.5)/4.0);
    glRotatef(90,  -1, 0, 0);
    gluCylinder(object, 1.04/scale, .69/scale, 2.16/scale, 20, 10);
    glPopMatrix();
    //N-O (Disk)
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 1.81/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluDisk(object, 1.04/scale, 1.18/scale, 10, 10);
    glPopMatrix();
    //O-P
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 1.21/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, 1.18/scale, 1.18/scale, .6/scale, 10, 10);
    glPopMatrix();
    //P-Q
    glPushMatrix();
    glTranslatef((x+.5)/4.0, .6/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, 1.59/scale, 1.18/scale, .61/scale, 10, 10);
    glPopMatrix();
    //Q-R
    glPushMatrix();
    glTranslatef((x+.5)/4.0, .37/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, 1.46/scale, 1.59/scale, .23/scale, 10, 10);
    glPopMatrix();
    //R-S
    glPushMatrix();
    glTranslatef((x+.5)/4.0, .31/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, 1.59/scale, 1.46/scale, .06/scale, 10, 10);
    glPopMatrix();
    //S-T
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 0.0, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, 1.59/scale, 1.59/scale, .31/scale, 10, 10);
    glPopMatrix();
    //Base
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 0.0, (y+.5)/4.0);
    glRotatef(90, -1,  0, 0);
    gluDisk(object, 0, 1.59/scale, 10, 10);
    glPopMatrix();

    gluDeleteQuadric(object);}

void Space::drawKing()
{
    float x=0,y=0;
    float scale = 3.72*0.75;

    float Atoppeak[] = {0, 8.02, .2};   float ABtoppeak[] = {0, 8.02, -.2};
    float Btopside[] = {.31, 7.81, .2}; float BBtopside[] = {.31, 7.81, -.2};
    float BLtopside[] = {-.31, 7.81, .2}; float BLBtopside[] = {-.31, 7.81, -.2};
    float Ctopinside[] = {.24, 7.70, .2};   float CBtopinside[] = {.24, 7.70, -.2};
    float CLtopinside[] = {-.24, 7.70, .2}; float CLBtopinside[] = {-.24, 7.70, -.2};
    float Duppermid[] = {.63, 7.70, .2};    float DBuppermid[] = {.63, 7.70, -.2};
    float DLuppermid [] = {-.63, 7.70, .2};   float DLBuppermid[] = {-.63, 7.70, -.2};
    float Elowermid[] = {.63, 7.15, .2};    float EBlowermid[] = {.63, 7.15, -.2};
    float ELlowermid[] = {-.63, 7.15, .2};     float ELBlowermid[] = {-.63, 7.15, -.2};
    float Fmidinside[] = {.30, 7.15, .2}; float FBmidinside[] = {.30, 7.15, -.2};
    float FLmidinside[] = {-.30, 7.15, -.2}; float FLBmidinside[] = {-.30, 7.15, -.2};
    float Glowerside[] = {.51, 6.89, .2};   float GBlowerside[] = {.51, 6.89, -.2};
    float GLlowerside[] = {-.51, 6.89, .2};
    float HBlowerinside[] = {.47, 6.85, -.2};
    float HLlowerinside[] = {-.47, 6.85, .2}; float HLBlowerinside[] = {-.47, 6.85, -.2};
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 0, (y+.5)/4.0);
    glBegin(GL_POLYGON);
    //Front Diamond
    float temp1[3];
    float temp2[3];
    float temp3[3];
    subtract3f(Atoppeak, Btopside, temp1);
    subtract3f(Btopside, Ctopinside, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(0, 8.02/scale); glVertex3f(0, 8.02/scale, .2/scale);
    glTexCoord2f(.31/scale, 7.81/scale); glVertex3f(.31/scale, 7.81/scale, .2/scale);
    glTexCoord2f(.24/scale, 7.70/scale); glVertex3f(.24/scale, 7.70/scale, .2/scale);
    glTexCoord2f(-.24/scale, 7.70/scale); glVertex3f(-.24/scale, 7.70/scale, .2/scale);
    glTexCoord2f(-.31/scale, 7.81/scale); glVertex3f(-.31/scale, 7.81/scale, .2/scale);
    glEnd();
    glBegin(GL_QUADS);
    //Middle Rectangle
    glTexCoord2f(.63/scale, 7.70/scale); glVertex3f(.63/scale, 7.70/scale, .2/scale);
    glTexCoord2f(.63/scale, 7.15/scale); glVertex3f(.63/scale, 7.15/scale, .2/scale);
    glTexCoord2f(-.63/scale, 7.15/scale); glVertex3f(-.63/scale, 7.15/scale, .2/scale);
    glTexCoord2f(-.63/scale, 7.70/scale); glVertex3f(-.63/scale, 7.70/scale, .2/scale);

    //Bottom Triangle
    glTexCoord2f(.30/scale, 7.15/scale); glVertex3f(.30/scale, 7.15/scale, .2/scale);
    glTexCoord2f(-.3/scale, 7.15/scale); glVertex3f(-.30/scale, 7.15/scale, .2/scale);
    glTexCoord2f(-.51/scale, 6.89/scale); glVertex3f(-.51/scale, 6.89/scale, .2/scale);
    glTexCoord2f(.51/scale, 6.89/scale); glVertex3f(.51/scale, 6.89/scale, .2/scale);

    //Bottom Half of Bottom Triangle
    glTexCoord2f(.51/scale, 6.89/scale); glVertex3f(.51/scale, 6.89/scale, .2/scale);
    glTexCoord2f(-.51/scale, 6.89/scale); glVertex3f(-.51/scale, 6.89/scale, .2/scale);
    glTexCoord2f(-.47/scale, 6.85/scale); glVertex3f(-.47/scale, 6.85/scale, .2/scale);
    glTexCoord2f(.47/scale, 6.85/scale); glVertex3f(.47/scale, 6.85/scale, .2/scale);

    glEnd();
    subtract3f(ABtoppeak, BBtopside, temp1);
    subtract3f(BBtopside, CBtopinside, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    //Back Diamond
    glBegin(GL_POLYGON);
    glTexCoord2f(0, 8.02/scale); glVertex3f(0, 8.02/scale, -.2/scale);
    glTexCoord2f(.31/scale, 7.81/scale); glVertex3f(.31/scale, 7.81/scale, -.2/scale);
    glTexCoord2f(.24/scale, 7.70/scale); glVertex3f(.24/scale, 7.70/scale, -.2/scale);
    glTexCoord2f(-.24/scale, 7.70/scale); glVertex3f(-.24/scale, 7.70/scale, -.2/scale);
    glTexCoord2f(-.31/scale, 7.81/scale); glVertex3f(-.31/scale, 7.81/scale, -.2/scale);
    glEnd();
    //Back of Middle Rectangle
    glBegin(GL_QUADS);
    glTexCoord2f(.63/scale, 7.70/scale); glVertex3f(.63/scale, 7.70/scale, -.2/scale);
    glTexCoord2f(.63/scale, 7.15/scale); glVertex3f(.63/scale, 7.15/scale, -.2/scale);
    glTexCoord2f(-.63/scale, 7.15/scale); glVertex3f(-.63/scale, 7.15/scale, -.2/scale);
    glTexCoord2f(-.63/scale, 7.70/scale); glVertex3f(-.63/scale, 7.70/scale, -.2/scale);

    //Back of Bottom Triangle
    glTexCoord2f(.30/scale, 7.15/scale); glVertex3f(.30/scale, 7.15/scale, -.2/scale);
    glTexCoord2f(-.30/scale, 7.15/scale); glVertex3f(-.30/scale, 7.15/scale, -.2/scale);
    glTexCoord2f(-.51/scale, 6.89/scale); glVertex3f(-.51/scale, 6.89/scale, -.2/scale);
    glTexCoord2f(.51/scale, 6.89/scale); glVertex3f(.51/scale, 6.89/scale, -.2/scale);
    //Back Bottom Half of Bottom Triangle
    glTexCoord2f(.51/scale, 6.89/scale); glVertex3f(.51/scale, 6.89/scale, -.2/scale);
    glTexCoord2f(-.51/scale, 6.89/scale); glVertex3f(-.51/scale, 6.89/scale, -.2/scale);
    glTexCoord2f(-.47/scale, 6.85/scale); glVertex3f(-.47/scale, 6.85/scale, -.2/scale);
    glTexCoord2f(.47/scale, 6.85/scale); glVertex3f(.47/scale, 6.85/scale, -.2/scale);

    //Sides of middle rectangle
    subtract3f(Ctopinside, CBtopinside, temp1);
    subtract3f(CBtopinside, Duppermid, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(.24/scale, 7.70/scale); glVertex3f(.24/scale, 7.70/scale, .2/scale);
    glTexCoord2f(.24/scale, 7.70/scale); glVertex3f(.24/scale, 7.70/scale, -.2/scale);
    glTexCoord2f(.63/scale, 7.70/scale); glVertex3f(.63/scale, 7.70/scale, -.2/scale);
    glTexCoord2f(.63/scale, 7.70/scale); glVertex3f(.63/scale, 7.70/scale, .2/scale);

    subtract3f(Duppermid, DBuppermid, temp1);
    subtract3f(DBuppermid, Elowermid, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(.63/scale, 7.70/scale); glVertex3f(.63/scale, 7.70/scale, -.2/scale);
    glVertex3f(.63/scale, 7.70/scale, .2/scale);
    glTexCoord2f(.63/scale, 7.15/scale); glVertex3f(.63/scale, 7.15/scale, .2/scale);
    glVertex3f(.63/scale, 7.15/scale, -.2/scale);

    subtract3f(EBlowermid, Elowermid, temp1);
    subtract3f(Elowermid, Fmidinside, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glVertex3f(.63/scale, 7.15/scale, -.2/scale);
    glVertex3f(.63/scale, 7.15/scale, .2/scale);
    glTexCoord2f(.30/scale, 7.15/scale); glVertex3f(.30/scale, 7.15/scale, .2/scale);
    glVertex3f(.30/scale, 7.15/scale, -.2/scale);

    subtract3f(CLtopinside, CLBtopinside, temp1);
    subtract3f(CLBtopinside, DLuppermid, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(-.24/scale, 7.70/scale); glVertex3f(-.24/scale, 7.70/scale, .2/scale);
    glVertex3f(-.24/scale, 7.70/scale, -.2/scale);
    glTexCoord2f(-.63/scale, 7.70/scale); glVertex3f(-.63/scale, 7.70/scale, -.2/scale);
    glVertex3f(-.63/scale, 7.70/scale, .2/scale);

    subtract3f(DLBuppermid, DLuppermid, temp1);
    subtract3f(DLuppermid, ELlowermid, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(-.63/scale, 7.70/scale); glVertex3f(-.63/scale, 7.70/scale, -.2/scale);
    glVertex3f(-.63/scale, 7.70/scale, .2/scale);
    glTexCoord2f(-.63/scale, 7.15/scale); glVertex3f(-.63/scale, 7.15/scale, .2/scale);
    glVertex3f(-.63/scale, 7.15/scale, -.2/scale);

    subtract3f(ELBlowermid, ELlowermid, temp1);
    subtract3f(ELlowermid, FLmidinside, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(-.63/scale, 7.15/scale); glVertex3f(-.63/scale, 7.15/scale, -.2/scale);
    glVertex3f(-.63/scale, 7.15/scale, .2/scale);
    glTexCoord2f(-.3/scale, 7.15/scale); glVertex3f(-.30/scale, 7.15/scale, .2/scale);
    glVertex3f(-.30/scale, 7.15/scale, -.2/scale);

    //Sides of diamond
    subtract3f(ABtoppeak, BBtopside, temp1);
    subtract3f(BBtopside, Btopside, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(0, 8.02/scale); glVertex3f(0, 8.02/scale, -.2/scale);
    glTexCoord2f(.31/scale, 7.81/scale); glVertex3f(.31/scale, 7.81/scale, -.2/scale);
    glVertex3f(.31/scale, 7.81/scale, .2/scale);
    glTexCoord2f(0, 8.02/scale); glVertex3f(0, 8.02/scale, .2/scale);

    subtract3f(BBtopside, Btopside, temp1);
    subtract3f(Btopside, Ctopinside, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(.31/scale, 7.81/scale); glVertex3f(.31/scale, 7.81/scale, -.2/scale);
    glVertex3f(.31/scale, 7.81/scale, .2/scale);
    glTexCoord2f(.24/scale, 7.70/scale); glVertex3f(.24/scale, 7.70/scale, .2/scale);
    glVertex3f(.24/scale, 7.70/scale, -.2/scale);

    subtract3f(ABtoppeak, BLBtopside, temp1);
    subtract3f(BLBtopside, BLtopside, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(0, 8.02/scale); glVertex3f(0, 8.02/scale, -.2/scale);
    glTexCoord2f(-.31/scale, 7.81/scale); glVertex3f(-.31/scale, 7.81/scale, -.2/scale);
    glVertex3f(-.31/scale, 7.81/scale, .2/scale);
    glTexCoord2f(0, 8.02/scale); glVertex3f(0, 8.02/scale, .2/scale);

    subtract3f(BLBtopside, BLtopside, temp1);
    subtract3f(BLtopside, CLtopinside, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(-.31/scale, 7.81/scale); glVertex3f(-.31/scale, 7.81/scale, -.2/scale);
    glVertex3f(-.31/scale, 7.81/scale, .2/scale);
    glTexCoord2f(-.24/scale, 7.70/scale); glVertex3f(-.24/scale, 7.70/scale, .2/scale);
    glVertex3f(-.24/scale, 7.70/scale, -.2/scale);


    //Sides of bottom triangle
    subtract3f(Fmidinside, FBmidinside, temp1);
    subtract3f(FBmidinside, Glowerside, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(.3/scale, 7.15/scale); glVertex3f(.30/scale, 7.15/scale, .2/scale);
    glVertex3f(.30/scale, 7.15/scale, -.2/scale);
    glTexCoord2f(.51/scale, 6.89/scale); glVertex3f(.51/scale, 6.89/scale, -.2/scale);
    glVertex3f(.51/scale, 6.89/scale, .2/scale);

    subtract3f(FLmidinside, FLBmidinside, temp1);
    subtract3f(FLBmidinside, GLlowerside, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(-.3/scale, 7.15/scale); glVertex3f(-.30/scale, 7.15/scale, .2/scale);
    glVertex3f(-.30/scale, 7.15/scale, -.2/scale);
    glTexCoord2f(-.51/scale, 6.89/scale); glVertex3f(-.51/scale, 6.89/scale, -.2/scale);
    glVertex3f(-.51/scale, 6.89/scale, .2/scale);
    //Sides of Bottom Triangle Bottom Half
    subtract3f(HBlowerinside, GBlowerside, temp1);
    subtract3f(GBlowerside, Glowerside, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glVertex3f(.51/scale, 6.89/scale, -.2/scale);
    glTexCoord2f(.47/scale, 6.85/scale); glVertex3f(.47/scale, 6.85/scale, -.2/scale);
    glVertex3f(.47/scale, 6.85/scale, .2/scale);
    glTexCoord2f(.51/scale, 6.89/scale); glVertex3f(.51/scale, 6.89/scale, .2/scale);

    subtract3f(HLBlowerinside, HLlowerinside, temp1);
    subtract3f(HLlowerinside, GLlowerside, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(-.47/scale, 6.85/scale); glVertex3f(-.47/scale, 6.85/scale, -.2/scale);
    glVertex3f(-.47/scale, 6.85/scale, .2/scale);
    glTexCoord2f(-.51/scale, 6.89/scale); glVertex3f(-.51/scale, 6.89/scale, .2/scale);
    glVertex3f(-.51/scale, 6.89/scale, -.2/scale);

    glEnd();
    glPopMatrix();

    //Cylinders
    GLUquadricObj* object;
    object = gluNewQuadric();
    gluQuadricDrawStyle(object, GLU_FILL);
    gluQuadricNormals(object, GL_SMOOTH);
    gluQuadricTexture(object, GL_TRUE);
    //H-I Disk and Top Disk
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 6.85/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluDisk(object, 0, .68/scale, 10, 10);
    glPopMatrix();
    //I-J
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 6.69/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .82/scale, .68/scale, .16/scale, 10, 10);
    glPopMatrix();
    //J-K
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 6.48/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, 1.18/scale, .82/scale, .21/scale, 15, 10);
    glPopMatrix();
    //K-L
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 5.38/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .88/scale, 1.18/scale, 1.1/scale, 20, 10);
    glPopMatrix();
    //L-M
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 5.34/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .9/scale, .88/scale, .04/scale, 10, 10);
    glPopMatrix();
    //M-N
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 5.22/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .9/scale, .9/scale, .12/scale, 10, 10);
    glPopMatrix();
    //N-O
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 5.18/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .78/scale, .9/scale, .04/scale, 10, 10);
    glPopMatrix();
    //O-P
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 4.79/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .78/scale, .78/scale, .39/scale, 20, 20);
    glPopMatrix();
    //P-Q - Disk
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 4.79/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluDisk(object, .78/scale, .86/scale, 10, 10);
    glPopMatrix();
    //Q-R
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 4.66/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .86/scale, .86/scale, .11/scale, 15, 10);
    glPopMatrix();
    //R-S
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 4.25/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, 1.09/scale, .86/scale, .41/scale, 20, 10);
    glPopMatrix();
    //S-T
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 4.09/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .53/scale, 1.09/scale, .16/scale, 10, 10);
    glPopMatrix();
    //T-U
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 1.91/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, .88/scale, .53/scale, 2.18/scale, 25, 10);
    glPopMatrix();
    //U-V - Disk
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 1.91/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluDisk(object, .88/scale, 1.02/scale, 10, 10);
    glPopMatrix();
    //V-W
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 1.40/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, 1.07/scale, 1.02/scale, .51/scale, 15, 20);
    glPopMatrix();
    //W-X
    glPushMatrix();
    glTranslatef((x+.5)/4.0, .67/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, 1.51/scale, 1.07/scale, .73/scale, 15, 10);
    glPopMatrix();
    //X-Y
    glPushMatrix();
    glTranslatef((x+.5)/4.0, .42/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, 1.37/scale, 1.51/scale, .25/scale, 10, 10);
    glPopMatrix();
    //Y-Z
    glPushMatrix();
    glTranslatef((x+.5)/4.0, .31/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, 1.37/scale, 1.51/scale, .11/scale, 10, 10);
    glPopMatrix();
    //Z-AA
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 0, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, 1.51/scale, 1.51/scale, .31/scale, 10, 10);
    glPopMatrix();

    gluDeleteQuadric(object);}

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