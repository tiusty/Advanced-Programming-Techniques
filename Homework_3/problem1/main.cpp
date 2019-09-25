/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 9/25/2019
Description:
 Main function for the program
*/

#include "lattice.h"

#include <iostream>

int main()
{
    Lattice lat(4,10);
    lat.findNumberOfPaths();
    return 1;
}
