/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 10/31/19
Description:
 Stores the data/position of a given ship in the world
*/

#ifndef HOMEWORK_5_SHIP_HPP
#define HOMEWORK_5_SHIP_HPP

/**
 * The mass of a yellow jacket
 */
constexpr int yellowJacketMass = 10000;

/**
 * Store coordinate as a struct for easy manipulation
 */
struct Coordinate
{
    // 3D positions
    double x;
    double y;
    double z;

    /**
     * Zero ctro
     */
    Coordinate():Coordinate(0,0,0) {}
    /**
     * Set values for a Coordinate
     */
    Coordinate(double xNew, double yNew, double zNew)
            :x(xNew), y(yNew), z(zNew)
    {}
};

/**
 * Stores position/velocity/force information for a given ship
 */
class Ship {
public: // Methods
    /**
     * Get the distance in 1-D line between two points
     * @param pos Position 1
     * @param dest Position 2
     * @return The distance
     */
    double getDistance(double pos, double dest);
    /**
     * Get the 3D distance between two 3D points.
     * The distance is between this ship and the desired location
     * @param dest The Coordinate of the other object
     * @return The distance as an L2 norm
     */
    double getDistance(Coordinate dest);
    /**
     * calculates the force needed to hit a target velocity in one second time step
     * @param startVel The current vel
     * @param endVel The desired vel
     * @return The force needed
     */
    double forceToGetVel(double startVel, double endVel);
    /**
     * Gets the Mag of the velocity
     * @return The mag of the velocity
     */
    double getMagVel();
    /**
     * Gets the mag of the position
     * @return The mag of the position
     */
    double getMagPos();
    /**
     * Gets the velocity unit vector of this ship
     * @return The unit vector
     */
    Coordinate getVelUnitVec();
    /**
     * Gets the position unit vector of this ship
     * @return The unit vector
     */
    Coordinate getDistUnitVec();

public: // Members
    /**
     * The id of the ship
     */
    int id{0};
    /**
     * The 3D position of the ship
     */
    Coordinate position{0,0,0};
    /**
     * The 3D velocity of the ship
     */
    Coordinate velocity{10,0,0};
    /*
     * The 3D force vector of this ship
     */
    Coordinate force{0,0,0};
    /*
     * The max allowed force
     */
    double maxForce{0};
    /**
     * State of the ship
     *  0 = destroyed
     *  1 = active
     *  2 = docked
     */
    int status{1};
};


#endif //HOMEWORK_5_SHIP_HPP
