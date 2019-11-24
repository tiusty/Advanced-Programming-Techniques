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
    void getUavData(double data[], unsigned int uavNum);
    void setFieldData(double data[]);
    void initializeUAVs();
    void drawField();
    void drawUAVS(unsigned int timeStep);
    void drawSphere();
    double distanceBetweenUavs(const UAV &uav1, const UAV &uav2) const;
    Coordinate sphereLocation();
    bool checkAllUavsAtSphere();
    void checkCollisions();
public: // Members
    static constexpr float lenFootballField{yardToMeter(100)};
    static constexpr float widthFootballField{yardToMeter((53*3+1)/3)};
    static constexpr unsigned int numUAVs{15};
    static constexpr unsigned int numElements{6};
    std::array<UAV, numUAVs> uavs;
    Coordinate origin;
};


#endif //FINALPROJECT_FOOTBALLFIELD_H
