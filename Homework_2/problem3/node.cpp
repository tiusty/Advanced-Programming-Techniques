/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 9/11/2019
Description: 
*/

#include "node.hpp"

#include <utility>

Node::Node(int value, nodeIndex index)
: value(value), index(std::move(index))
{}
