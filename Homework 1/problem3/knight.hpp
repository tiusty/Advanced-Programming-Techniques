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

    /**
     * Sets all the valid neighbors for the given knight
     * @param num_knights The number of knights trying to be seated
     */
    void setValidFibPairs(unsigned int num_knights);

public: // Members
    /**
     * Stores the maximum number of knights that can be tried to be
     * seated
     */
    static constexpr int max_number_of_knights{30};

    /**
     * An array of the possible valid knights that can be neighbors
     */
    std::array<unsigned int, Knight::max_number_of_knights> valid_knights{0};

    /**
     * The number of valid knights that there are
     */
    unsigned int num_valid_knights{0};

    /**
     * The seat number associated with the knight
     */
    unsigned int seat_num{0};

    /**
     * Determines if the knights seating position has been found
     */
    bool found{false};

    /**
     * The fib helper which provides some helper methods/data
     */
    std::shared_ptr<FibHelper> fib_helper;
};


#endif //HOMEWORK_1_KNIGHT_HPP
