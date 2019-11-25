/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 11/25/2019
Description: 
*/

#ifndef FINALPROJECT_FOOTBALLFIELD_H
#define FINALPROJECT_FOOTBALLFIELD_H

#include <array>
#include "uav.h"

// Helper function to convert from yards to meters
constexpr float yardToMeter(float yardValue)
{
    return yardValue*.9144;
}

/**
 * Classes stores the state of the football field and all the uavs on it
 *
 * Data format per UAV is:
 * x,y,z,velx,vely,velz, initApproach
 *
 * Used for MPI framework for passing data between processes
 */
class FootballField {
public: // Methods
    /**
     * Ctor that initializes the field and the UAVs on it
     */
    FootballField();
    /**
     * Retrives the MPI values for a single uav
     * @param data double array of size numElements, that will have the data populated based on format above
     * @param uavNum The UAV that the data is desired from
     */
    void getUavData(double data[], unsigned int uavNum);
    /**
     * Sets the whole field data. Takes an array of all the UAVs plus a blank first numElements
     * to populate the field data
     * @param data Double array of size numElements*16
     */
    void setFieldData(double data[]);
    /**
     * Initializes UAVs in correct location
     */
    void initializeUAVs();
    /**
     * Draws the football field
     */
    void drawField();
    /**
     * Draws all the uavs
     */
    void drawUAVS(unsigned int timeStep);
    /**
     * Draws the desired sphere location
     */
    void drawSphere();
    /**
     * Calculates the L-2 norm between UAVs
     * @param uav1 The first uav
     * @param uav2 The second uav
     * @return The distance between the two
     */
    double distanceBetweenUavs(const UAV &uav1, const UAV &uav2) const;
    /**
     * Determines the sphere location
     * @return
     */
    Coordinate sphereLocation();
    /**
     * Check to see if all the UAVs made it to the sphere
     * @return True -> They all have made it to the sphere
     *         False -> Not all of them have made it yet
     */
    bool checkAllUavsAtSphere();
    /**
     * Checks all the UAVs locations and see if any have collided
     */
    void checkCollisions();
public: // Members
    /**
     * The length of the football field
     */
    static constexpr float lenFootballField{yardToMeter(100)};
    /**
     * The width of the football field
     */
    static constexpr float widthFootballField{yardToMeter((53*3+1)/3)};
    /**
     * Number of UAVS
     */
    static constexpr unsigned int numUAVs{15};
    /**
     * The number of elements per UAV to send in the MPI framework
     */
    static constexpr unsigned int numElements{7};
    /**
     * Stores all the uavs
     */
    std::array<UAV, numUAVs> uavs;
    /**
     * The center of the football field
     */
    Coordinate origin;
};


#endif //FINALPROJECT_FOOTBALLFIELD_H
