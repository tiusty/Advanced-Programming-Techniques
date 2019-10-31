/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 10/31/19
Description: 
*/

#include <fstream>
#include <iostream>
#include <cmath>
#include "world.hpp"
#include <random>

// Define constexpr variables
constexpr int World::elementsPerShip;

void World::setWorldData(double *recBuf)
{
    // Array follows format
    // [xPos, yPos, zPos, xVel, yVel, zVel, xForce, yForce, zForce, status]
    // The first 7 are buzz
    // each 7 after that is each fighter
    buzzy.position = {recBuf[0], recBuf[1], recBuf[2]};
    buzzy.velocity = {recBuf[3], recBuf[4], recBuf[5]};
    buzzy.force = {recBuf[6], recBuf[7], recBuf[8]};

    int fighterCount{1};
    for(auto &ship : fighters)
    {
        ship.position = {recBuf[elementsPerShip*fighterCount], recBuf[elementsPerShip*fighterCount+1], recBuf[elementsPerShip*fighterCount+2]};
        ship.velocity = {recBuf[elementsPerShip*fighterCount+3], recBuf[elementsPerShip*fighterCount+4], recBuf[elementsPerShip*fighterCount+5]};
        ship.force = {recBuf[elementsPerShip*fighterCount+6], recBuf[elementsPerShip*fighterCount+7], recBuf[elementsPerShip*fighterCount+8]};
        ship.status = static_cast<int>(recBuf[elementsPerShip*fighterCount+9]);
        ship.id = fighterCount - 1;
        fighterCount++;
    }
}

void World::getShipDataBuzzy(double *sendBuff)
{
    sendBuff[0] = buzzy.position.x;
    sendBuff[1] = buzzy.position.y;
    sendBuff[2] = buzzy.position.z;
    sendBuff[3] = buzzy.velocity.x;
    sendBuff[4] = buzzy.velocity.y;
    sendBuff[5] = buzzy.velocity.z;
    sendBuff[6] = buzzy.force.x;
    sendBuff[7] = buzzy.force.y;
    sendBuff[8] = buzzy.force.z;
    sendBuff[9] =  1;
}

void World::getShipData(double *sendBuff, int shipNum)
{
    sendBuff[0] = fighters.at(shipNum).position.x;
    sendBuff[1] = fighters.at(shipNum).position.y;
    sendBuff[2] = fighters.at(shipNum).position.z;
    sendBuff[3] = fighters.at(shipNum).velocity.x;
    sendBuff[4] = fighters.at(shipNum).velocity.y;
    sendBuff[5] = fighters.at(shipNum).velocity.z;
    sendBuff[6] = fighters.at(shipNum).force.x;
    sendBuff[7] = fighters.at(shipNum).force.y;
    sendBuff[8] = fighters.at(shipNum).force.z;
    sendBuff[9] = static_cast<int>(fighters.at(shipNum).status);
}

void World::getWorldData(double *sendBuff)
{
    sendBuff[0] = buzzy.position.x;
    sendBuff[1] = buzzy.position.y;
    sendBuff[2] = buzzy.position.z;
    sendBuff[3] = buzzy.velocity.x;
    sendBuff[4] = buzzy.velocity.y;
    sendBuff[5] = buzzy.velocity.z;
    sendBuff[6] = buzzy.force.x;
    sendBuff[6] = buzzy.force.y;
    sendBuff[6] = buzzy.force.z;

    int fighterCount{1};
    for(auto &ship : fighters)
    {
        sendBuff[elementsPerShip*fighterCount] = ship.position.x;
        sendBuff[elementsPerShip*fighterCount+1] = ship.position.y;
        sendBuff[elementsPerShip*fighterCount+2] = ship.position.z;
        sendBuff[elementsPerShip*fighterCount+3] = ship.velocity.x;
        sendBuff[elementsPerShip*fighterCount+4] = ship.velocity.y;
        sendBuff[elementsPerShip*fighterCount+5] = ship.velocity.z;
        sendBuff[elementsPerShip*fighterCount+6] = ship.force.x;
        sendBuff[elementsPerShip*fighterCount+7] = ship.force.y;
        sendBuff[elementsPerShip*fighterCount+8] = ship.force.z;
        sendBuff[elementsPerShip*fighterCount+9] = ship.status;
        fighterCount++;
    }
}

void World::loadData()
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

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(80, 120); // define the range
    double ran = static_cast<double>(distr(eng))/100;
    return newForce*ran;

}

void World::handleYellowJacket(Ship &yellowJacket, int currDuration)
{
    // If it is not active then do nothing
    if(yellowJacket.status == 1)
    {
        // Stagger the fighters from moving so that the one with the highest rank approaches buzzy first
        if(currDuration > rankOfFighter(yellowJacket)*200)
        {
            yellowJacket.force.x = calculateForce(yellowJacket, yellowJacket.getDistance(buzzy.position), yellowJacket.position.x, buzzy.position.x, yellowJacket.velocity.x, buzzy.velocity.x);
            yellowJacket.force.y = calculateForce(yellowJacket, yellowJacket.getDistance(buzzy.position), yellowJacket.position.y, buzzy.position.y, yellowJacket.velocity.y, buzzy.velocity.y);
            yellowJacket.force.z = calculateForce(yellowJacket, yellowJacket.getDistance(buzzy.position), yellowJacket.position.z, buzzy.position.z, yellowJacket.velocity.z, buzzy.velocity.z);
        }
    }
}

double World::calculateForce(Ship ship, double dist3D, double currPos, double targetPos, double currVel, double targetVel)
{
    double force{0};
    if (dist3D > 1000)
    {
        if (std::fabs(currPos - targetPos) > 1000)
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
        if(yellowJacket.getDistance(buzzy.position) < 50)
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
            double distance = yellowJacket.getDistance(ship.position);
            if(distance < 250 && yellowJacket.id != ship.id && ship.status == 1)
            {
                yellowJacket.status = 0;
                ship.status=0;
            }
        }

    }
}

void World::evolveSystem(Ship& currShip)
{
    // Simulate the ship movement if it is active
    if(currShip.status == 1)
    {
        currShip.position.x = currShip.position.x + currShip.velocity.x + (currShip.force.x/yellowJacketMass)/2;
        currShip.position.y = currShip.position.y + currShip.velocity.y + (currShip.force.y/yellowJacketMass)/2;
        currShip.position.z = currShip.position.z + currShip.velocity.z + (currShip.force.z/yellowJacketMass)/2;

        currShip.velocity.x = currShip.velocity.x + currShip.force.x/yellowJacketMass;
        currShip.velocity.y = currShip.velocity.y + currShip.force.y/yellowJacketMass;
        currShip.velocity.z = currShip.velocity.z + currShip.force.z/yellowJacketMass;
    }
    // If the ship is docked then its position is just the last broadcast position of buzzy
    else if(currShip.status == 2)
    {
        currShip.position.x = buzzy.position.x;
        currShip.position.y = buzzy.position.y;
        currShip.position.z = buzzy.position.z;
    }
    else
    {
        // If the ship is destroyed then do nothing
    }
}

int World::rankOfFighter(Ship& currShip)
{
    double currDistance = currShip.getDistance(buzzy.position);
    int rank{0};
    for(auto &ship : fighters)
    {
        if(ship.id != currShip.id)
        {
            double shipDist = ship.getDistance(buzzy.position);
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

    return rank;
}

std::string World::getStatus(const Ship &ship)
{
    if(ship.status == 0)
    {
        return "Destroyed";
    }
    else if(ship.status == 1)
    {
        return "Still active";
    }
    else if (ship.status == 2)
    {
        return "Docked";
    }
    else
    {
        return "Unknown";
    }
}

void World::printResult()
{
    for(auto &ship : fighters)
    {
        std::cout << "Fighter: " << ship.id << ", status: " << getStatus(ship) << std::endl;
    }
}



