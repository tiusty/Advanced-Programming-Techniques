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
        for(auto &ship : world.ships)
        {
            world.handleYellowJacket(ship);
        }

        for(auto &ship : world.ships)
        {
            world.evolveSystem(ship);
        }

        for(unsigned int j=1; j<world.ships.size(); j++)
        {
            if(world.checkConditions(world.ships.at(j)))
            {
                break;
            }
        }
    }

    return 1;
}

void initializeShips()
{
}


