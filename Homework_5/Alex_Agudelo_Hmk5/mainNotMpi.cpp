/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 10/29/19
Description: This main function tests the code without using mpi
*/
#include <iostream>

#include "world.h"

int main()
{
    // Generate the world
    World world;
    world.loadData();

    // Loop for the mount of time we are allowed
    for(int i=0; i< world.duration; i++)
    {
        for(auto &ship : world.fighters)
        {
            world.handleYellowJacket(ship, i);
        }

        world.evolveSystem(world.buzzy);
        for(auto &ship : world.fighters)
        {
            world.evolveSystem(ship);
        }

        for(auto &ship : world.fighters)
        {
            world.checkConditions(ship);
        }
    }

    world.printResult();

    return 1;
}

