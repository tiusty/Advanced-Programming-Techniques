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
    Coordinate() = default;
    Coordinate(double x, double y, double z)
    :x{x}, y{y}, z{z} {}
    double x{0},y{0},z{0};
};

/**
 * Class stores information regarding a single UAV and actions it may perform
 */
class UAV {
public: // Methods
    UAV() = default;
    void setCenter(Coordinate center);
    void drawUAV() const;
    void setColor() const;
    double distanceFromCenterOfSphere();
    Coordinate calculateForceUnitVec();
    double calculateForceMag();
    double velMag();
    Coordinate getForce();
    void evolveSystem();
public: // Members
    static constexpr double mass = 1; //kg
    static constexpr double kSpring = 1;
    static constexpr double timeStep = .1; //seconds
    static constexpr double maxForce = 20;
    static constexpr double gravity = -10;
    Coordinate location;
    Coordinate velocity;
    Coordinate sphereCenter;
    bool initApproach{true};
    bool slowingDown{false};
};


#endif //FINALPROJECT_UAV_H
