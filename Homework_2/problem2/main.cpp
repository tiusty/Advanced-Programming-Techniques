/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 9/10/2019
Description:
 Main file for problem 2 homework 2. Executes the program
*/

#include "grid.hpp"

/**
 * @\class
 * Main function that executes the program
 * @return Exit status
 */
int main(int argc, char *argv[])
{
    char filename[50];

    // Read in file name
    sprintf(filename, "%s", argv[1]);

    // Create grid based on filename
    Grid grid = Grid(filename);

    // Find max product of neighbors
    grid.findMaxProductNeighbors();
    return 0;
}

