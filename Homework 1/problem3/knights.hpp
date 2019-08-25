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
    std::array<unsigned int, Knight::max_number_of_knights> seating_order{0};
    unsigned int seating_index{0};
    unsigned int num_knights{0};
    void determineSeatingOrder();
    bool foundKnightSeat(unsigned int found_knight);
    bool determineValidSeating(const Knight &already_seated,const Knight &potential_neighbor);
    bool findNeighbor(Knight &seated_knight);
    static constexpr int max_seating_char_length=100;
};


#endif //HOMEWORK_1_KNIGHTS_HPP
