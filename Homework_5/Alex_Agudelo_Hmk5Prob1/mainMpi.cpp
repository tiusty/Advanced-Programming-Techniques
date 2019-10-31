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
    double sendArray[7];
    double* pGatherBuffer;

    int duration{0};


    MPI_Init(&argc, &argv);


    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
    MPI_Get_processor_name(hostname, &len);

    printf("Hello from task %d on %s!\n", taskid, hostname);
    pGatherBuffer = new double[7*8];

    if (taskid == MASTER)
        printf("MASTER: Number of MPI tasks is: %d\n", numtasks);

    int counter = 1;
    for(int i=0; i<3; i++)
    {
        if(taskid == MASTER)
        {
            for(int i=0; i<7; i++)
            {
                sendArray[i] = counter*i*(taskid+1);
            }
            MPI_Allgather(sendArray, 7, MPI_DOUBLE, pGatherBuffer, 7, MPI_DOUBLE, MPI_COMM_WORLD);
            printf("Master got");
            for(int i=0; i<7*8; i++)
            {
                printf("%d ", pGatherBuffer[i]);
            }
            printf("\n");
        }
        else
        {

            for(int i=0; i<7; i++)
            {
                sendArray[i] = counter*i*(taskid+1);
            }
            sendArray[6] += .2;
            MPI_Allgather(sendArray, 7, MPI_INT, pGatherBuffer, 7, MPI_INT, MPI_COMM_WORLD);
        }
        counter++;
    }

    MPI_Finalize();
}

