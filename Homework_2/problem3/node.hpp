/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 9/11/2019
Description:
 Class encapsulates the functionality of a single node within the triangle
*/

#ifndef HOMEWORK_2_NODE_HPP
#define HOMEWORK_2_NODE_HPP

#include <memory>

// Stores a coordinate for a node
// <row, column>
using nodeIndex = std::pair<int, int>;

/**
 * Stores data regarding a single node in the triangle class
 */
class Node {
public: // Methods
    /**
     * Default ctor that make a blank node
     */
    Node() = default;
    /**
     * Defines a node given a value and its coordinates in the triangle
     */
    explicit Node(int value, nodeIndex index);

public: // Members
    /**
     * The index of the node
     */
    nodeIndex index;
    /**
     * The value that the node has
     */
    int value{0};
    /**
     * The sum up to and including the node. The sum up to is the max possible sum that can reach that node
     */
    int sumWithNode{0};
    /**
     * A pointer to the parent that had the max sum
     *  This allows recreating the path that was taken to give the max sum
     */
    std::shared_ptr<Node> pathToParent;
};


#endif //HOMEWORK_2_NODE_HPP
