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
    double getDistance(double pos, double dest);
    double getDistance(Coordinate dest);
    double forceToGetVel(double startVel, double endVel);
    double getMagVel();
    double getMagPos();
    Coordinate getVelUnitVec();
    Coordinate getDistUnitVec();

public: // Members
    int id{0};
    Coordinate position{0,0,0};
    Coordinate velocity{10,0,0};
    Coordinate force{0,0,0};
    double maxForce{0};
    int status{1};
};


#endif //HOMEWORK_5_SHIP_HPP
