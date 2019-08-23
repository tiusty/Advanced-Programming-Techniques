/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 8/23/2019
Description: 
*/

#ifndef HOMEWORK_1_KNIGHTS_HPP
#define HOMEWORK_1_KNIGHTS_HPP

#include <array>
#include <memory>
#include "fib_helper.hpp"
#include "knight.hpp"

class Knights {
public:
    Knights(const std::shared_ptr<FibHelper>& fib_helper);
    void initializeKnights(unsigned int num_knights);
    std::array<Knight, Knight::max_number_of_knights> knights;
    unsigned int num_knights{0};
};


#endif //HOMEWORK_1_KNIGHTS_HPP
