/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 10/29/19
Description: 
*/

#include "ship.hpp"

#include <cmath>

int Ship::timeToStop(double velocity)
{
    // Do .95 percent so there is a margin due to the misfire
    return std::abs(static_cast<int>(std::ceil((velocity/(maxForce*.95))*yellowJacketMass)));
}

int Ship::timeToDest(double pos, double dest, double vel)
{
    if(vel != 0)
    {
        return std::abs(static_cast<int>(std::ceil(getDistance(pos, dest)/vel)));
    }
    return 0;
}

double Ship::getDistanceUnitVec(double pos, double dest)
{
    double distNorm = getDistance(pos, dest);
    return (dest - pos)/distNorm;
}

double Ship::getDistance(double pos, double dest)
{
    return std::sqrt(std::pow(pos-dest,2));
}

double Ship::getMagVel()
{

    return std::sqrt(std::pow(velocity.x,2) + std::pow(velocity.y,2) + std::pow(velocity.z, 2));
}

double Ship::getLargestVelocityVector()
{
    double largest = std::abs(velocity.x);
    if(largest < std::abs(velocity.y))
    {
        largest = std::abs(velocity.y);
    }
    if(largest < std::abs(velocity.z))
    {
        largest = std::abs(velocity.z);
    }

    return largest;
}

double Ship::stopForce(double vel)
{
    double forceToStop = -vel*yellowJacketMass;
    if(forceToStop > maxForce)
    {
        return maxForce;
    }
    else
    {
        return forceToStop;
    }
}

Coordinate Ship::getVelUnitVec()
{
    int norm = static_cast<int>(std::sqrt(std::pow(velocity.x,2) + std::pow(velocity.y, 2) + std::pow(velocity.z,2)));
    return {velocity.x/norm, velocity.y/norm, velocity.z/norm};
}
