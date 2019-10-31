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
#define  MASTER		0

int main(int argc, char *argv[])
{
    int   numtasks, taskid, len;
    char hostname[MPI_MAX_PROCESSOR_NAME];
    std::array<int,6> sendArray;

    int duration{0};


    MPI_Init(&argc, &argv);


    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
    MPI_Get_processor_name(hostname, &len);

    printf("Hello from task %d on %s!\n", taskid, hostname);

    if (taskid == MASTER)
        printf("MASTER: Number of MPI tasks is: %d\n", numtasks);

    for(int i=0; i<2; i++)
    {
        if(taskid == MASTER)
        {
            std::array<int, 6*8> rbuf{0};
            for(int i=0; i<6; i++)
            {
                sendArray.at(i) = i*taskid;
            }
            MPI_Allgather(static_cast<void*>(sendArray.data()), 6, MPI_INT, static_cast<void*>(rbuf.data()), 6*8, MPI_INT, MPI_COMM_WORLD);
            printf("Master got");
            for(int i=0; i<6*8; i++)
            {
                printf("%d", rbuf.at(i));
            }
            printf("\n");
        }
        else
        {

            std::array<int, 6*8> rbuf{0};
            for(int i=0; i<6; i++)
            {
                sendArray.at(i) = i*taskid;
            }
            MPI_Allgather(static_cast<void*>(sendArray.data()), 6, MPI_INT, static_cast<void*>(rbuf.data()), 6*8, MPI_INT, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
}

