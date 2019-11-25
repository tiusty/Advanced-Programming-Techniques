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
    /**
     * Default ctor
     */
    UAV() = default;
    /**
     * Sets the center of the sphere that the uavs are trying to circle
     * @param center Coordinates of the center of the sphere
     */
    void setCenter(Coordinate center);
    /**
     * Draws the uav in the correct location
     * @param timeStep Used for color oscillations. Expects value 0-128
     */
    void drawUAV(unsigned int timeStep) const;
    /**
     * Sets the color of the uav
     * @param timeStep Used for color oscillations. Expects value 0-128
     */
    void setColor(unsigned int timeStep) const;
    /**
     * Determines the L-2 distance from the center of the sphere
     * @return The magnitude of the distance
     */
    double distanceFromCenterOfSphere();
    /**
     * Returns the desired force unit vector to maintain 10 meters from center of sphere
     * @return The coordinate
     */
    Coordinate calculateForceUnitVec();
    /**
     * Calculates the current velocity unit vector
     * @return The coordinate
     */
    Coordinate velUnitVec();
    /**
     * Calculates the desired force magnitude to maintain 10 meter from center of sphere
     * @return The mag of the force
     */
    double calculateForceMag();
    /**
     * The current velocity magnitude of the uav
     * @return The mag of the velocity
     */
    double velMag();
    /**
     * Gets the force vector to apply which includes desired force + effect of gravity
     * @return The force values
     */
    Coordinate getForce();
    /**
     * Gets a random orthogonal vector to the input vector
     * @param vec The input vector that needs an orthogonal vector
     * return The vector
     */
    Coordinate getOrthogonalVector(Coordinate vec);
    /**
     * Moves the uav one time step
     */
    void evolveSystem();
public: // Members
    /**
     * Mass of the uav
     */
    static constexpr double mass = 1; //kg
    /**
     * Desired spring constant for hooke's law
     */
    static constexpr double kSpring = 1;
    /**
     * The timestep per iteration
     */
    static constexpr double timeStep = .1; //seconds
    /**
     * Max allowed force
     */
    static constexpr double maxForce = 20;
    /**
     * Maginutde of gravity
     */
    static constexpr double gravity = -10;
    /**
     * The current location of the uav
     */
    Coordinate location;
    /**
     * The current velocity vector of the uav
     */
    Coordinate velocity;
    /**
     * The location of the center of the desired sphere
     */
    Coordinate sphereCenter;
    /**
     * Determines if the uav is approaching the sphere or not
     */
    bool initApproach{true};
    /**
     * Determines if the uav is slowing down or speeding up
     */
    bool slowingDown{false};
};


#endif //FINALPROJECT_UAV_H
