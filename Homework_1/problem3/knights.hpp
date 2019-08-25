/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 8/24/2019
Description:
 Stores a bunch of knights that want to be seated
*/

#ifndef HOMEWORK_1_KNIGHTS_HPP
#define HOMEWORK_1_KNIGHTS_HPP

#include <array>
#include <memory>

#include "fib_helper.hpp"
#include "knight.hpp"

/**
 * Class stores a bunch of knights that want to be seated. It also
 *  stores functions related to managing the knights
 */
class Knights {
public: // Methods
    /**
     * Constructor which allows passing in the fib helper
     * @param fib_helper A shared pointer to the fib helper
     */
    explicit Knights(const std::shared_ptr<FibHelper>& fib_helper);

    /**
     * Given a number of knights to seat, determines the appropriate seating order
     * @param knights_num The number of knights to seat
     */
    void determineSeatingOrder(unsigned int knights_num);

public: // Members
    /**
     * Stores the current seating order
     */
    std::array<unsigned int, Knight::max_number_of_knights> seating_order{{0}};

    /**
     * Stores the current index to which the seating order is valid
     */
    unsigned int seating_index{0};

private: // Methods
    /**
     * Initialize the knights depending on the number that
     *  want to be seated
     * @param num_knights The number of knights that are going to
     * be seated
     */
    void initializeKnights(unsigned int num_knights);

    /**
     * Given a seated knight and a potential neighbor, determines if that neighbor
     *  is a valid neighbor
     * @param already_seated The knight that is already seated that is looking for a neighbor
     * @param potential_neighbor A potential knight that is being tested to see if it can sit next
     *  to the already seated knight
     * @return True -> The neighbor can sit next to the already seated knight
     *         False -> The neighbor is not a valid neighbor
     */
    bool determineValidSeating(const Knight &already_seated,const Knight &potential_neighbor);

    /**
     * Given a seated knight, the function tries to find a suitable neighbor and seats them
     *  if it finds one
     * @param seated_knight The knight that was just seated
     * @return True -> There is a valid neighbor that was seated
     *         False -> The knight has no valid neighbors
     */
    bool findNeighbor(Knight &seated_knight);

private: // Members
    /**
     * Stores all the potential knights that can be seated. Actual
     *  number of knights seated is dependent on what the num_knights
     *  is initialized to
     */
    std::array<Knight, Knight::max_number_of_knights> knights;

    /**
     * Stores the number of knights that want to be seated
     */
    unsigned int num_knights{0};

    /**
     * Stores the length of the char for the seating string
     */
    static constexpr int max_seating_char_length=100;
};


#endif //HOMEWORK_1_KNIGHTS_HPP
