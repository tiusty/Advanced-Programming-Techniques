/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 10/31/19
Description: 
    Main function using MPI. Initializes MPI framework and calls each fighter on a different node(Process)
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <array>
#include <iomanip>

#include "mpi.h"
#include "world.h"
#define  MASTER		0

int main(int argc, char *argv[])
{
    // Declare variables
    int   numtasks, taskid, len, rc;
    char hostname[MPI_MAX_PROCESSOR_NAME];
    double shipData[World::elementsPerShip];
    double* pWorldData;

    // Setup MPI
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
    MPI_Get_processor_name(hostname, &len);

    // Set up variables for all MPI processes
    World world;
    int numWorldElements = world.elementsPerShip*numtasks;
    int miscData[2]{0};
    pWorldData = new double[numWorldElements];

    // Master will load data, the rest of the processes will wait to receive the data from the Master process
    if(taskid == MASTER)
    {
        world.loadData();
        world.getWorldData(pWorldData);
        miscData[0] = world.maxForce;
        miscData[1] = world.duration;
    }
    // Send world data to all other processes
    MPI_Bcast(pWorldData, numWorldElements, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);
    world.setWorldData(pWorldData);
    // Send misc data such as max force and duration to other processes
    MPI_Bcast(miscData, 2, MPI_INT, MASTER, MPI_COMM_WORLD);
    world.maxForce = miscData[0];
    world.duration = miscData[1];

    // Run simulation for the duration allocated
    for(int i=0; i<world.duration; i++)
    {
        // Master handles only the buzzy dynamics
        if(taskid == MASTER)
        {

            // Evolve buzzy location
            world.evolveSystem(world.buzzy);

            // Get the data for buzzy
            world.getShipDataBuzzy(shipData);

            MPI_Allgather(shipData, 10, MPI_DOUBLE, pWorldData, 10, MPI_DOUBLE, MPI_COMM_WORLD);

            // Update the world with the new data
            world.setWorldData(pWorldData);

            // Print out fighter data
            for(int j=1; j<numtasks; j++)
            {
                Ship *fighter = &world.fighters.at(j);
                std::cout << std::scientific << std::setprecision(6);
                std::cout << j << "," << fighter->status << "," << fighter->position.x << "," << fighter->position.y << "," << fighter->position.z << "," << fighter->force.x << "," << fighter->force.y << "," << fighter->force.z << std::endl;
            }
        }
        // Each of the other processes handles one of the yellow jackets
        else
        {
            //The fighter num is determined by taskid
            int shipNum = taskid -1;

            // Calculate and set forces for the processes yellow jacket
            world.handleYellowJacket(world.fighters.at(shipNum), i);

            // Evolve the ship location based on force calculated
            // Each process will evolve their own ship
            world.evolveSystem(world.fighters.at(shipNum));

            // Return the ship data for this process
            world.getShipData(shipData, shipNum);

            // Blocks until everyone calls allgather (including master)
            // Each process will add their own shipData and afterwards,
            //  Every process will have the aggregated pWorldData which contains
            //  All the ship data together in one array.
            MPI_Allgather(shipData, 10, MPI_DOUBLE, pWorldData, 10, MPI_DOUBLE, MPI_COMM_WORLD);

            // Since every process has the ship data from every other process
            //  Update the current processes world information from the data it received from all the other processes
            world.setWorldData(pWorldData);

            // Check the conditions to see if any fighters crashed etc
            world.checkConditions(world.fighters.at(shipNum));
        }
    }

    // Master process print out result of simulation
    if(taskid == MASTER)
    {
//        world.printResult();
    }

    // End MPI
    MPI_Finalize();
}
