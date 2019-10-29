/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 10/29/19
Description: 
*/

#ifndef HOMEWORK_5_SHIP_HPP
#define HOMEWORK_5_SHIP_HPP

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
    int timeToStop(const Coordinate& dest);
    double getDistance(const Coordinate& dest);
    double getMagVel();
    double getLargestVelocityVector();
    Coordinate getVelUnitVec();


public: // Members
    Coordinate position{0,0,0};
    Coordinate velocity{0,0,0};
    Coordinate force{0,0,0};
    int maxForce{54000};
    int status;
};


#endif //HOMEWORK_5_SHIP_HPP
