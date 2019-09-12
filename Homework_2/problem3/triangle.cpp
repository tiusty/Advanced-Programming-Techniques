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

// Define constexpr terms
constexpr const char* Triangle::outputFileName;

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

    // Read in every node into the triangle
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
    // Make sure the index is values are valid
    // Throw is mostly used for checking in the unittests
    if(not determineValidIndex(std::make_pair(row, column)))
    {
        throw std::out_of_range("Indices are not valid");
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
    // We are assuming the first element is at (1,1)
    if(index.first < 1 || index.second < 1)
    {
        result = false;
    }
    // The column needs to be equal to or less than the row to be valid
    if(index.second > index.first)
    {
        result = false;
    }
    return result;
}

void Triangle::determineLargestParent(Node &nodeToCheck)
{
    // Stores a pointer to the largest parent
    std::shared_ptr<Node> largestParent = nullptr;

    // Get the indices for the two possible parent nodes
    nodeIndex parentLeft = std::make_pair(nodeToCheck.index.first - 1, nodeToCheck.index.second - 1);
    nodeIndex parentRight = std::make_pair(nodeToCheck.index.first -1, nodeToCheck.index.second);

    // If the left index is valid then save that parent as the largest
    if(determineValidIndex(parentLeft))
    {
        largestParent = std::make_shared<Node>(getNode(parentLeft.first, parentLeft.second));
    }

    // If the right index is valid, and is larger than the left index(if it exists) then make it the largest parent
    if(determineValidIndex(parentRight))
    {
        std::shared_ptr<Node> parentRightNode = std::make_shared<Node>(getNode(parentRight.first, parentRight.second));
        // If the left parent wasn't valid then make right parent the largest parent
        if(largestParent == nullptr)
        {
            largestParent = parentRightNode;
        }
        // If the right parent has a largest sum than left, then switch the largest parent
        else if(largestParent->sumWithNode < parentRightNode->sumWithNode)
        {
            largestParent = parentRightNode;
        }
    }

    // Make sure that there exists a larger parent
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

    // Output result to file
    generateOutput(largestSum);
}

void Triangle::generateOutput(int largestSum)
{
    std::ofstream file(outputFileName);
    if(file.is_open())
    {
        file << largestSum;
        file.close();
    }
}
