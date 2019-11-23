/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 11/22/2019
Description:
 Implements the uav class
*/

#include "uav.h"
#include <GL/glut.h>
#include <cmath>
#include <iostream>

// Determine piece material properties
GLfloat mat_specular[] = {0.5, 0.5, 0.5, 1.0};
GLfloat shininess[] = {50.0};
unsigned char uavColor[] = {255,0,0};

// Define constexpr
constexpr double UAV::mass; //kg
constexpr double UAV::kSpring;
constexpr double UAV::timeStep;
constexpr double UAV::maxForce;


// Overloads the multiplcation operator so a Coordiante can be multiplied by a scalar to represent
// a unit vector being multiplied by the magnitude
Coordinate operator* (double scalar, const Coordinate& coord)
{
    return Coordinate{coord.x * scalar, coord.y * scalar, coord.z*scalar};
}

Coordinate operator* (const Coordinate& y, double scalar)
{
    return scalar*y;
}

void UAV::setCenter(Coordinate center)
{
    sphereCenter = center;
}

double UAV::velMag()
{
    return sqrt(pow(velocity.x, 2) + pow(velocity.y, 2) + pow(velocity.z,2));
}

double UAV::distanceFromCenterOfSphere()
{
    return sqrt(pow(sphereCenter.x - location.x,2) + pow(sphereCenter.y - location.y, 2) + pow(sphereCenter.z - location.z,2));
}

Coordinate UAV::calculateForceUnitVec()
{
    double distance = distanceFromCenterOfSphere();
    return Coordinate{(sphereCenter.x - location.x)/distance, (sphereCenter.y - location.y)/distance, (sphereCenter.z - location.z)/distance};
}

double UAV::calculateForceMag()
{
    double distance = distanceFromCenterOfSphere();
    double force{0};

    if (initApproach)
    {
        if(velMag() < 2)
        {
            force =  -kSpring*(10 - distanceFromCenterOfSphere());
        }
        else
        {
            force = 0;
        }
        if(distance < 12)
        {
            initApproach = false;
        }
    }
    else
    {
        force =  -kSpring*(10 - distanceFromCenterOfSphere());
    }

    if (force > maxForce)
    {
        return maxForce;
    }
    else if (force < -maxForce)
    {
        return -maxForce;
    }
    else
    {
        return force;
    }
}

void UAV::evolveSystem()
{
    Coordinate force = calculateForceMag()*calculateForceUnitVec();
    location.x = location.x + velocity.x*timeStep + .5*force.x/mass*pow(timeStep,2);
    location.y = location.y + velocity.y*timeStep + .5*force.y/mass*pow(timeStep,2);
    location.z = location.z + velocity.z*timeStep + .5*force.z/mass*pow(timeStep,2);

    velocity.x = velocity.x + force.x/mass*timeStep;
    velocity.y = velocity.y + force.y/mass*timeStep;
    velocity.z = velocity.z + force.z/mass*timeStep;
    std::cout << "velocity x:" << velocity.x << ", velocity y: " << velocity.y << ", velocity z: " << velocity.z << std::endl;
}

void UAV::drawUAV() const
{
    // Draws the UAV which we are representing as a solid red sphere
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
