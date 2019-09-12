/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 9/11/2019
Description: 
*/

#ifndef HOMEWORK_2_TRIANGLE_HPP
#define HOMEWORK_2_TRIANGLE_HPP

#include <vector>

#include "node.hpp"

class Triangle {
public: // Methods
    Triangle() = default;
    explicit Triangle(const char* filename);
    bool determineValidIndex(nodeIndex index);
    void determineLargestParent(Node &nodeToCheck);
    const Node& getLargestParent(const Node &nodeToCheck);
    const Node& getNode(unsigned int row, unsigned column);
    void getLargestSum();
public: // Members
    std::vector<Node> triangle;
    unsigned int numLevels{0};

};


#endif //HOMEWORK_2_TRIANGLE_HPP
