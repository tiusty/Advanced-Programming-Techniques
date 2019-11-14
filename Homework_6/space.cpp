/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 11/14/2019
Description:
 Implements space class functionality
*/

// For drawing the 3D pieces, used code from:
// https://github.com/semaslo/3D_Chess/blob/master/

#include <GL/glut.h>
#include <math.h>

#include "space.h"

// Determine team colors
GLfloat lightTeamColor[] = { 140.0/255, 140.0/255, 135.0/255};
GLfloat darkTeamColor[] = { 150/255, 75/255, 0/255 };

// Determine piece material properties
float mat_specular[] = {0.5, 0.5, 0.5, 1.0};
float shininess = 50;

// Helper functions for drawing pieces
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

void Space::draw(bool enhanced)
{
    // Clear the color
    glClearColor(0.0, 0.7, 1.0, 1.0); // sky color is light blue

    // Determine which version of the piece to draw
    if(enhanced)
    {
        drawEnhanced();
    }
    else
    {
        drawRegular();
    }
}

void Space::drawRegular()
{
    // Determines which piece to draw
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
    glRotatef(90,1,0,0);
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



void Space::drawEnhanced()
{
    // Determines which piece to draw
    if(type == Piece::pawn)
    {
        setColor();
        glTranslatef(-.2,.15,0);
        glScalef(1, 1, 1);
        glRotatef(90,1,0,0);
        drawPawnEnhanced();
    }
    else if(type == Piece::rook)
    {
        setColor();
        glTranslatef(-.1,.1,0);
        glScalef(1.1, 1.1, .75);
        glRotatef(90,1,0,0);
        drawRookEnhanced();
    }
    else if(type == Piece::knight)
    {
        setColor();
        glTranslatef(-.1,.1,0);
        glScalef(.9, .9, .75);
        glRotatef(90,1,0,0);
        drawKnightEnhanced();
    }
    else if(type == Piece::bishop)
    {
        setColor();
        glTranslatef(-.6,.6,0);
        glScalef(5, 5, 4);
        glRotatef(90,1,0,0);
        drawBishopEnhanced();
    }
    else if(type == Piece::queen)
    {
        setColor();
        glTranslatef(-0.1,.1,0);
        glScalef(1, 1, .75);
        glRotatef(90,1,0,0);
        drawQueenEnhanced();
    }
    else if(type == Piece::king)
    {
        setColor();
        glTranslatef(-.1,.1,0);
        glScalef(.9, .9, .75);
        glRotatef(90,1,0,0);
        drawKingEnhanced();
    }
}

void Space::drawPawnEnhanced()
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

void Space::drawRookEnhanced()
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

void Space::drawKnightEnhanced()
{
    float x=0,y=0;
//Below are listed the vertices and their mirror on the back since the knight is symmetrical
    float scale = 3.72*0.75;
    float A[] = {-.4, 5.47, .31};   float AB[] = {-.4, 5.47, -.31};
    float B[] = {0, 5.12, .19};     float BB[] = {0, 5.12, -.19};
    float C[] = {.86, 4.48, .12};   float CB[] = {.86, 4.48, -.12};
    float D[] = {.78, 4.13, .16};   float DB[] = {.78, 4.13, -.16};
    float E[] = {.83, 3.99, .18};   float EB[] = {.83, 3.99, -.18};
    float E1[] = {.24, 4.86, .05};  float E1B[] = {.24, 4.86, -.05};
    float F[] = {.05, 3.84, .19};   float FB[] = {.05, 3.84, -.19};
    float G[] = {.89, 2.70, .22};   float GB[] = {.89, 2.70, -.22};
    float H[] = {.61, 1.99, .48};   float HB[] = {.61, 1.99, -.48};
    float P[] = {-.75, 1.91, .2};   float PB[] = {-.75, 1.91, -.2};
    float Q[] = {-1.06, 2.85, .1};  float QB[] = {-1.06, 2.85, -.1};
    float R[] = {-1.12, 3.51, .05}; float RB[] = {-1.12, 3.51, -.05};
    float S[] = {-.92, 4.22, .09};  float SB[] = {-.92, 4.22, -.09};
    float T[] = {-.48, 4.86, .28};  float TB[] = {-.48, 4.86, -.28};
    float U[] = {-.37, 4.32, .33};  float UB[] = {-.37, 4.32, -.33};
    float V[] = {-.25, 3.52, .38};  float VB[] = {-.25, 3.52, -.38};
    float W[] = {0, 2.49, .40};     float WB[] = {0, 2.49, -.40};
    float X[] = {.15, 2.49, .45};   float XB[] = {.05, 4.75, -.19};
    float Y[] = {.05, 4.75, .19};   float YB[] = {.05, 4.75, -.19};
    float Z[] = {.40, 4.57, .13};   float ZB[] = {.40, 4.57, -.13};
    float A2[] = {-.19, 5.12, .19}; float A2B[] = {-.19, 5.12, -.19};
    //Front-side of horse; multiple pieces to avoid concave polygons
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 0, (y+.5)/4.0);
    glBegin(GL_POLYGON);
    float temp1[3];
    float temp2[3];
    float temp3[3];
    subtract3f(W, X, temp1);
    subtract3f(X, H, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(.61/scale, 1.99/scale);    glVertex3f(.61/scale, 1.99/scale, .48/scale); //H
    glTexCoord2f(.15/scale, 2.49/scale);    glVertex3f(.15/scale, 2.49/scale, .45/scale); //X
    glTexCoord2f(0, 2.49/scale);      glVertex3f(0, 2.49/scale, .40/scale); //W
    glTexCoord2f(-.25/scale, 3.52/scale);   glVertex3f(-.25/scale, 3.52/scale, .38/scale); //V
    glTexCoord2f(-.37/scale, 4.32/scale);   glVertex3f(-.37/scale, 4.32/scale, .33/scale); //U
    glTexCoord2f(.05/scale, 3.84/scale);    glVertex3f(.05/scale, 3.84/scale, .19/scale); //F
    glTexCoord2f(.89/scale, 2.70/scale);    glVertex3f(.89/scale, 2.70/scale, .22/scale); //G
    glEnd();
    glBegin(GL_POLYGON);
    subtract3f(F, E, temp1);
    subtract3f(E, D, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(.05/scale, 3.84/scale); glVertex3f(.05/scale, 3.84/scale, .19/scale); //F
    glTexCoord2f(.83/scale, 3.99/scale); glVertex3f(.83/scale, 3.99/scale, .18/scale); //E
    glTexCoord2f(.78/scale, 4.13/scale); glVertex3f(.78/scale, 4.13/scale, .16/scale); //D
    glEnd();
    glBegin(GL_POLYGON);
    subtract3f(C, D, temp1);
    subtract3f(D, F, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);

    glTexCoord2f(.86/scale, 4.48/scale); glVertex3f(.86/scale, 4.48/scale, .12/scale); //C
    glTexCoord2f(.78/scale, 4.13/scale); glVertex3f(.78/scale, 4.13/scale, .16/scale); //D
    glTexCoord2f(.05/scale, 3.84/scale); glVertex3f(.05/scale, 3.84/scale, .19/scale); //F
    glTexCoord2f(-.37/scale, 4.32/scale); glVertex3f(-.37/scale, 4.32/scale, .33/scale); //U
    glTexCoord2f(.4/scale, 4.57/scale);  glVertex3f(.40/scale, 4.57/scale, .13/scale); //Z
    glEnd();
    glBegin(GL_POLYGON);
    subtract3f(U, Y, temp1);
    subtract3f(Y, Z, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(-.37/scale, 4.32/scale); glVertex3f(-.37/scale, 4.32/scale, .33/scale); //U
    glTexCoord2f(.05/scale, 4.75/scale); glVertex3f(.05/scale, 4.75/scale, .19/scale); //Y
    glTexCoord2f(.40/scale, 4.57/scale); glVertex3f(.40/scale, 4.57/scale, .13/scale); //Z
    glEnd();
    glBegin(GL_POLYGON);
    subtract3f(A, A2, temp1);
    subtract3f(A2, Y, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(-.4/scale, 5.47/scale); glVertex3f(-.4/scale, 5.47/scale, .31/scale); //A
    glTexCoord2f(-.19/scale, 5.12/scale); glVertex3f(-.19/scale, 5.12/scale, .19/scale); //A2
    glTexCoord2f(.05/scale, 4.75/scale); glVertex3f(.05/scale, 4.75/scale, .19/scale); //Y
    glTexCoord2f(-.37/scale, 4.32/scale); glVertex3f(-.37/scale, 4.32/scale, .33/scale); //U
    glEnd();
    //Back front-side
    glBegin(GL_POLYGON);
    subtract3f(HB, XB, temp1);
    subtract3f(XB, WB, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(.61/scale, 1.99/scale); glVertex3f(.61/scale, 1.99/scale, -.48/scale); //H
    glTexCoord2f(.15/scale, 2.49/scale); glVertex3f(.15/scale, 2.49/scale, -.45/scale); //X
    glTexCoord2f(0, 2.49/scale); glVertex3f(0, 2.49/scale, -.40/scale); //W
    glTexCoord2f(-.25/scale, 3.52/scale); glVertex3f(-.25/scale, 3.52/scale, -.38/scale); //V
    glTexCoord2f(-.37/scale, 4.32/scale); glVertex3f(-.37/scale, 4.32/scale, -.33/scale); //U
    glTexCoord2f(.05/scale, 3.84/scale); glVertex3f(.05/scale, 3.84/scale, -.19/scale); //F
    glTexCoord2f(.89/scale, 2.70/scale); glVertex3f(.89/scale, 2.70/scale, -.22/scale); //G
    glEnd();
    glBegin(GL_POLYGON);
    subtract3f(FB, EB, temp1);
    subtract3f(EB, DB, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(.05/scale, 3.84/scale); glVertex3f(.05/scale, 3.84/scale, -.19/scale); //F
    glTexCoord2f(.83/scale, 3.99/scale); glVertex3f(.83/scale, 3.99/scale, -.18/scale); //E
    glTexCoord2f(.78/scale, 4.13/scale); glVertex3f(.78/scale, 4.13/scale, -.16/scale); //D
    glEnd();
    glBegin(GL_POLYGON);
    subtract3f(CB, DB, temp1);
    subtract3f(DB, FB, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(.86/scale, 4.48/scale); glVertex3f(.86/scale, 4.48/scale, -.12/scale); //C
    glTexCoord2f(.78/scale, 4.13/scale); glVertex3f(.78/scale, 4.13/scale, -.16/scale); //D
    glTexCoord2f(.05/scale, 3.84/scale); glVertex3f(.05/scale, 3.84/scale, -.19/scale); //F
    glTexCoord2f(-.37/scale, 4.32/scale); glVertex3f(-.37/scale, 4.32/scale, -.33/scale); //U
    glTexCoord2f(.40/scale, 4.57/scale); glVertex3f(.40/scale, 4.57/scale, -.13/scale); //Z
    glEnd();
    glBegin(GL_POLYGON);
    subtract3f(UB, YB, temp1);
    subtract3f(YB, ZB, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(-.37/scale, 4.32/scale); glVertex3f(-.37/scale, 4.32/scale, -.33/scale); //U
    glTexCoord2f(.05/scale, 4.75/scale); glVertex3f(.05/scale, 4.75/scale, -.19/scale); //Y
    glTexCoord2f(.40/scale, 4.57/scale); glVertex3f(.40/scale, 4.57/scale, -.13/scale); //Z
    glEnd();
    glBegin(GL_POLYGON);
    subtract3f(AB, A2B, temp1);
    subtract3f(A2B, YB, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(-.4/scale, 5.47/scale); glVertex3f(-.4/scale, 5.47/scale, -.31/scale); //A
    glTexCoord2f(-.19/scale, 5.12/scale); glVertex3f(-.19/scale, 5.12/scale, -.19/scale); //A2
    glTexCoord2f(.05/scale, 4.75/scale); glVertex3f(.05/scale, 4.75/scale, -.19/scale); //Y
    glTexCoord2f(-.37/scale, 4.32/scale); glVertex3f(-.37/scale, 4.32/scale, -.33/scale); //U
    glEnd();
    //Back-side Split into multiple sections to avoid convex polygons
    glBegin(GL_TRIANGLES);
    subtract3f(A, T, temp1);
    subtract3f(T, U, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(-.4/scale, 5.47/scale); glVertex3f(-.4/scale, 5.47/scale, .31/scale); //A
    glTexCoord2f(-.48/scale, 4.86/scale); glVertex3f(-.48/scale, 4.86/scale, .28/scale); //T
    glTexCoord2f(-.37/scale, 4.32/scale); glVertex3f(-.37/scale, 4.32/scale, .33/scale); //U

    subtract3f(T, U, temp1);
    subtract3f(U, S, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(-.48/scale, 4.86/scale); glVertex3f(-.48/scale, 4.86/scale, .28/scale); //T
    glTexCoord2f(-.37/scale, 4.32/scale); glVertex3f(-.37/scale, 4.32/scale, .33/scale); //U
    glTexCoord2f(-.92/scale, 4.22/scale); glVertex3f(-.92/scale, 4.22/scale, .09/scale); //S
    glEnd();
    glBegin(GL_QUADS);
    subtract3f(S, U, temp1);
    subtract3f(U, R, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(-.37/scale, 4.32/scale); glVertex3f(-.37/scale, 4.32/scale, .33/scale); //U
    glTexCoord2f(-.92/scale, 4.22/scale); glVertex3f(-.92/scale, 4.22/scale, .09/scale); //S
    glTexCoord2f(-1.12/scale, 3.51/scale); glVertex3f(-1.12/scale, 3.51/scale, .05/scale); //R
    glTexCoord2f(-.25/scale, 3.52/scale); glVertex3f(-.25/scale, 3.52/scale, .38/scale); //V

    subtract3f(V, W, temp1);
    subtract3f(W, R, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(-1.12/scale, 3.51/scale); glVertex3f(-1.12/scale, 3.51/scale, .05/scale); //R
    glTexCoord2f(-.25/scale, 3.52/scale); glVertex3f(-.25/scale, 3.52/scale, .38/scale); //V
    glTexCoord2f(0, 2.95/scale); glVertex3f(0, 2.95/scale, .40/scale);  //W
    glTexCoord2f(-1.06/scale, 2.85/scale); glVertex3f(-1.06/scale, 2.85/scale, .1/scale); //Q

    subtract3f(X, P, temp1);
    subtract3f(P, Q, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(0, 2.95/scale); glVertex3f(0, 2.95/scale, .40/scale);  //W
    glTexCoord2f(-1.06/scale, 2.85/scale); glVertex3f(-1.06/scale, 2.85/scale, .1/scale); //Q
    glTexCoord2f(-.75/scale, 1.91/scale); glVertex3f(-.75/scale, 1.91/scale, .2/scale); //P
    glTexCoord2f(.15/scale, 2.49/scale); glVertex3f(.15/scale, 2.49/scale, .45/scale); //X
    glEnd();
    glBegin(GL_TRIANGLES);
    subtract3f(P, X, temp1);
    subtract3f(X, H, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(-.75/scale, 1.91/scale); glVertex3f(-.75/scale, 1.91/scale, .2/scale); //P
    glTexCoord2f(.15/scale, 2.49/scale); glVertex3f(.15/scale, 2.49/scale, .45/scale); //X
    glTexCoord2f(.61/scale, 1.99/scale); glVertex3f(.61/scale, 1.99/scale, .48/scale); //H
    glEnd();
    //Back Side Back
    glBegin(GL_TRIANGLES);
    subtract3f(AB, TB, temp1);
    subtract3f(TB, UB, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(-.4/scale, 5.47/scale); glVertex3f(-.4/scale, 5.47/scale, -.31/scale); //A
    glTexCoord2f(-.48/scale, 4.86/scale); glVertex3f(-.48/scale, 4.86/scale, -.28/scale); //T
    glTexCoord2f(-.37/scale, 4.32/scale); glVertex3f(-.37/scale, 4.32/scale, -.33/scale); //U

    subtract3f(TB, UB, temp1);
    subtract3f(UB, SB, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(-.48/scale, 4.86/scale); glVertex3f(-.48/scale, 4.86/scale, -.28/scale); //T
    glTexCoord2f(-.37/scale, 4.32/scale); glVertex3f(-.37/scale, 4.32/scale, -.33/scale); //U
    glTexCoord2f(-.92/scale, 4.22/scale); glVertex3f(-.92/scale, 4.22/scale, -.09/scale); //S
    glEnd();
    glBegin(GL_QUADS);
    subtract3f(RB, UB, temp1);
    subtract3f(UB, VB, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(-.37/scale, 4.32/scale); glVertex3f(-.37/scale, 4.32/scale, -.33/scale); //U
    glTexCoord2f(-.92/scale, 4.22/scale); glVertex3f(-.92/scale, 4.22/scale, -.09/scale); //S
    glTexCoord2f(-1.12/scale, 3.51/scale); glVertex3f(-1.12/scale, 3.51/scale, -.05/scale); //R
    glTexCoord2f(-.25/scale, 3.52/scale); glVertex3f(-.25/scale, 3.52/scale, -.38/scale); //V

    subtract3f(RB, VB, temp1);
    subtract3f(VB, WB, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(-1.12/scale, 3.51/scale); glVertex3f(-1.12/scale, 3.51/scale, -.05/scale); //R
    glTexCoord2f(-.25/scale, 3.52/scale); glVertex3f(-.25/scale, 3.52/scale, -.38/scale); //V
    glTexCoord2f(0, 2.95/scale); glVertex3f(0, 2.95/scale, -.40/scale);  //W
    glTexCoord2f(-1.06/scale, 2.85/scale); glVertex3f(-1.06/scale, 2.85/scale, -.1/scale); //Q

    subtract3f(QB, WB, temp1);
    subtract3f(WB, PB, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(0, 2.95/scale); glVertex3f(0, 2.95/scale, -.40/scale);  //W
    glTexCoord2f(-1.06/scale, 2.85/scale); glVertex3f(-1.06/scale, 2.85/scale, -.1/scale); //Q
    glTexCoord2f(-.75/scale, 1.91/scale); glVertex3f(-.75/scale, 1.91/scale, -.2/scale); //P
    glTexCoord2f(.15/scale, 2.49/scale); glVertex3f(.15/scale, 2.49/scale, -.45/scale); //X
    glEnd();
    glBegin(GL_TRIANGLES);
    subtract3f(PB, XB, temp1);
    subtract3f(XB, HB, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(-.75/scale, 1.91/scale); glVertex3f(-.75/scale, 1.91/scale, -.2/scale); //P
    glTexCoord2f(.15/scale, 2.49/scale); glVertex3f(.15/scale, 2.49/scale, -.45/scale); //X
    glTexCoord2f(.61/scale, 1.99/scale); glVertex3f(.61/scale, 1.99/scale, -.48/scale); //H
    glEnd();
    //Front and Chest of horse
    glBegin(GL_QUADS);
    subtract3f(HB, H, temp1);
    subtract3f(H, G, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(.61/scale, 1.99/scale); glVertex3f(.61/scale, 1.99/scale, -.48/scale); //H
    glTexCoord2f(.61/scale, 1.99/scale); glVertex3f(.61/scale, 1.99/scale, .48/scale); //H
    glTexCoord2f(.89/scale, 2.70/scale); glVertex3f(.89/scale, 2.70/scale, .22/scale); //G
    glTexCoord2f(.89/scale, 2.70/scale); glVertex3f(.89/scale, 2.70/scale, -.22/scale); //G

    subtract3f(G, GB, temp1);
    subtract3f(GB, F, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(.89/scale, 2.70/scale); glVertex3f(.89/scale, 2.70/scale, .22/scale); //G
    glTexCoord2f(.89/scale, 2.70/scale); glVertex3f(.89/scale, 2.70/scale, -.22/scale); //G
    glTexCoord2f(.05/scale, 3.84/scale); glVertex3f(.05/scale, 3.84/scale, -.19/scale); //F
    glTexCoord2f(.05/scale, 3.84/scale); glVertex3f(.05/scale, 3.84/scale, .19/scale); //F

    subtract3f(F, FB, temp1);
    subtract3f(FB, E, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(.05/scale, 3.84/scale); glVertex3f(.05/scale, 3.84/scale, -.19/scale); //F
    glTexCoord2f(.05/scale, 3.84/scale); glVertex3f(.05/scale, 3.84/scale, .19/scale); //F
    glTexCoord2f(.83/scale, 3.99/scale); glVertex3f(.83/scale, 3.99/scale, .18/scale); //E
    glTexCoord2f(.83/scale, 3.99/scale); glVertex3f(.83/scale, 3.99/scale, -.18/scale); //E

    subtract3f(W, Q, temp1);
    subtract3f(Q, P, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(.83/scale, 3.99/scale); glVertex3f(.83/scale, 3.99/scale, .18/scale); //E
    glTexCoord2f(.83/scale, 3.99/scale); glVertex3f(.83/scale, 3.99/scale, -.18/scale); //E
    glTexCoord2f(.78/scale, 4.13/scale); glVertex3f(.78/scale, 4.13/scale, -.16/scale); //D
    glTexCoord2f(.78/scale, 4.13/scale); glVertex3f(.78/scale, 4.13/scale, .16/scale); //D

    subtract3f(D, DB, temp1);
    subtract3f(DB, C, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(.78/scale, 4.13/scale); glVertex3f(.78/scale, 4.13/scale, .16/scale); //D
    glTexCoord2f(.78/scale, 4.13/scale); glVertex3f(.78/scale, 4.13/scale, -.16/scale); //D
    glTexCoord2f(.86/scale, 4.48/scale); glVertex3f(.86/scale, 4.48/scale, -.12/scale); //C
    glTexCoord2f(.86/scale, 4.48/scale); glVertex3f(.86/scale, 4.48/scale, .12/scale); //C

    subtract3f(C, CB, temp1);
    subtract3f(CB, E1, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(.86/scale, 4.48/scale); glVertex3f(.86/scale, 4.48/scale, -.12/scale); //C
    glTexCoord2f(.86/scale, 4.48/scale); glVertex3f(.86/scale, 4.48/scale, .12/scale); //C
    glTexCoord2f(.24/scale, 4.86/scale); glVertex3f(.24/scale, 4.86/scale, .05/scale); //E1
    glTexCoord2f(.24/scale, 4.86/scale); glVertex3f(.24/scale, 4.86/scale, -.05/scale); //E1

    subtract3f(E1, E1B, temp1);
    subtract3f(E1B, B, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(.24/scale, 4.86/scale); glVertex3f(.24/scale, 4.86/scale, .05/scale); //E1
    glTexCoord2f(.24/scale, 4.86/scale); glVertex3f(.24/scale, 4.86/scale, -.05/scale); //E1
    glTexCoord2f(0, 5.12/scale); glVertex3f(0, 5.12/scale, -.19/scale); //B
    glTexCoord2f(0, 5.12/scale); glVertex3f(0, 5.12/scale, .19/scale); //B

    subtract3f(B, A2, temp1);
    subtract3f(A2, BB, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(0, 5.12/scale); glVertex3f(0, 5.12/scale, -.19/scale); //B
    glTexCoord2f(0, 5.12/scale); glVertex3f(0, 5.12/scale, .19/scale); //B
    glTexCoord2f(-.19/scale, 5.12/scale); glVertex3f(-.19/scale, 5.12/scale, .19/scale); //A2
    glTexCoord2f(-.19/scale, 5.12/scale); glVertex3f(-.19/scale, 5.12/scale, -.19/scale); //A2
    glEnd();
    //Eye Depressions
    glBegin(GL_POLYGON);
    subtract3f(A2, B, temp1);
    subtract3f(B, E1, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(-.19/scale, 5.12/scale); glVertex3f(-.19/scale, 5.12/scale, .19/scale); //A2
    glTexCoord2f(0, 5.12/scale); glVertex3f(0, 5.12/scale, .19/scale); //B
    glTexCoord2f(.24/scale, 4.86/scale); glVertex3f(.24/scale, 4.86/scale, .05/scale); //E1
    glTexCoord2f(.86/scale, 4.48/scale); glVertex3f(.86/scale, 4.48/scale, .12/scale); //C
    glTexCoord2f(.40/scale, 4.57/scale); glVertex3f(.40/scale, 4.57/scale, .19/scale); //Z
    glTexCoord2f(.05/scale, 4.75/scale); glVertex3f(.05/scale, 4.75/scale, .19/scale); //Y
    glEnd();
    glBegin(GL_POLYGON);
    subtract3f(A2B, BB, temp1);
    subtract3f(BB, E1B, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(-.19/scale, 5.12/scale); glVertex3f(-.19/scale, 5.12/scale, -.19/scale); //A2
    glTexCoord2f(0, 5.12/scale); glVertex3f(0, 5.12/scale, -.19/scale); //B
    glTexCoord2f(.24/scale, 4.86/scale); glVertex3f(.24/scale, 4.86/scale, -.05/scale); //E1
    glTexCoord2f(.86/scale, 4.48/scale); glVertex3f(.86/scale, 4.48/scale, -.12/scale); //C
    glTexCoord2f(.40/scale, 4.57/scale); glVertex3f(.40/scale, 4.57/scale, -.19/scale); //Z
    glTexCoord2f(.05/scale, 4.75/scale); glVertex3f(.05/scale, 4.75/scale, -.19/scale); //Y
    glEnd();
    //Ears
    glBegin(GL_TRIANGLES);
    float A3[3] = {-.19, 5.12, 0};
    float A4[3] = {-.48, 4.86, 0};

    subtract3f(A, A2, temp1);
    subtract3f(A2, A3, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(-.4/scale, 5.47/scale); glVertex3f(-.4/scale, 5.47/scale, .31/scale); //A
    glTexCoord2f(-.19/scale, 5.12/scale); glVertex3f(-.19/scale, 5.12/scale, .19/scale); //A2
    glTexCoord2f(-.19/scale, 5.12/scale); glVertex3f(-.19/scale, 5.12/scale, 0); //A3

    subtract3f(A, A3, temp1);
    subtract3f(A3, A4, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(-.4/scale, 5.47/scale); glVertex3f(-.4/scale, 5.47/scale, .31/scale); //A
    glTexCoord2f(-.19/scale, 5.12/scale); glVertex3f(-.19/scale, 5.12/scale, 0); //A3
    glTexCoord2f(-.48/scale, 4.86/scale); glVertex3f(-.48/scale, 4.86/scale, 0); //A4

    subtract3f(A, A4, temp1);
    subtract3f(A4, T, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(-.4/scale, 5.47/scale); glVertex3f(-.4/scale, 5.47/scale, .31/scale); //A
    glTexCoord2f(-.48/scale, 4.86/scale); glVertex3f(-.48/scale, 4.86/scale, 0); //A4
    glTexCoord2f(-.48/scale, 4.86/scale); glVertex3f(-.48/scale, 4.86/scale, .28/scale); //T

    subtract3f(AB, A2B, temp1);
    subtract3f(A2B, A3, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(-.4/scale, 5.47/scale); glVertex3f(-.4/scale, 5.47/scale, -.31/scale); //A
    glTexCoord2f(-.19/scale, 5.12/scale); glVertex3f(-.19/scale, 5.12/scale, -.19/scale); //A2
    glTexCoord2f(-.19/scale, 5.12/scale); glVertex3f(-.19/scale, 5.12/scale, 0); //A3

    subtract3f(AB, A3, temp1);
    subtract3f(A3, A4, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(-.4/scale, 5.47/scale); glVertex3f(-.4/scale, 5.47/scale, -.31/scale); //A
    glTexCoord2f(-.19/scale, 5.12/scale); glVertex3f(-.19/scale, 5.12/scale, 0); //A3
    glTexCoord2f(-.48/scale, 4.86/scale); glVertex3f(-.48/scale, 4.86/scale, 0); //A4

    subtract3f(AB, A4, temp1);
    subtract3f(A4, TB, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(-.4/scale, 5.47/scale); glVertex3f(-.4/scale, 5.47/scale, -.31/scale); //A
    glTexCoord2f(-.48/scale, 4.86/scale); glVertex3f(-.48/scale, 4.86/scale, 0); //A4
    glTexCoord2f(-.48/scale, 4.86/scale); glVertex3f(-.48/scale, 4.86/scale, -.28/scale); //T
    glEnd();
    //Back of horse
    glBegin(GL_QUADS);
    subtract3f(TB, T, temp1);
    subtract3f(T, S, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(-.48/scale, 4.86/scale); glVertex3f(-.48/scale, 4.86/scale, -.28/scale); //T
    glTexCoord2f(-.48/scale, 4.86/scale); glVertex3f(-.48/scale, 4.86/scale, .28/scale); //T
    glTexCoord2f(-.92/scale, 4.22/scale); glVertex3f(-.92/scale, 4.22/scale, .09/scale); //S
    glTexCoord2f(-.92/scale, 4.22/scale); glVertex3f(-.92/scale, 4.22/scale, -.09/scale); //S

    subtract3f(S, SB, temp1);
    subtract3f(SB, RB, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(-.92/scale, 4.22/scale); glVertex3f(-.92/scale, 4.22/scale, .09/scale); //S
    glTexCoord2f(-.92/scale, 4.22/scale); glVertex3f(-.92/scale, 4.22/scale, -.09/scale); //S
    glTexCoord2f(-1.12/scale, 3.51/scale); glVertex3f(-1.12/scale, 3.51/scale, -.05/scale); //R
    glTexCoord2f(-1.12/scale, 3.51/scale); glVertex3f(-1.12/scale, 3.51/scale, .05/scale); //R

    subtract3f(R, RB, temp1);
    subtract3f(RB, QB, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(-1.12/scale, 3.51/scale); glVertex3f(-1.12/scale, 3.51/scale, .05/scale); //R
    glTexCoord2f(-1.12/scale, 3.51/scale); glVertex3f(-1.12/scale, 3.51/scale, -.05/scale); //R
    glTexCoord2f(-1.06/scale, 2.85/scale); glVertex3f(-1.06/scale, 2.85/scale, -.10/scale); //Q
    glTexCoord2f(-1.06/scale, 2.85/scale); glVertex3f(-1.06/scale, 2.85/scale, .10/scale); //Q

    subtract3f(QB, Q, temp1);
    subtract3f(QB, P, temp2);
    crossproduct3f(temp1, temp2, temp3);
    rescalenormals(temp3);
    glNormal3fv(temp3);
    glTexCoord2f(-1.06/scale, 2.85/scale); glVertex3f(-1.06/scale, 2.85/scale, -.10/scale); //Q
    glTexCoord2f(-1.06/scale, 2.85/scale); glVertex3f(-1.06/scale, 2.85/scale, .10/scale); //Q
    glTexCoord2f(-.75/scale, 1.91/scale); glVertex3f(-.75/scale, 1.91/scale, .2/scale); //P
    glTexCoord2f(-.75/scale, 1.91/scale); glVertex3f(-.75/scale, 1.91/scale, -.2/scale); //P
    glEnd();
    glPopMatrix();

    //Cylinders
    GLUquadricObj* object;
    object = gluNewQuadric();
    gluQuadricDrawStyle(object, GLU_FILL);
    gluQuadricNormals(object, GL_SMOOTH);
    gluQuadricTexture(object, GL_TRUE);
    //H-I Disk
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 1.99/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluDisk(object, 0, .85/scale, 10, 10);
    glPopMatrix();
    //I-J
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 1.68/scale,(y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, 1.09/scale, .85/scale, .31/scale, 10, 10);
    glPopMatrix();
    //J-K
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 1.45/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, 1.02/scale, 1.09/scale, .23/scale, 10, 10);
    glPopMatrix();
    //K-L
    glPushMatrix();
    glTranslatef((x+.5)/4.0, .93/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, 1.49/scale, 1.02/scale, .52/scale, 15, 15);
    glPopMatrix();
    //L-M
    glPushMatrix();
    glTranslatef((x+.5)/4.0, .52/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, 1.39/scale, 1.49/scale, .41/scale, 15, 10);
    glPopMatrix();
    //M-N
    glPushMatrix();
    glTranslatef((x+.5)/4.0, .36/scale, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, 1.52/scale, 1.39/scale, .16/scale, 10, 10);
    glPopMatrix();
    //N-0
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 0, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluCylinder(object, 1.52/scale, 1.52/scale, .36/scale, 15, 10);
    glPopMatrix();
    //Bottom Disk
    glPushMatrix();
    glTranslatef((x+.5)/4.0, 0, (y+.5)/4.0);
    glRotatef(90, -1, 0, 0);
    gluDisk(object, 0, 1.52/scale, 15, 10);
    glPopMatrix();

    //Eyes - last because the color changes.
    //Change this so that it is white instead of gray
    float mat_gray[] = {.5, .5, .5, 1.0};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_gray);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_gray);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_gray);
    glColor3f(0.5f, 0.5f, 0.5f);
    glPushMatrix();
    glTranslatef((x+.5)/4.0+.24/scale, 4.82/scale, (y+.5+1.09/scale)/4.0);
    gluSphere(object, .04/4.0, 10, 10);
    glPopMatrix();
    glPushMatrix();
    glTranslatef((x+.5)/4.0+.24/scale, 4.82/scale, (y+.5-1.09/scale)/4.0);
    gluSphere(object, .04/4.0, 10, 10);
    glPopMatrix();

    gluDeleteQuadric(object);}

void Space::drawBishopEnhanced()
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

void Space::drawQueenEnhanced()
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

void Space::drawKingEnhanced()
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
    // Set material properties
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    // Set color based on team
    if(team)
    {
        glColor3f(lightTeamColor[0], lightTeamColor[1], lightTeamColor[2]); // set drawing color to white
    }
    else
    {
        glColor3f(darkTeamColor[0], darkTeamColor[1], darkTeamColor[2]); // set drawing color to white
    }
}