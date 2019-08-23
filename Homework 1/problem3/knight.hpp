/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 8/23/2019
Description: 
*/

#ifndef HOMEWORK_1_KNIGHT_HPP
#define HOMEWORK_1_KNIGHT_HPP

#include <array>

class Knight {
    static constexpr int max_number_of_knights{10000};
    std::array<bool, max_number_of_knights> knight{false};
};


#endif //HOMEWORK_1_KNIGHT_HPP
