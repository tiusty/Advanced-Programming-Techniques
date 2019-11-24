/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 11/22/2019
Description: 
*/

#include "footballField.h"
#include <GL/glut.h>
#include <cmath>

// Define constexpr variables
constexpr float FootballField::lenFootballField;
constexpr float FootballField::widthFootballField;
constexpr unsigned int FootballField::numUAVs;

FootballField::FootballField()
{
    origin.x = widthFootballField/2;
    origin.y = lenFootballField/2;
    origin.z = 0;
    initializeUAVs();
}

double FootballField::distanceBetweenUavs(const UAV &uav1, const UAV &uav2) const
{
    return sqrt(
            pow(uav2.location.x - uav1.location.x, 2) +
            pow(uav2.location.y - uav1.location.y, 2) +
            pow(uav2.location.z - uav1.location.z, 2));
}

void FootballField::checkCollisions()
{
    for(int i=0; i<uavs.size(); i++)
    {
        for(int j=i; j < uavs.size(); j++)
        {
            // If another UAV comes within .01 of it then swap velocity vectors
            if(distanceBetweenUavs(uavs.at(i), uavs.at(j)) < .51)
            {
                Coordinate vel1 = uavs.at(i).velocity;
                uavs.at(i).velocity = uavs.at(j).velocity;
                uavs.at(j).velocity = vel1;
            }
        }
    }
}

Coordinate FootballField::sphereLocation()
{
    return Coordinate{origin.x, origin.y, origin.z + 50};
}

void FootballField::drawSphere()
{
    Coordinate sphereLoc = sphereLocation();
    glPushMatrix();
        glColor3f(1.0,1.0,0.0);
        glTranslatef(sphereLoc.x, sphereLoc.y, sphereLoc.z);
        glutWireSphere(10, 10,20);
    glPopMatrix();
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
        uav.setCenter(sphereLocation());
        uav.location.y = yardToMeter(25*column);
        uav.location.x = (counter%3)*widthFootballField/2;
        counter++;
        if (counter %3 == 0)
        {
            column++;
        }
    }

}

void FootballField::drawUAVS(unsigned int timeStep)
{
    for(const auto &uav : uavs)
    {
        uav.drawUAV(timeStep);
    }
}

bool FootballField::checkAllUavsAtSphere()
{
    bool status{true};
    for (const auto &uav : uavs)
    {
        status = status and !uav.initApproach;
    }

    return status;
}
