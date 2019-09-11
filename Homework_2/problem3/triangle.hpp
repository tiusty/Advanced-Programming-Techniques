/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 9/11/2019
Description: 
*/

#ifndef HOMEWORK_2_TRIANGLE_HPP
#define HOMEWORK_2_TRIANGLE_HPP

#include <vector>

class Triangle {
public: // Methods
    Triangle() = default;
    explicit Triangle(const char* filename);
public: // Members
    std::vector<int> triangle;
    unsigned int numLevels;

};


#endif //HOMEWORK_2_TRIANGLE_HPP
