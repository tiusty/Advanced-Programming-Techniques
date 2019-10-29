/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 10/29/19
Description: 
*/
#include <iostream>
#include <cmath>

#include "ship.hpp"

constexpr int yellowJacketMass = 10000;

void handleYellowJacket();
void calculateYellowJacketForce();
Ship yellowJacket{};
Coordinate destination{100, 100, 100};

int main()
{
    std::cout << "Hello World" << std::endl;

    // Read in files

    // Determine stating positions

    // On Buzzy just calculate new position
    Ship buzzy{};

    for(int i=0; i< 10; i++)
    {
        handleYellowJacket();
    }

    // For each jacket
    // 1. Determine the force necessary
    //      Determine how many time steps to reach goal location at max speed
    //      Calculate the position of buzz at that time step
    //      Determine number of time steps to slow down to necessary speed
    //          When the number of steps of steps is 4 then start slowing down at 4 + 4

    //  If mag of distance is less than 1000 then stop and wait turn
    //      The closest person who is less than 1000 will proceed to dock
    // 2. Evolve the system
    return 1;
}


void evolveSystem(Ship& currShip)
{
    currShip.position.x = currShip.position.x + currShip.velocity.x + (currShip.force.x/yellowJacketMass)/2;
    currShip.position.y = currShip.position.y + currShip.velocity.y + (currShip.force.y/yellowJacketMass)/2;
    currShip.position.z = currShip.position.z + currShip.velocity.z + (currShip.force.z/yellowJacketMass)/2;

    currShip.velocity.x = currShip.velocity.x + currShip.force.x/yellowJacketMass;
    currShip.velocity.y = currShip.velocity.y + currShip.force.y/yellowJacketMass;
    currShip.velocity.z = currShip.velocity.z + currShip.force.z/yellowJacketMass;
}

void handleYellowJacket()
{
    yellowJacket.force.x = 50000;
//    calculateYellowJacketForce();
    std::cout << yellowJacket.timeToStop(destination) << std::endl;
    evolveSystem(yellowJacket);
}

void calculateTimeToDest(const Coordinate& dest)
{

}

void calculateYellowJacketForce()
{

}

