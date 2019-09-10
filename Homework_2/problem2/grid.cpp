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
        }
    }
}

void Grid::updateMaxPossibleProduct(int value, std::priority_queue<int, std::vector<int>, std::greater<> > &productNums)
{
    if(productNums.size() < numAdjNumbers)
    {
        productNums.push(value);
    }
    else
    {
        if (value > productNums.top())
        {
            // Remove the old element and remove it from the maxPossibleProduct
            int removedElement = productNums.top();
            productNums.pop();
            maxPossibleProduct /= removedElement;

            // Add in the new element and add it to the product
            productNums.push(value);
            maxPossibleProduct *= value;
        }
    }
}
