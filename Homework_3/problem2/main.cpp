/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 9/10/2019
Description:
 Main file for problem 2 homework 2. Executes the program
*/

#include "grid.hpp"
#include <iostream>

/**
 * @\class
 * Main function that executes the program
 * @return Exit status
 */
int main(int argc, char *argv[])
{
    char filename[50];

    if(argc < 2 || argc > 2)
    {
        std::cerr << "Error with arguments: Make sure to include only on extra argument which is the filename" << std::endl;
        exit(1);
    }
    sprintf(filename, "%s", argv[1]);

    Grid grid = Grid(filename);

    grid.findMaxProductNeighbors();
    return 0;
}

