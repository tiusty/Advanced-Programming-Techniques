/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 10/29/19
Description: 
*/
#include <iostream>
#include <cmath>

#include "ship.hpp"


void handleYellowJacket();
double calculateYellowJacketForce(double fullDist, double currPos, double currVel, double targetVel, double targetPos, double targetVelUnitVec);
bool checkConditions(Ship &yellowJacket,Ship &buzzy);
void evolveSystem(Ship& currShip);
Ship yellowJacket{};
Ship buzzy{};

int main()
{
    std::cout << "Hello World" << std::endl;

    // Read in files

    // Determine stating positions

    // On Buzzy just calculate new position
    buzzy.position = {1000,600,70};
    buzzy.velocity = {300,100,0};

    for(int i=0; i< 5000; i++)
    {
        evolveSystem(buzzy);
        handleYellowJacket();
        if(checkConditions(yellowJacket, buzzy))
        {
            break;
        }
    }

    return 1;
}

bool checkConditions(Ship &yellowJacket,Ship &buzzy)
{
    if(yellowJacket.getFullDistance(buzzy.position) < 50)
    {
        if(yellowJacket.getMagVel() < 1.1*buzzy.getMagVel())
        {
            double dotProduct = yellowJacket.velocity.x*buzzy.velocity.x + yellowJacket.velocity.y*buzzy.velocity.y+yellowJacket.velocity.z*buzzy.velocity.z;
            if(dotProduct/(yellowJacket.getMagVel()*buzzy.getMagVel()) > .8)
            {
                yellowJacket.status = 2;
            }
            else
            {
                yellowJacket.status = 0;
            }
        }
        else
        {
            yellowJacket.status = 0;
        }
        return true;
    }

    return false;
}


void evolveSystem(Ship& currShip)
{
    currShip.position.x = currShip.position.x + currShip.velocity.x + (currShip.force.x/yellowJacketMass)/2;
    currShip.position.y = currShip.position.y + currShip.velocity.y + (currShip.force.y/yellowJacketMass)/2;
    currShip.position.z = currShip.position.z + currShip.velocity.z + (currShip.force.z/yellowJacketMass)/2;

    currShip.velocity.x = currShip.velocity.x + currShip.force.x/yellowJacketMass;
    currShip.velocity.y = currShip.velocity.y + currShip.force.y/yellowJacketMass;
    currShip.velocity.z = currShip.velocity.z + currShip.force.z/yellowJacketMass;
}

void handleYellowJacket()
{
    yellowJacket.force.x = calculateYellowJacketForce(yellowJacket.getFullDistance(buzzy.position), yellowJacket.position.x, yellowJacket.velocity.x,
                                                      buzzy.velocity.x,
                                                      buzzy.position.x, buzzy.getVelUnitVec().x);
    yellowJacket.force.y = calculateYellowJacketForce(yellowJacket.getFullDistance(buzzy.position), yellowJacket.position.y, yellowJacket.velocity.y,
                                                      buzzy.velocity.y,
                                                      buzzy.position.y, buzzy.getVelUnitVec().y);
    yellowJacket.force.z = calculateYellowJacketForce(yellowJacket.getFullDistance(buzzy.position), yellowJacket.position.z, yellowJacket.velocity.z,
                                                      buzzy.velocity.z,
                                                      buzzy.position.z, buzzy.getVelUnitVec().z);

    evolveSystem(yellowJacket);
}

double calculateYellowJacketForce(double fullDist, double currPos, double currVel, double targetVel, double targetPos, double targetVelUnitVec)
{
    double force{0};
    double timeDif{0};
    double timeToDest = yellowJacket.timeToDest(currPos, targetPos, currVel - targetVel);
    double timeToVel = yellowJacket.timeToGetToVel(currVel, targetVel);
    if(timeToVel > 0)
    {
        timeDif = timeToDest/timeToVel;
    }

    // When close, line up

    // Force the docking speed when close to the target
    if(fullDist < 100)
    {

        force = yellowJacket.forceToGetVel(currVel, 1.05 * targetVel * targetVelUnitVec);
    }
    // If the ship is far enough away then accelerate at full force
    else if(timeDif > 2)
    {
        force = yellowJacket.getForce(yellowJacket.maxForce);
    }
    // If the ship is getting close then force it to slow down to a resonable speed
    else
    {
        if(std::abs(currPos - targetPos) > 10 && timeDif == 0)
        {
            force = yellowJacket.maxForce*.1;
        }
        else
        {
            force = yellowJacket.forceToGetVel(currVel, .99*targetVel * targetVelUnitVec);
        }
    }

    return force;
}

