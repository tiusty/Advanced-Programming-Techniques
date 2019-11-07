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
    // Master node will send data to all other processes
    //  All other processes will block here until master broadcasts the data
    MPI_Bcast(pWorldData, numWorldElements, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);

    // This is executed on all processes.
    // Given the pWorldData that every process received from master (including master itself)
    //  Use that data to initialize the world data locally for each process
    world.setWorldData(pWorldData);

    // Master process will send the MISC data to all other processes
    // Blocking call, that waits for all processes to call MPI_Bcast before moving on
    MPI_Bcast(miscData, 2, MPI_INT, MASTER, MPI_COMM_WORLD);

    // All processes will set the misc data locally
    world.maxForce = miscData[0];
    world.duration = miscData[1];

    // All processes will run the simulation locally for the allocated amount of time
    // This for loop stay syncronized by the MPI_Allgather.
    // MPI_Allgather blocks until all processes (including master) call the function.
    // Once all the processes call MPI_Allgather, they all receive the aggregated data from
    //  all the processes and continue executing
    for(int i=0; i<world.duration; i++)
    {
        // Master handles only the buzzy dynamics
        if(taskid == MASTER)
        {

            // Evolve buzzy location
            // Buzzy moves at constant speed so no need to calculate force
            world.evolveSystem(world.buzzy);

            // Get the data for buzzy
            world.getShipDataBuzzy(shipData);

            MPI_Allgather(shipData, 10, MPI_DOUBLE, pWorldData, 10, MPI_DOUBLE, MPI_COMM_WORLD);

            // Update the world with the new data
            world.setWorldData(pWorldData);

            // Print out fighter data each iteration
            for(int j=0; j<numtasks-1; j++)
            {
                Ship *fighter = &world.fighters.at(j);
                std::cout << std::scientific << std::setprecision(6);
                std::cout << j+1 << "," << fighter->status << "," << fighter->position.x << "," << fighter->position.y << "," << fighter->position.z << "," << fighter->force.x << "," << fighter->force.y << "," << fighter->force.z << std::endl;
            }
        }
        // Each of the other processes handles one of the yellow jackets (fighters)
        else
        {
            //The fighter num is determined by taskid
            int shipNum = taskid -1;

            // Calculate and set forces for the processes's yellow jacket
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

            // Since every process has the aggregated ship data from every other process
            //  Update the ;pca; process's world information from the data it received from all the other processes
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
    
    // Delete the dynamic memory on each process to prevent memory leak
    delete pWorldData;

    // End MPI
    MPI_Finalize();
}

