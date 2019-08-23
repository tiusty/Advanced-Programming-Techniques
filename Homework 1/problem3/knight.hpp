/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 8/23/2019
Description: 
*/

#ifndef HOMEWORK_1_KNIGHT_HPP
#define HOMEWORK_1_KNIGHT_HPP

#include <array>
#include <memory>
#include "fib_helper.hpp"

class Knight {
public: // Methods
    void setValidFibPairs();
public: // Members
    static constexpr int max_number_of_knights{100};
    std::array<unsigned int, max_number_of_knights> valid_knights{0};
    unsigned int num_valid_knights{0};
    unsigned int seat_num{0};
    bool found{false};
    std::shared_ptr<FibHelper> fib_helper;


};


#endif //HOMEWORK_1_KNIGHT_HPP
