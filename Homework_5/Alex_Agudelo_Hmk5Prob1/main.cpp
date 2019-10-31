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

int main()
{
    World world;
    // Determine stating positions

    for(int i=0; i< world.duration; i++)
    {
        for(auto &ship : world.fighers)
        {
            world.handleYellowJacket(ship);
        }

        world.evolveSystem(world.buzzy);
        for(auto &ship : world.fighers)
        {
            world.evolveSystem(ship);
        }

        for(auto &ship : world.fighers)
        {
            world.checkConditions(ship);
        }
        std::cout << "End" << std::endl;
    }

    return 1;
}
