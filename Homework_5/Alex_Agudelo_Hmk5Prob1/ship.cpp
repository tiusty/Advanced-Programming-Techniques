/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 10/29/19
Description: 
*/

#include "ship.hpp"

#include <cmath>

int Ship::timeToGetToVel(double currVel, double desiredVel)
{
    return std::abs((desiredVel - currVel)*yellowJacketMass/maxForce);
}

double Ship::getForce(double force)
{
    return force;
}

int Ship::timeToDest(double pos, double dest, double vel)
{
    if(vel < 0)
    {
        return 10000;
    }
    if(vel != 0)
    {
        return std::abs(static_cast<int>(std::floor(getDistance(pos, dest)/vel)));
    }
    return 0;
}

double Ship::getDistanceUnitVec(double pos, double norm)
{
    return pos/norm;
}

double Ship::getDistance(double pos, double dest)
{
    return std::sqrt(std::pow(pos-dest,2));
}

double Ship::getFullDistance(Coordinate dest)
{
    return std::sqrt(std::pow(position.x - dest.x, 2) + std::pow(position.y - dest.y, 2) + std::pow(position.z - dest.z, 2));}

double Ship::getMagVel()
{

    return std::sqrt(std::pow(velocity.x,2) + std::pow(velocity.y,2) + std::pow(velocity.z, 2));
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
