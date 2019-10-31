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
    int sendArray[6];
    int* pGatherBuffer;

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
            pGatherBuffer = new int[6*8];
            for(int i=0; i<6; i++)
            {
                sendArray[i] = i*(taskid+1);
            }
            for(int i=0; i<6; i++)
            {
                printf("%d", sendArray[i]);
            }
            printf("\n");
            MPI_Allgather(sendArray, 6, MPI_INT, pGatherBuffer, 8, MPI_INT, MPI_COMM_WORLD);
            printf("Master got");
            for(int i=0; i<6*8; i++)
            {
                printf("%d", pGatherBuffer[i]);
            }
            printf("\n");
        }
        else
        {

            pGatherBuffer = new int[6*8];
            for(int i=0; i<6; i++)
            {
                sendArray[i] = i*(taskid+1);
            }
            printf("Task done %d on %s!\n", taskid, hostname);
            MPI_Allgather(sendArray, 6, MPI_INT, pGatherBuffer, 8, MPI_INT, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
}

