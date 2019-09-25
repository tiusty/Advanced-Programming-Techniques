/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 9/25/2019
Description: 
    Implements functionality for lattice class
 */

#include "lattice.h"

#include <iostream>

Lattice::Lattice(unsigned int height, unsigned int width)
: latHeight(height), latWidth(width)
{
    if(numLatNodes() > maxLatElem)
    {
        std::cerr << "Max Lat Element is less then # of elements. Please increase the constexpr to run" << std::endl;
        exit(1);
    }
}

unsigned int Lattice::numLatNodes()
{
    return (latHeight + 1)*(latWidth+1);
}