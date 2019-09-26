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
int main()
{
    Grid grid = Grid("data_Problem2.txt");
    grid.findMaxProductNeighbors();
    return 0;
}

