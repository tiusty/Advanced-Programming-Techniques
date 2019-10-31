/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 10/29/19
Description: 
*/
#include <iostream>
#include <cmath>
#include <fstream>

#include "ship.hpp"
#include "world.hpp"


void handleYellowJacket();
double calculateForce(double dist3D, double currPos, double targetPos, double currVel, double targetVel);
double calculateYellowJacketForce(double fullDist, double currPos, double currVel, double targetVel, double targetPos, double targetVelUnitVec, double targetDistUnitVec);
bool checkConditions(Ship &yellowJacket,Ship &buzzy);
void evolveSystem(Ship& currShip);
Ship yellowJacket{};
Ship buzzy{};

int main()
{
    World world;
    // Determine stating positions

    // On Buzzy just calculate new position
    buzzy.position = {1000,500,0};
    buzzy.velocity = {300,-10,0};

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

void initializeShips()
{
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
    yellowJacket.force.x = calculateForce(yellowJacket.getFullDistance(buzzy.position), yellowJacket.position.x, buzzy.position.x, yellowJacket.velocity.x, buzzy.velocity.x);
    yellowJacket.force.y = calculateForce(yellowJacket.getFullDistance(buzzy.position), yellowJacket.position.y, buzzy.position.y, yellowJacket.velocity.y, buzzy.velocity.y);
    yellowJacket.force.z = calculateForce(yellowJacket.getFullDistance(buzzy.position), yellowJacket.position.z, buzzy.position.z, yellowJacket.velocity.z, buzzy.velocity.z);

    evolveSystem(yellowJacket);
}

double calculateForce(double dist3D, double currPos, double targetPos, double currVel, double targetVel)
{
    double force{0};
    if (dist3D > 1000)
    {
        if (std::abs(currPos - targetPos) > 1000)
        {
            // Accelerate to the targetVel + 75 as quickly as possible
            force = yellowJacket.getForce(yellowJacket.forceToGetVel(currVel, targetVel + 75));
        }
        else
        {
            // Maintain velocity but make minor adjustments
            force = yellowJacket.getForce(yellowJacket.forceToGetVel(currVel, targetVel) + (targetPos - currPos)*.0003*yellowJacket.maxForce);
        }
    }
    else
    {
        // Maintain velocity but make minor adjustments
        force = yellowJacket.getForce(yellowJacket.forceToGetVel(currVel, targetVel) + (targetPos - currPos)*.0003*yellowJacket.maxForce);
    }

    return force;
}
