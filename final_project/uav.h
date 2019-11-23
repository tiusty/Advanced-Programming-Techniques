/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 11/22/2019
Description:
 Define a single instance of a uav. Stores all the info regarding a single uav
*/

#ifndef FINALPROJECT_UAV_H
#define FINALPROJECT_UAV_H

/**
 * Struct defines a Coordiante in 3D space to easily represent the location of a UAV
 */
struct Coordinate
{
    float x{0},y{0},z{0};
};

/**
 * Class stores information regarding a single UAV and actions it may perform
 */
class UAV {
public: // Methods
    void drawUAV() const;
    void setColor() const;
public: // Members
    static constexpr unsigned int mass = 1; //kg
    Coordinate location;
    Coordinate velocity;
};


#endif //FINALPROJECT_UAV_H
