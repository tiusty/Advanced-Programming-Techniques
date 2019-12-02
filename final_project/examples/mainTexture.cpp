/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 11/24/2019
Description: 
*/

//#include <windows.h> //for Code::Blocks user

#include <GL/glut.h>

#include <stdio.h>

#include <GL/glut.h>

#include <stdlib.h>

#include "ECE_Bitmap.h"


GLuint texture[2];

float x_angle = 0;
float y_angle = 0;
float z_angle = 0;

struct Image {

    unsigned long sizeX;

    unsigned long sizeY;

    char *data;

};

typedef struct Image Image;

BMP inBitmap;


#define checkImageWidth 64

#define checkImageHeight 64


GLubyte checkImage[checkImageWidth][checkImageHeight][3];

void makeCheckImage(void) {

    int i, j, c;

    for (i = 0; i < checkImageWidth; i++) {

        for (j = 0; j < checkImageHeight; j++) {

            c = ((((i & 0x8) == 0) ^ ((j & 0x8) == 0))) * 255;

            checkImage[i][j][0] = (GLubyte)c;

            checkImage[i][j][1] = (GLubyte)c;

            checkImage[i][j][2] = (GLubyte)c;

        }

    }

}

void myinit(void)

{

    glClearColor(0.5, 0.5, 0.5, 0.0);

    glEnable(GL_DEPTH_TEST);

//    glCullFace(GL_BACK);
//    glEnable(GL_CULL_FACE);

    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    inBitmap.read("WinterIsland.bmp");

    makeCheckImage();

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Create Textures

    glGenTextures(2, texture);

    // Setup first texture
    glBindTexture(GL_TEXTURE_2D, texture[0]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //scale linearly when image bigger than texture

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //scale linearly when image smalled than texture


    glTexImage2D(GL_TEXTURE_2D, 0, 3, inBitmap.bmp_info_header.width, inBitmap.bmp_info_header.height, 0,
                 GL_BGR_EXT, GL_UNSIGNED_BYTE, &inBitmap.data[0]);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    // Do the second texture

    glBindTexture(GL_TEXTURE_2D, texture[1]);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth, checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, &checkImage[0][0][0]);

    glEnable(GL_TEXTURE_2D);

}



void display(void) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glPushMatrix();

    glRotatef(x_angle, 1.0, 0.0, 0.0);
    glRotatef(y_angle, 0.0, 1.0, 0.0);
    glRotatef(z_angle, 0.0, 0.0, 1.0);


    glBindTexture(GL_TEXTURE_2D, texture[1]);

    glutSolidTeapot(0.25);

    glBindTexture(GL_TEXTURE_2D, texture[0]);

    glBegin(GL_QUADS);
    glTexCoord2f(1, 1);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glTexCoord2f(0, 1);
    glVertex3f(-1.0f, 1.0f, 0.0f);
    glTexCoord2f(0, 0);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glTexCoord2f(1, 0);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();

    glPopMatrix();

    glutSwapBuffers();

}


void myReshape(int w, int h) {

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluPerspective(60.0, 1.0*(GLfloat)w / (GLfloat)h, 1.0, 30.0);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    glTranslatef(0.0, 0.0, -3.6);

}


void keyboard(unsigned char key, int x, int y) {

    switch (key) {

        case 'x':
            x_angle = ((int)x_angle+10)%360;
            glutPostRedisplay();
            break;
        case 'y':
            y_angle = ((int)y_angle + 10) % 360;
            glutPostRedisplay();
            break;
        case 'z':
            z_angle = ((int)z_angle + 10) % 360;
            glutPostRedisplay();
            break;
        case 27: // �esc� on keyboard

            exit(0);

            break;

        default: // �a� on keyboard

            break;

    }

}


int main(int argc, char** argv)

{

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutCreateWindow("Texture Mapping - Programming Techniques");

    myinit();

    glutReshapeFunc(myReshape);

    glutDisplayFunc(display);

    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;

}