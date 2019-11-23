/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 11/22/2019
Description: 
*/

#ifndef FINALPROJECT_FOOTBALLFIELD_H
#define FINALPROJECT_FOOTBALLFIELD_H

#include <array>
#include "uav.h"

// Football field parameters
constexpr float yardToMeter(float yardValue)
{
    return yardValue*.9144;
}

class FootballField {
public: // Methods
    FootballField();
    void initializeUAVs();
    void drawField();
    void drawUAVS();
    void drawSphere();
    Coordinate sphereLocation();
    bool checkAllUavsAtSphere();
public: // Members
    static constexpr float lenFootballField{yardToMeter(100)};
    static constexpr float widthFootballField{yardToMeter((53*3+1)/3)};
    static constexpr unsigned int numUAVs{15};
    std::array<UAV, numUAVs> uavs;
    Coordinate origin;
};


#endif //FINALPROJECT_FOOTBALLFIELD_H
