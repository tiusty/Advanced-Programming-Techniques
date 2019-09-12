/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 9/11/2019
Description:
 Implements triangle funtionality
*/

#include "triangle.hpp"

#include <fstream>
#include <memory>
#include <iostream>
#include <exception>

Triangle::Triangle(const char* filename)
{
    std::ifstream file(filename);

    if(!file)
    {
        std::cerr << "Cannot open file" << std::endl;
        exit(1);
    }

    // Read in the row and column number
    file >> numLevels;

    // Reserve the vector size for the number of nodes based on the number
    // of levels using the nth triangular number
    unsigned int numNodes = (numLevels*(numLevels + 1))/2;
    triangle.reserve(numNodes);

    // Read in every gridElement to a new spot in the data
    unsigned int currRow{1};
    unsigned int currColumn{1};
    for(unsigned int i=0; i < numNodes; i++)
    {
            // Store the element in the matrix
            int value;
            file >> value;
            triangle.emplace_back(value, std::make_pair(currRow, currColumn));
            if(currColumn >= currRow)
            {
                currRow++;
                currColumn = 1;
            }
            else
            {
                currColumn++;
            }
    }
}

const Node& Triangle::getNode(unsigned int row, unsigned column)
{
    unsigned int nodeIndex{0};
    if (row < 1)
    {
        std::cerr << "Error: Attempted to get row less than 1: " << row << std::endl;
        throw std::out_of_range("Row out of range in getNode");
    }
    if (column > row || column < 1)
    {
        std::cerr << "Error: Attempted to get column :" << column << std::endl;
        std::cerr << "That is not valid, must be greater than 0 and less than or equal to the row number" << std::endl;
        throw std::out_of_range("Column out of range in getNode");
    }

    // Get number of elements before the desired row
    nodeIndex = ((row-1)*((row-1) + 1))/2;
    // Add the column index to get the desired node
    nodeIndex += column;

    // Since indices for row 1, column 1 should start at 0, not 1
    nodeIndex-=1;

    return triangle.at(nodeIndex);
}

bool Triangle::determineValidIndex(nodeIndex index)
{
    bool result{true};
    if(index.first < 1 || index.second < 1)
    {
        result = false;
    }
    if(index.second > index.first)
    {
        result = false;
    }
    return result;
}

void Triangle::determineLargestParent(Node &nodeToCheck)
{
    std::shared_ptr<Node> largestParent = nullptr;

    nodeIndex parentLeft = std::make_pair(nodeToCheck.index.first - 1, nodeToCheck.index.second - 1);
    nodeIndex parentRight = std::make_pair(nodeToCheck.index.first -1, nodeToCheck.index.second);

    if(determineValidIndex(parentLeft))
    {
        largestParent = std::make_shared<Node>(getNode(parentLeft.first, parentLeft.second));
    }
    if(determineValidIndex(parentRight))
    {
        std::shared_ptr<Node> parentRightNode = std::make_shared<Node>(getNode(parentRight.first, parentRight.second));
        if(largestParent == nullptr)
        {
            largestParent = parentRightNode;
        }
        else if(largestParent->sumWithNode < parentRightNode->sumWithNode)
        {
            largestParent = parentRightNode;
        }
    }

    if(largestParent != nullptr)
    {
        nodeToCheck.sumWithNode = nodeToCheck.value + largestParent->sumWithNode;
        nodeToCheck.pathToParent = largestParent;
    }
    else
    // Should only happen with first node since it has no parents
    {
        nodeToCheck.sumWithNode = nodeToCheck.value;
    }
}

void Triangle::getLargestSum()
{
    // Iterate through all nodes
    int largestSum{0};
    for(auto &n : triangle)
    {
        determineLargestParent(n);
        if(n.sumWithNode > largestSum)
        {
            largestSum = n.sumWithNode;
        }
    }

    // Find largest parent sum and save sum and path to last node
    std::cout << "hi" << std::endl;
}
