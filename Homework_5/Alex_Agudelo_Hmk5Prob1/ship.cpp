/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 10/29/19
Description: 
*/

#include "ship.hpp"

#include <cmath>

Coordinate Ship::getVelUnitVec()
{
    if(getMagVel() != 0)
    {
        return {velocity.x/getMagVel(), velocity.y/getMagVel(), velocity.z/getMagVel()};
    }
    return {0,0,0};
}

Coordinate Ship::getDistUnitVec()
{
    if(getMagPos() != 0)
    {
        return {position.x/getMagPos(), position.y/getMagPos(), position.z/getMagPos()};
    }
    return {0,0,0};
}

double Ship::getDistance(double pos, double dest)
{
    return std::sqrt(std::pow(pos-dest,2));
}

double Ship::getDistance(Coordinate dest)
{
    return std::sqrt(std::pow(position.x - dest.x, 2) + std::pow(position.y - dest.y, 2) + std::pow(position.z - dest.z, 2));}

double Ship::getMagVel()
{
    return std::sqrt(std::pow(velocity.x,2) + std::pow(velocity.y,2) + std::pow(velocity.z, 2));
}

double Ship::getMagPos()
{
    return std::sqrt(std::pow(position.x,2) + std::pow(position.y,2) + std::pow(position.z, 2));
}

double Ship::forceToGetVel(double startVel, double endVel)
{
    double forceToGetVel = (endVel - startVel)*yellowJacketMass;
    if(forceToGetVel > maxForce)
    {
        return maxForce;
    }
    else if(forceToGetVel < -maxForce)
    {
        return -maxForce;
    }
    else
    {
        return forceToGetVel;
    }
}
