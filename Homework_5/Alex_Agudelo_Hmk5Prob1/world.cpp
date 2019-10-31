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
    std::ifstream file("in.data");

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