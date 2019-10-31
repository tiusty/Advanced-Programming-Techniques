/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 10/31/19
Description: 
*/

#ifndef HOMEWORK_5_WORLD_HPP
#define HOMEWORK_5_WORLD_HPP

#include <array>

#include "ship.hpp"

class World {
public: // Methods
    World();
    double setForce(double force);
    void handleYellowJacket(Ship yellowJacket);
    double calculateForce(Ship ship, double dist3D, double currPos, double targetPos, double currVel, double targetVel);
    bool checkConditions(Ship &yellowJacket);
    void evolveSystem(Ship& currShip);
public: // Members
    double maxForce{0};
    int duration{0};

    std::array<Ship, 8> ships;
};


#endif //HOMEWORK_5_WORLD_HPP
