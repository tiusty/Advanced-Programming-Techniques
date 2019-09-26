/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 9/10/2019
Description:
 Implements the Grid functionality
*/

#include "grid.hpp"

#include <fstream>
#include <iostream>
#include <array>
#include <omp.h>

// Define constexpr terms
constexpr unsigned int Grid::numAdjNeighbors;
constexpr const char* Grid::outputFileName;

Grid::Grid(const char* filename)
{
    std::ifstream file(filename);

    if(!file)
    {
        std::cerr << "Cannot open file" << std::endl;
        exit(1);
    }

    std::string line;

    // Read in the row and column number
    file >> numRows >> numColumns;
    std::getline(file, line);

    // Reserve the vector size for the number of rows
    matrix.reserve(numRows);

    // Read in every gridElement to a new spot in the data
    for(unsigned int i=0; i < numRows; i++)
    {
        matrix.emplace_back(numColumns, 0);
        for(unsigned int j=0; j < numColumns; j++)
        {
            // Store the element in the matrix
            file >> matrix.at(i).at(j);
            // Add the element to the priority queue
            restOfElements.push(std::make_pair(std::make_pair(i, j), matrix.at(i).at(j)));
        }
    }

    // Add the first numAdjNeighbors to the topAdjElements and remove them from the restofElements
    for(int i=0; i < numAdjNeighbors; i++)
    {
        // Compute the maxPossibleProduct based on the elements in the topAdjElements
        maxPossibleProduct *= restOfElements.top().second;
        topAdjElements.push(restOfElements.top());
        restOfElements.pop();
    }
}

void Grid::findMaxProductNeighbors()
{
    // Loop until the restOfElements queue is empty, aka there are no more elements to check
    // Hopefully it will quit before hand via the break
    while(!restOfElements.empty())
    {
        // Pull off largest element

        // Check 4 directions. The negative and positive of each vector is checked to
        //  fully check all "8" directions. For me x axis is up and down and y axis is left
        //  to right

#pragma omp parallel default(none) shared(currentLargestProduct, indexMaxProduct)
        {
            gridElement elementToCheck = topAdjElements.top();
#pragma omp sections
            {
                // Check right down to left up diagonal
#pragma omp section
                largestProductAlongLine(1, -1, elementToCheck);
                // Check Up/Down line
#pragma omp section
                largestProductAlongLine(1, 0, elementToCheck);
                // Check left/right line
#pragma omp section
                largestProductAlongLine(0, 1, elementToCheck);
                // Check right up to left down diagonal
#pragma omp section
                largestProductAlongLine(1, 1, elementToCheck);
            }
        }

        // The current max is the largest product found so far while searching
        // The maxPossibleProduct is the product of the elements in the topAdjElements,
        //   Aka if all the largest remaining numbers were put next to each other.
        if(currentLargestProduct > maxPossibleProduct)
        {
            // If the current max is larger than any potential remaining
            //  maxPossibleProducts then the solution is found and we can quit
            break;
        }
        else
        {
            // If there still can be a larger max product then we will loop to check the next largest element

            // Steps:
            // 1. Divide out the current number being checked and remove it from the priority queue
            // 2. Multiple the maxPossibleProduct by the new number being added to the topAdjElements queue
            // 3. Remove that new element from the restOfElements queue and added it to the topAdjElements queue
            maxPossibleProduct /= topAdjElements.top().second;
            topAdjElements.pop();
            maxPossibleProduct *= restOfElements.top().second;
            topAdjElements.push(restOfElements.top());
            restOfElements.pop();
        }
    }

    // Print start and end index to the console
    std::cout << "Solution starts at: "
                 " Start index: (" << indexMaxProduct.at(0).first << "," << indexMaxProduct.at(0).second <<
              ") End index: ("<< indexMaxProduct.at(1).first << "," << indexMaxProduct.at(1).second << ")." << std::endl;
    generateOutput();
}

void Grid::largestProductAlongLine(int xNormVec, int yNormVec, gridElement elementToCheck)
{
    // Given a vector of a line to check, check every possible combination along that line
    // and fine the largest product on that line. Since we are checking with respect to an element
    //  that element must be in contained within the indices
    gridIndex initIndex = elementToCheck.first;

    // Starts at the far end of the line and then shifts down one element at a time checking the product
    //  each time. This will shift from the start_index being the elementToCheck until the element to check
    //  is the endIndex
    for(int i=0; i < numAdjNeighbors; i++)
    {
        // Get the start index and end index of the line being checked
        gridIndex startIndex = std::make_pair(initIndex.first - i * xNormVec, initIndex.second - i * yNormVec);
        gridIndex endIndex = std::make_pair(initIndex.first + xNormVec * (numAdjNeighbors - 1) - i * xNormVec,
                                            initIndex.second + yNormVec * (numAdjNeighbors - 1) - i * yNormVec);
        // Determines the product between the two indices
        long long unsigned int product = productBetweenIndices(startIndex, endIndex);
        // If the product is larger than the current max then save it, and save the start and end indices
#pragma omp critical
        {
            if (product > currentLargestProduct) {
                currentLargestProduct = product;
                indexMaxProduct.at(0) = startIndex;
                indexMaxProduct.at(1) = endIndex;
            }
        }
    }
}

long long unsigned int Grid::productBetweenIndices(gridIndex startIndex, gridIndex endIndex)
{
    // Set up variables and determine normalized vectors
    long long unsigned int product = 1;
    int xVector = endIndex.first - startIndex.first;
    // xNormVec determines the direction that x iterates
    // xNormVec stands for normalized vector
    // I.e
    // If it is zero then x won't change because the vector is incrementing along the y axis
    // If is it 1, then it increments along the x-axis
    // If it is -1, then it decrements along the x-axis
    int xNormVec{0};
    if(xVector !=0)
    {
        xNormVec = xVector / abs(xVector);
    }
    int yVector = endIndex.second - startIndex.second;
    // yNormVec norm performs the same as xNormVec but w.r.t to the y vector
    int yNormVec{0};
    if(yVector !=0)
    {
        yNormVec = yVector / abs(yVector);
    }

    // Since it must be up/down, left/right or diagonal, we can test to make sure that is the case
    if ((xNormVec == 0 and yNormVec == 0) or (abs(xNormVec) > 1 or abs(yNormVec) > 1))
    {
        std::cerr << " Error: Attempted to find product between matrices not on a line"
                     " Start index: (" << startIndex.first << "," << startIndex.second <<
                     ") End index: ("<< endIndex.first << "," << endIndex.second << ")." << std::endl;
        exit(1);
    }

    // Goes through and multiples the elements along the line between the start index and
    //  the end index
    for(int i=0; i<=std::max(abs(xVector), abs(yVector)); i++)
    {
        int xIndex = startIndex.first + xNormVec * i;
        int yIndex = startIndex.second + yNormVec * i;
        // If any of the indices become invalid then make the product 0 since it is not a valid
        //  solution and return
        if(xIndex < 0 or yIndex < 0 or xIndex >= numRows or yIndex >= numColumns)
        {
            product = 0;
            continue;
        }
        product*=matrix.at(xIndex).at(yIndex);
    }

    return product;
}

void Grid::generateOutput()
{
    std::ofstream file(outputFileName);
    if(file.is_open())
    {
        file << currentLargestProduct;
        file.close();
    }
}
