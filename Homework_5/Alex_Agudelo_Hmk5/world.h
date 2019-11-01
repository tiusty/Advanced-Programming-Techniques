/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 10/31/19
Description:
 World stores information regarding all objects and manipulations that occur
*/

#ifndef HOMEWORK_5_WORLD_HPP
#define HOMEWORK_5_WORLD_HPP

#include <array>

#include "ship.h"

/**
 * The world stores all the ships, and functionality related to moving the ships
 *
 * When using MPI, the array format goes as follows
 * [xPos, yPos, zPos, xVel, yVel, zVel, xForce, yForce, zForce, status]
 *
 * This is used in two ways
 * 1. Just as the ship data which only contains those 10 elements for a single ship
 * 2. In the world dataw which contains those 10 elements concatenated together with the
 * rest of the ships so that follow the format
 * [buzzy, ship1, ship2...]
 * that patter is repeated for buzzy + # of fighters
 *
 * Therefore the number of elements in that world array is
 * 10*#of ships
 *
 */
class World {
public: // Methods
    /**
     * Default ctor
     */
    World() = default;
    /**
     * Sets the world members based on the input array. The input array is what is expected
     *  to be received from the MPI framework
     * @param recBuf The array following format described above
     */
    void setWorldData(double *recBuf);
    /**
     * Populates the recBuf with the data from a single ship
     * @param sendBuff The array which is size 10 for all the components of the ship data
     * @param shipNum The fighter # that that is desired
     */
    void getShipData(double *sendBuff, int shipNum);
    /**
     * Same as above execpt it returns the data for buzzy
     * @param sendBuff The buffer that will contain the data for buzzy
     */
    void getShipDataBuzzy(double *sendBuff);
    /**
     * Populates the sendBuff with the data from the world, aka all the ships
     * @param sendBuff Where the data will be populated, needs size of 10*#of ships
     */
    void getWorldData(double *sendBuff);
    /**
     * Loads data from in.dat file
     */
    void loadData();
    /**
     * Sets the force that is actually applied. Adjusts force due to bounds and misfire
     * @param force The desired force
     * @return The actual force exerted
     */
    double setForce(double force);
    /**
     * Handles the functionality of a fighter for a single time step
     * @param yellowJacket The yellowjacket being operated on
     * @param currDuration The current duration of the simulation
     */
    void handleYellowJacket(Ship &yellowJacket, int currDuration);
    /**
     * Calculates the force that should be exerted in the given component.
     * This should be called for each of the 3 components, x,y,z
     * @param ship The current ship
     * @param dist3D The 3D norm between the ship and buzzy
     * @param currPos The current position for the sub component
     * @param targetPos The target position for the sub component
     * @param currVel The current velocity along the sub component
     * @param targetVel The target velocity along the sub component
     * @return The force that should be exerted along that sub component
     */
    double calculateForce(Ship ship, double dist3D, double currPos, double targetPos, double currVel, double targetVel);
    /**
     * Checks the condition of the yellow jacket to test for status changes
     * @param yellowJacket The current fighter
     */
    void checkConditions(Ship &yellowJacket);
    /**
     * Evolves the system one time step
     * @param currShip The current ship
     */
    void evolveSystem(Ship& currShip);
    /**
     * Determines the rank of the fighter. The lower the rank the closer the fighter is to buzzy.
     * Rank 0, means closet fighter.
     * @param currShip  The current ship
     * @return The rank of the fighter
     */
    int rankOfFighter(Ship& currShip);
    /**
     * Function to easily print out the status string representation
     * @param ship The current ship
     * @return The string for the status
     */
    std::string getStatus(const Ship &ship);
    /**
     * Prints the results of the fighters
     */
    void printResult();

public: // Members
    /**
     * The number of elements per ship for the mpi framework
     */
    static constexpr int elementsPerShip{10};

    /**
     * The max force each fighter can exert
     */
    double maxForce{0};
    /**
     * The duration of the simulation
     */
    int duration{0};
    /**
     * The fighters that are trying to dock on buzzy
     */
    std::array<Ship, 7> fighters;
    /**
     * BUZZY! Buzz buzz
     */
    Ship buzzy;
};


#endif //HOMEWORK_5_WORLD_HPP
