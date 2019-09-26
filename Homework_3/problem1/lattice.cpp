/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 9/25/2019
Description: 
    Implements functionality for lattice class
 */

#include <iostream>
#include "lattice.h"
#include <omp.h>
#include <sstream>
#include <fstream>

Lattice::Lattice(unsigned int height, unsigned int width)
: latHeight(height), latWidth(width)
{

    // Support tall matrices by transposing it since we only work on the upper triangle of the lattice
    if (height > width)
    {
        latHeight = width;
        latWidth = height;
    }

    // Store number of nodes
    latHeightNodes = latHeight + 1;
    latWidthNodes = latWidth + 1;

    // Protect against too many elements
    if(numLatNodes() > maxLatElem)
    {
        throw std::out_of_range("Max Lat Element is less than # of elements. Please increase constexpr to run");
    }

}

unsigned int Lattice::numLatNodes()
{
    return latHeightNodes * latWidthNodes;
}


unsigned int Lattice::getNode(unsigned int row, unsigned int col)
{
    // Need a signed row
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
    if(row > latHeightNodes || col > latWidthNodes)
    {
        throw std::out_of_range("The desired index is out of range for current lattice");
    }

    // In the first row case, the row-2 will become -1 which will still equate to 0, so this still works. Though
    //  we need to make sure the value is signed to allow negative numbers

    // Given that we are only storing the top half of the wide matrix (or square) we need to easily retrieve
    //  the node corresponding to the index we want.
    return ((rowSigned - 1) * latWidthNodes -   // Add nodes from rows above
            ((rowSigned - 2) * (rowSigned - 2) +  (rowSigned - 2)) / 2) + // Due to symmetry get rid of extra nodes that don't exist
           (col - 1 - (row - 1)); // Adjust due to column but also since first node is the diagonal element, shift more
}

unsigned long long int Lattice::getParentSum(unsigned int row, unsigned int col)
{
    unsigned long long int sumLeft{0};
    unsigned long long int sumUp{0};

    // Case to support the first element
    if(row == 1 and col == 1)
    {
        return 1;
    }

    // Get the sum from the left element
    if (row != col || col > row)
    {
        sumLeft = latNodes.at(getNode(row, col - 1));
    }

    // Get the sum from the up element
    if(row > 1)
    {
        // If statement which determines if multi-threading is used. If it is, then this busy loop is necessary
        if (openMPSupport)
        {
            // Busy loop waiting for the element above to get populated by a different thread
            while(latNodes.at(getNode(row -1, col)) == 0);
        }

        // Actually retrieve the value
        sumUp = latNodes.at(getNode(row - 1, col));
        // In the case that the element is on the diagonal,
        //  then the sum is twice the up element
        if(row == col)
        {
            sumUp *= 2;
        }
    }

    // Return the sum of the parents
    return sumLeft + sumUp;
}

void Lattice::findNumberOfPaths()
{
    if(openMPSupport)
    {
        findNumberOfPathsOpenMp();
    } else {
        findNumberOfPathsSingleThread();
    }
    outputResults();
}

void Lattice::findNumberOfPathsSingleThread()
{
    for (unsigned int i = 1; i < latHeightNodes + 1; i++) {
        for (unsigned int j = i; j < latWidthNodes + 1; j++) {
            latNodes.at(getNode(i, j)) = getParentSum(i, j);
        }
    }
}

void Lattice::findNumberOfPathsOpenMp()
{
    // Sum the upper triangle of the lattice
    omp_set_num_threads(2);
#pragma omp parallel for schedule(dynamic)
        for (unsigned int i = 1; i < latHeightNodes + 1; i++) {
            for (unsigned int j = i; j < latWidthNodes + 1; j++) {
                latNodes.at(getNode(i, j)) = getParentSum(i, j);
            }
        }
}

void Lattice::outputResults()
{
    std::cout << "Number of Routes: " << latNodes.at(getNode(latHeightNodes, latWidthNodes));
    std::ofstream file(outputFileName);
    // Open file and write result to the file
    if(file.is_open())
    {
        file << latNodes.at(getNode(latHeightNodes, latWidthNodes));
        file.close();
    }
}



