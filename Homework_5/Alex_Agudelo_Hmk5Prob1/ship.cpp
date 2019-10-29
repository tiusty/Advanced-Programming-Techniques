/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 10/29/19
Description: 
*/

#include "ship.hpp"

#include <cmath>

int Ship::timeToStop(const Coordinate& dest)
{
    if(getLargestVelocityVector() != 0)
    {
        return static_cast<int>(std::ceil(getDistance(dest)/getLargestVelocityVector()));
    }
    return 0;
}
double Ship::getDistance(const Coordinate& dest)
{
    return std::sqrt(std::pow(position.x - dest.x, 2) + std::pow(position.y - dest.y, 2) + std::pow(position.z - dest.z, 2));
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

Coordinate Ship::getVelUnitVec()
{
    int norm = static_cast<int>(std::sqrt(std::pow(velocity.x,2) + std::pow(velocity.y, 2) + std::pow(velocity.z,2)));
    return {velocity.x/norm, velocity.y/norm, velocity.z/norm};
}
