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

class Node {
public: // Methods
    Node() = default;
    explicit Node(int value);

public: // Members
    int value{0};
    int sumWithNode{0};
    std::shared_ptr<Node> pathToParent;
};


#endif //HOMEWORK_2_NODE_HPP
