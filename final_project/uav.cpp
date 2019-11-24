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
#include <random>

// Determine piece material properties
GLfloat mat_specular[] = {0.5, 0.5, 0.5, 1.0};
GLfloat shininess[] = {50.0};
unsigned char uavColor[] = {255,0,0};

// Define constexpr
constexpr double UAV::mass; //kg
constexpr double UAV::kSpring;
constexpr double UAV::timeStep;
constexpr double UAV::maxForce;
constexpr double UAV::gravity;


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

    // The initialize approach to the sphere has a difference force law
    if (initApproach)
    {
        // The velocity should be limited on the approach to the sphere to prevent
        //  mass velocity that makes slowing down the UAV take a long time
        if(velMag() < 2)
        {
            force =  -kSpring*(10 - distanceFromCenterOfSphere());
        }
        else
        {
            force = 0;
        }
        // Condition to break out of the initial approach
        if(distance < 11)
        {
            initApproach = false;
        }
    }
    else
    {
        force =  -kSpring*(10 - distanceFromCenterOfSphere());
        // To prevent unstable oscillations, if the uav is not trying to slow down,
        // Then limit the force to prevent "slamming on the accelerator"
        // The slowing down for should simulate slamming on the brakes and thus is not reduced.
        // This stabilizes the uav towards the equilibrium based on Hooke's law
        if(!slowingDown)
        {
            force *=.8;
        }
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

Coordinate UAV::getOrthogonalVector(Coordinate vec)
{

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(1, 5); // define the range
    double x = distr(eng);
    double y = distr(eng);
    double z = distr(eng);
    Coordinate newVec;

    if(vec.x != 0)
    {
        newVec = {(-y*vec.y - z*vec.z)/vec.x, y, z};
    }
    else if (vec.y != 0)
    {
        newVec = {(-x*vec.x - z*vec.z)/vec.y, y, z};
    }
    else if (vec.z != 0)
    {
        newVec = {(-x*vec.x - y*vec.y)/vec.z, y, z};
    }
    else
    {
        newVec = {1,1,1};
    }
    double mag =  sqrt(pow(newVec.x, 2) + pow(newVec.y, 2) + pow(newVec.z,2));
    return (1/mag)*newVec;
}

Coordinate UAV::getForce()
{
    // Get the force magnitude
    // To compensate for gravity we always limit the magnitude to 10 (since the max is 20)
    //   then we will assume the uav is always firing the extra 10N to counter the effect of gravity
    double mag = calculateForceMag();

    // Limit the force of the UAV motors to +=10 so that the extra 10 newton are always
    //  being used to counter the effets of gravity
    if(mag > 8)
    {
        mag = 8;
    }
    else if (mag < -8)
    {
        mag = -8;
    }

    // calculate the force of the desired direction
    Coordinate unitVec = calculateForceUnitVec();
    Coordinate force = mag*unitVec;

    if(!initApproach)
    {

        if(velMag() < 5)
        {
            double leftOverForce = 2;
            Coordinate ortho = getOrthogonalVector(unitVec);
            force.x += leftOverForce*ortho.x;
            force.y += leftOverForce*ortho.y;
            force.z += leftOverForce*ortho.z;
        }

    }
    // The two statements below counter each other but left to display what it is doing
    // Add the effect of gravity
    force.z -= gravity;

    // With the extra 10 Newtons (reserved), apply the force in the z direction to counter the
    //  effect of gravity
    force.z += gravity;

    // Return the new force vector
    return force;
}

void UAV::evolveSystem()
{
    Coordinate force = getForce();

    // Equations of motion for the new position
    location.x = location.x + velocity.x*timeStep + .5*force.x/mass*pow(timeStep,2);
    location.y = location.y + velocity.y*timeStep + .5*force.y/mass*pow(timeStep,2);
    location.z = location.z + velocity.z*timeStep + .5*force.z/mass*pow(timeStep,2);

    double beforeMag = velMag();
    // Equations of motion for the velocity
    velocity.x = velocity.x + force.x/mass*timeStep;
    velocity.y = velocity.y + force.y/mass*timeStep;
    velocity.z = velocity.z + force.z/mass*timeStep;
    double afterMag = velMag();

    // Determines if the UAV is slowing down or speeding up
    // Used in the force calculation to reduce the oscillations
    slowingDown = afterMag < beforeMag;
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
