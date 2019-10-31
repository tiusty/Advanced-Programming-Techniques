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
    pWorldData = new double[numWorldElements];

    if(taskid == MASTER)
    {
        world.loadData();
        world.getWorldData(pWorldData);
    }
    MPI_Bcast(pWorldData, numWorldElements, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);
    world.setWorldData(pWorldData);

    if(taskid == 1)
    {
        std::cout << "printing world data" << std::endl;
        for(int i=0; i<numWorldElements; i++)
        {
            std::cout << pWorldData[i] << " ";
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);

    int counter = 1;
    for(int i=0; i<3; i++)
    {
        if(taskid == MASTER)
        {
            for(int i=0; i<7; i++)
            {
                shipData[i] = counter*i*(taskid+1);
            }
            MPI_Allgather(shipData, 7, MPI_DOUBLE, pWorldData, 7, MPI_DOUBLE, MPI_COMM_WORLD);
            printf("Master got");
            for(int i=0; i<7*8; i++)
            {
                std::cout << pWorldData[i] << " ";
            }
            std::cout << std::endl;
        }
        else
        {

            for(int i=0; i<7; i++)
            {
                shipData[i] = counter*i*(taskid+1);
            }
            shipData[6] += .2;
            MPI_Allgather(shipData, 7, MPI_DOUBLE, pWorldData, 7, MPI_DOUBLE, MPI_COMM_WORLD);
        }
        counter++;
    }

    MPI_Finalize();
}

