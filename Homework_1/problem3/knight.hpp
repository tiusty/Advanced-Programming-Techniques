/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 8/24/2019
Description:
 Contains the functionality and data related to a single knight
*/

#ifndef HOMEWORK_1_KNIGHT_HPP
#define HOMEWORK_1_KNIGHT_HPP

#include <array>
#include <memory>

#include "fib_helper.hpp"

/**
 * Stores an single instance of a knight and its properties
 */
class Knight {
public: // Methods

    /**
     * Sets all the valid neighbors for the given knight
     * @param numKnights The number of knights trying to be seated
     */
    void setValidFibPairs(unsigned int numKnights);

public: // Members
    /**
     * Stores the maximum number of knights that can be tried to be
     * seated
     */
    static constexpr int kMaxNumberOfKnights{30};

    /**
     * An array of the possible valid knights that can be neighbors
     */
    std::array<unsigned int, Knight::kMaxNumberOfKnights> validKnights{{0}};

    /**
     * The number of valid knights that there are
     */
    unsigned int numValidKnights{0};

    /**
     * The seat number associated with the knight
     */
    unsigned int seatNum{0};

    /**
     * Determines if the knights seating position has been found
     */
    bool found{false};

    /**
     * The fib helper which provides some helper methods/data
     */
    std::shared_ptr<FibHelper> fibHelper;
};


#endif //HOMEWORK_1_KNIGHT_HPP
