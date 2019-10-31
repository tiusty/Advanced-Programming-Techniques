/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 10/31/19
Description: 
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <array>

#include "mpi.h"
#include "world.hpp"
#define  MASTER		0

int main(int argc, char *argv[])
{
    int   numtasks, taskid, len, rc;
    char hostname[MPI_MAX_PROCESSOR_NAME];
    double shipData[World::elementsPerShip];
    double* pWorldData;

    int duration{0};


    MPI_Init(&argc, &argv);


    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
    MPI_Get_processor_name(hostname, &len);

    printf("Hello from task %d on %s!\n", taskid, hostname);

    // Set up variables for all MPI processes
    World world;
    int numWorldElements = world.elementsPerShip*numtasks;
    int miscData[2]{0};
    pWorldData = new double[numWorldElements];

    if(taskid == MASTER)
    {
        world.loadData();
        world.getWorldData(pWorldData);
        miscData[0] = world.maxForce;
        miscData[1] = world.duration;
    }
    MPI_Bcast(pWorldData, numWorldElements, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);
    world.setWorldData(pWorldData);
    MPI_Bcast(miscData, 2, MPI_INT, MASTER, MPI_COMM_WORLD);
    world.maxForce = miscData[0];
    world.duration = miscData[1];

    for(int i=0; i<world.duration; i++)
    {
        if(taskid == MASTER)
        {
            world.evolveSystem(world.buzzy);
//            printf("Before all gather master on %s!\n", taskid, hostname);
            MPI_Allgather(shipData, 7, MPI_DOUBLE, pWorldData, 7, MPI_DOUBLE, MPI_COMM_WORLD);
        }
        else
        {
            int shipNum = taskid -1;
            // Calculate and set forces for each yellow jacket
            world.handleYellowJacket(world.fighters.at(shipNum), i);

            // Evolve the world
            world.evolveSystem(world.fighters.at(shipNum));

            // Return the ship data for this process
            world.getShipData(shipData, shipNum);

            // Wait for everyone to send the data
//            printf("Before all gather task %d on %s!\n", taskid, hostname);
            MPI_Allgather(shipData, 7, MPI_DOUBLE, pWorldData, 7, MPI_DOUBLE, MPI_COMM_WORLD);

            // Update the world with the new data
            world.setWorldData(pWorldData);

            // Check the conditions to see if any fighters crashed etc
            world.checkConditions(world.fighters.at(shipNum));
        }
    }

    if(taskid == MASTER)
    {
        world.printResult();
    }
    MPI_Finalize();
}

