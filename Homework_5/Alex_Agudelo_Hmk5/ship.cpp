/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 10/31/19
Description:
 Implements ship functionality
*/

#include "ship.hpp"

#include <cmath>

Coordinate Ship::getVelUnitVec()
{
    // Unit vec is the velocity component divided by the magniuted
    if(getMagVel() != 0)
    {
        return {velocity.x/getMagVel(), velocity.y/getMagVel(), velocity.z/getMagVel()};
    }
    return {0,0,0};
}

Coordinate Ship::getDistUnitVec()
{
    // Unit vec is the velocity component divided by the magniuted
    if(getMagPos() != 0)
    {
        return {position.x/getMagPos(), position.y/getMagPos(), position.z/getMagPos()};
    }
    return {0,0,0};
}

double Ship::getDistance(double pos, double dest)
{
    // L2 norm between two points in 1D
    return std::sqrt(std::pow(pos-dest,2));
}

double Ship::getDistance(Coordinate dest)
{
    // L2 norm between two points in 3D
    return std::sqrt(std::pow(position.x - dest.x, 2) + std::pow(position.y - dest.y, 2) + std::pow(position.z - dest.z, 2));}

double Ship::getMagVel()
{
    // Norm of the velocity vector
    return std::sqrt(std::pow(velocity.x,2) + std::pow(velocity.y,2) + std::pow(velocity.z, 2));
}

double Ship::getMagPos()
{
    // Norm of the position vector
    return std::sqrt(std::pow(position.x,2) + std::pow(position.y,2) + std::pow(position.z, 2));
}

double Ship::forceToGetVel(double startVel, double endVel)
{
    // Equation of motion to for desired force
    double forceToGetVel = (endVel - startVel)*yellowJacketMass;

    // Set bounds to prevent over powering if added to another force before calling setForce
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
