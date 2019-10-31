/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 10/31/19
Description: 
*/

#include <fstream>
#include <iostream>
#include "world.hpp"

World::World()
{
    std::ifstream file("in.dat");

    if(!file)
    {
        std::cerr << "Cannot open file" << std::endl;
        exit(1);
    }

    std::string line;

    // Read in the row and column number
    file >> duration;
    file >> maxForce;

    double shipSpeed{0};
    double xVec{0};
    double yVec{0};
    double zVec{0};

    file >> buzzy.position.x >> buzzy.position.y >> buzzy.position.z >> shipSpeed >> xVec >> yVec >> zVec;
    buzzy.velocity.x = shipSpeed * xVec;
    buzzy.velocity.y = shipSpeed * yVec;
    buzzy.velocity.z = shipSpeed * zVec;
    buzzy.maxForce = maxForce;

    int counter{0};
    for(auto & ship : fighters)
    {
        file >> ship.position.x >> ship.position.y >> ship.position.z >> shipSpeed >> xVec >> yVec >> zVec;
        ship.velocity.x = shipSpeed * xVec;
        ship.velocity.y = shipSpeed * yVec;
        ship.velocity.z = shipSpeed * zVec;
        ship.maxForce = maxForce;
        ship.id = counter;
        counter++;
    }
}

double World::setForce(double force)
{
    double newForce = force;
    if(force > maxForce)
    {
        newForce = maxForce;
    }
    else if(force < -maxForce)
    {
        newForce = -maxForce;
    }

    return newForce;

}

void World::handleYellowJacket(Ship &yellowJacket, int currDuration)
{
    // Stagger the fighters from moving so that the one with the highest rank approaches buzzy first
    if(currDuration > rankOfFighter(yellowJacket)*200)
    {
        yellowJacket.force.x = calculateForce(yellowJacket, yellowJacket.getFullDistance(buzzy.position), yellowJacket.position.x, buzzy.position.x, yellowJacket.velocity.x, buzzy.velocity.x);
        yellowJacket.force.y = calculateForce(yellowJacket, yellowJacket.getFullDistance(buzzy.position), yellowJacket.position.y, buzzy.position.y, yellowJacket.velocity.y, buzzy.velocity.y);
        yellowJacket.force.z = calculateForce(yellowJacket, yellowJacket.getFullDistance(buzzy.position), yellowJacket.position.z, buzzy.position.z, yellowJacket.velocity.z, buzzy.velocity.z);
    }
}

double World::calculateForce(Ship ship, double dist3D, double currPos, double targetPos, double currVel, double targetVel)
{
    double force{0};
    if (dist3D > 1000)
    {
        if (std::abs(currPos - targetPos) > 1000)
        {
            // Accelerate to the targetVel + 75 as quickly as possible
            force = setForce(ship.forceToGetVel(currVel, targetVel + 75));
        }
        else
        {
            // Maintain velocity but make minor adjustments
            force = setForce(ship.forceToGetVel(currVel, targetVel) + (targetPos - currPos)*.0003*maxForce);
        }
    }
    else
    {
        // Maintain velocity but make minor adjustments
        force = setForce(ship.forceToGetVel(currVel, targetVel) + (targetPos - currPos)*.0003*maxForce);
    }

    return force;
}

void World::checkConditions(Ship &yellowJacket)
{
    if(yellowJacket.status == 1)
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
        }

        // Check to see if any fighters crashed
        for(auto &ship : fighters)
        {
            double distance = yellowJacket.getFullDistance(ship.position);
            if(distance < 250 && yellowJacket.id != ship.id)
            {
                yellowJacket.status = 0;
                ship.status=0;
            }
        }

    }
}

void World::evolveSystem(Ship& currShip)
{
    currShip.position.x = currShip.position.x + currShip.velocity.x + (currShip.force.x/yellowJacketMass)/2;
    currShip.position.y = currShip.position.y + currShip.velocity.y + (currShip.force.y/yellowJacketMass)/2;
    currShip.position.z = currShip.position.z + currShip.velocity.z + (currShip.force.z/yellowJacketMass)/2;

    currShip.velocity.x = currShip.velocity.x + currShip.force.x/yellowJacketMass;
    currShip.velocity.y = currShip.velocity.y + currShip.force.y/yellowJacketMass;
    currShip.velocity.z = currShip.velocity.z + currShip.force.z/yellowJacketMass;
}

int World::rankOfFighter(Ship& currShip)
{
    double currDistance = currShip.getFullDistance(buzzy.position);
    int rank{0};
    for(auto &ship : fighters)
    {
        if(ship.id != currShip.id)
        {
            double shipDist = ship.getFullDistance(buzzy.position);
            if(shipDist < currDistance)
            {
                rank++;
            }
            else if (shipDist == currDistance)
            {
                if(ship.id < currShip.id)
                {
                    rank++;
                }
            }
        }
    }
}



