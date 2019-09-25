/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 9/25/2019
Description: 
    Implements functionality for lattice class
 */

#include "lattice.h"

Lattice::Lattice(unsigned int height, unsigned int width)
: latHeight(height), latWidth(width)
{
    if(numLatNodes() > maxLatElem)
    {
        throw std::out_of_range("Max Lat Element is less than # of elements. Please increase constexpr to run");
    }
}

unsigned int Lattice::numLatNodes()
{
    return (latHeight + 1)*(latWidth+1);
}


unsigned int Lattice::getNode(unsigned int row, unsigned int col)
{
    int rowSigned = row;
    // Row and col are base 1
    if(row < 1 or col < 1)
    {
        throw std::out_of_range("Row and col must be greater than 0");
    }
    if(col < row)
    {
        throw std::out_of_range("This index does not exist since we are only storing top half of matrix");
    }
    if(row > latHeight || col > latWidth)
    {
        throw std::out_of_range("The desired index is out of range for current lattice");
    }

    // In the first row case, the row-2 will become -1 which will still equate to 0, so this still works. Though
    //  we need to make sure the value is signed to allow negative numbers

    // Given that we are only storing the top half of the wide matrix (or square) we need to easily retrieve
    //  the node corresponding to the index we want.
    return ((rowSigned - 1) * latWidth -   // Add nodes from rows above
            ((rowSigned - 2) * (rowSigned - 2) +  (rowSigned - 2)) / 2) + // Due to symmetry get rid of extra nodes that don't exist
           (col - 1 - (row - 1)); // Adjust due to column but also since first node is the diagonal element, shift more
}

