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

using nodeIndex = std::pair<int, int>;

class Node {
public: // Methods
    Node() = default;
    explicit Node(int value, nodeIndex index);

public: // Members
    nodeIndex index;
    int value{0};
    int sumWithNode{0};
    std::shared_ptr<Node> pathToParent;
};


#endif //HOMEWORK_2_NODE_HPP
