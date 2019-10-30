/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 10/29/19
Description: 
*/

#ifndef HOMEWORK_5_SHIP_HPP
#define HOMEWORK_5_SHIP_HPP

constexpr int yellowJacketMass = 10000;

struct Coordinate
{
    double x;
    double y;
    double z;

    Coordinate():Coordinate(0,0,0) {}
    Coordinate(double xNew, double yNew, double zNew)
            :x(xNew), y(yNew), z(zNew)
    {}
};


class Ship {
public: // Methods
    int timeToStop(double velocity);
    int timeToDest(double pos, double dest, double vel);
    double getDistance(double pos, double dest);
    double getFullDistance(Coordinate dest);
    double getDistanceUnitVec(double pos, double dest);
    double forceToGetVel(double startVel, double endVel);
    double getMagVel();
    double getLargestVelocityVector();
    Coordinate getVelUnitVec();
    double stopForce(double vel);


public: // Members
    Coordinate position{0,0,0};
    Coordinate velocity{10,0,0};
    Coordinate force{0,0,0};
    int maxForce{54000};
    int status;
};


#endif //HOMEWORK_5_SHIP_HPP
