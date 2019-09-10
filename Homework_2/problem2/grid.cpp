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

// Define constexpr terms
constexpr unsigned int Grid::numAdjNumbers;

Grid::Grid(const char* filename)
{
    std::ifstream file(filename);
    std::priority_queue<int, std::vector<int>, std::greater<> > productNums;

    if(!file)
    {
        std::cerr << "Cannot open file" << std::endl;
        exit(1);
    }

    std::string line;

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
            file >> matrix.at(i).at(j);
            element_queue.push(std::make_pair(std::make_pair(i,j), matrix.at(i).at(j)));
            updateMaxPossibleProduct(matrix.at(i).at(j), productNums);
        }
    }
}

void Grid::findMaxProductNeighbors()
{
    // Pull off largest element
    gridElement elementToCheck = element_queue.top();

    // Check 4 directions

    // Within each direction check all combinations i.e all 4

    // Save the current max and indicies

    // At end, pop the largest element and find new maxPossible
    //  If current max > new maxPossible then all done
}

void Grid::largestProductAlongLine(int xVecNorm, int yVecNorm, gridElement elementToCheck)
{
    // Setup variables
    gridIndex initIndex = elementToCheck.first;
    for(int i=0; i<numAdjNumbers; i++)
    {
        gridIndex startIndex = std::make_pair(initIndex.first - i*xVecNorm, initIndex.second - i*yVecNorm);
        gridIndex endIndex = std::make_pair(initIndex.first + xVecNorm*(numAdjNumbers - 1) - i*xVecNorm, initIndex.second + yVecNorm*(numAdjNumbers -1) - i*yVecNorm);
        int product = productBetweenIndices(startIndex, endIndex);
        if( product > currentLargestProduct)
        {
            currentLargestProduct = product;
            indexMaxProduct.at(0) = startIndex;
            indexMaxProduct.at(1) = endIndex;
        }
    }
}

int Grid::productBetweenIndices(gridIndex startIndex, gridIndex endIndex)
{
    int product = 1;
    int xVector = endIndex.first - startIndex.first;
    int xVectorNorm{0};
    if(xVector !=0)
    {
        xVectorNorm = xVector/abs(xVector);
    }
    int yVector = endIndex.second - startIndex.second;
    int yVectorNorm{0};
    if(yVector !=0)
    {
        yVectorNorm = yVector/abs(yVector);
    }

    // Since it must be up/down, left/right or diagonal, we can test to make sure that is the case
    if ((xVectorNorm == 0 and yVectorNorm ==0) or (abs(xVectorNorm) > 1 or abs(yVectorNorm) > 1))
    {
        std::cerr << " Attempted to find product between matrices not on a line"
                     " Start index: (" << startIndex.first << "," << startIndex.second <<
                     ") End index: ("<< endIndex.first << "," << endIndex.second << ")." << std::endl;
        exit(1);
    }

    for(int i=0; i<=std::max(abs(xVector), abs(yVector)); i++)
    {
        // Goes through and multiples the elements along the line between the start index and
        //  the end index
        product*=matrix.at(startIndex.first + xVectorNorm*i).at(startIndex.second + yVectorNorm*i);
    }

    return  product;
}

void Grid::updateMaxPossibleProduct(int value, std::priority_queue<int, std::vector<int>, std::greater<> > &productNums)
{
    if(productNums.size() < numAdjNumbers)
    {
        productNums.push(value);
        if(value != 0)
        {
            maxPossibleProduct *= value;
        }
    }
    else
    {
        if (value > productNums.top())
        {
            // Remove the old element and remove it from the maxPossibleProduct
            int removedElement = productNums.top();
            productNums.pop();
            if(removedElement != 0)
            {
                maxPossibleProduct /= removedElement;
            }

            // Add in the new element and add it to the product
            productNums.push(value);
            if(value !=0)
            {
                maxPossibleProduct *= value;
            }
        }
    }
}
