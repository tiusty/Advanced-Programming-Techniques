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
constexpr unsigned int FootballField::numUAVs;

FootballField::FootballField()
{
    initializeUAVs();
    origin.x = lenFootballField/2;
    origin.y = widthFootballField/2;
    origin.z = 0;
}

void FootballField::drawField()
{
    // To make calculations easier. Yard 0 on the field starts at 0 and ends at 100 yards.
    // Then the vertex is drawn an extra 10 yards on each side, i.e -10 to 110 yards to
    //  draw the end zone.
    glPushMatrix();
        glColor3f(0.0, 1.0, 0.0); // set drawing color to white
        glBegin(GL_QUADS);
        glVertex3f(0, 0-yardToMeter(10), 0.0);
        glVertex3f(0, lenFootballField+yardToMeter(10), 0.0);
        glVertex3f(widthFootballField, lenFootballField+yardToMeter(10), 0.0);
        glVertex3f(widthFootballField, 0-yardToMeter(10), 0.0);
        glEnd();
    glPopMatrix();
}

void FootballField::initializeUAVs()
{
    unsigned int counter = 0;
    unsigned int column = 0;
    for(auto &uav : uavs)
    {
        uav.location.y = yardToMeter(25*column);
        uav.location.x = (counter%3)*widthFootballField/2;
        counter++;
        if (counter %3 == 0)
        {
            column++;
        }
    }

}

void FootballField::drawUAVS()
{
    for(const auto &uav : uavs)
    {
        uav.drawUAV();
    }
}
