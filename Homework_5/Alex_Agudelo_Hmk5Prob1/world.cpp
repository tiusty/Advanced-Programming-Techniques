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

    for(auto & ship : ships)
    {
        double shipSpeed{0};
        double xVec{0};
        double yVec{0};
        double zVec{0};
        file >> ship.position.x >> ship.position.y >> ship.position.z >> shipSpeed >> xVec >> yVec >> zVec;
        ship.velocity.x = shipSpeed * xVec;
        ship.velocity.y = shipSpeed * yVec;
        ship.velocity.z = shipSpeed * zVec;
        ship.maxForce = maxForce;
    }
}

double World::setForce(double force)
{
    double newForce{0};
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

void World::handleYellowJacket(Ship yellowJacket)
{
    yellowJacket.force.x = calculateForce(yellowJacket, yellowJacket.getFullDistance(ships.at(0).position), yellowJacket.position.x, ships.at(0).position.x, yellowJacket.velocity.x, ships.at(0).velocity.x);
    yellowJacket.force.y = calculateForce(yellowJacket, yellowJacket.getFullDistance(ships.at(0).position), yellowJacket.position.y, ships.at(0).position.y, yellowJacket.velocity.y, ships.at(0).velocity.y);
    yellowJacket.force.z = calculateForce(yellowJacket, yellowJacket.getFullDistance(ships.at(0).position), yellowJacket.position.z, ships.at(0).position.z, yellowJacket.velocity.z, ships.at(0).velocity.z);
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

bool World::checkConditions(Ship &yellowJacket)
{
    Ship buzzy = ships.at(0);
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

void World::evolveSystem(Ship& currShip)
{
    currShip.position.x = currShip.position.x + currShip.velocity.x + (currShip.force.x/yellowJacketMass)/2;
    currShip.position.y = currShip.position.y + currShip.velocity.y + (currShip.force.y/yellowJacketMass)/2;
    currShip.position.z = currShip.position.z + currShip.velocity.z + (currShip.force.z/yellowJacketMass)/2;

    currShip.velocity.x = currShip.velocity.x + currShip.force.x/yellowJacketMass;
    currShip.velocity.y = currShip.velocity.y + currShip.force.y/yellowJacketMass;
    currShip.velocity.z = currShip.velocity.z + currShip.force.z/yellowJacketMass;
}



