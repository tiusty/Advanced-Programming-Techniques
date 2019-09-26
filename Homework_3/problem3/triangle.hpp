/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 9/11/2019
Description:
 Class stores a vector of values that represent a triangle and preforms operations on it
*/

#ifndef HOMEWORK_2_TRIANGLE_HPP
#define HOMEWORK_2_TRIANGLE_HPP

#include <vector>

#include "node.hpp"

/**
 * Stores values for triangles and helps determine the largest sum
 */
class Triangle {
public: // Methods
    /**
     * Default ctor for an empty triangle class
     */
    Triangle() = default;
    /**
     * Loads data from a file given by the filename into the triangle vector
     * @param filename The filename to load from
     */
    explicit Triangle(const char* filename);
    /**
     * Determines if a given node index is valid
     *  A node index needs to follow the triangle format of row , column starting from base 1
     * @param index The index to check
     * @return True -> The index is valid
     *         False -> The index is not valid
     */
    bool determineValidIndex(nodeIndex index);
    /**
     * Determines the largest parent of a node and then saves that parent to the node with its sum
     * @param nodeToCheck The child node being checked
     */
    void determineLargestParent(Node &nodeToCheck);
    /**
     * Retrieves a node from the triangle vector given a row and column. Makes it easier
     *  to look up a particular entry of the triangle
     * @param row The row the node is on
     * @param column The column of the node in the row
     * @return A const reference to the node being referenced
     */
    const Node& getNode(unsigned int row, unsigned column);
    /**
     * Main run function which executes the functionality for finding the largest sum
     */
    void getLargestSum();
    /**
     * Print the output sum to a file
     */
    void generateOutput(int largestSum);
public: // Members
    /**
     * Stores the data for all the nodes
     */
    std::vector<Node> triangle;
    /**
     * Determines the number of levels that the triangle has
     */
    unsigned int numLevels{0};
    /**
     * Constexpr for the output file name
     */
    static constexpr const char* outputFileName{"output3.txt"};
};


#endif //HOMEWORK_2_TRIANGLE_HPP
