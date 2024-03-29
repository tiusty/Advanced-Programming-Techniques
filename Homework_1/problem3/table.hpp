/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 8/27/2019
Description:
 Stores a bunch of knights and corresponding helper functions for seating them
*/

#ifndef HOMEWORK_1_TABLE_HPP
#define HOMEWORK_1_TABLE_HPP

#include <array>
#include <memory>

#include "fib_helper.hpp"
#include "knight.hpp"

/**
 * Class stores a bunch of knights that want to be seated. It also
 *  stores functions related to managing the knights
 */
class Table {
public: // Methods
    /**
     * Constructor which allows passing in the fib helper
     * @param fibHelper A shared pointer to the fib helper
     */
    explicit Table(const std::shared_ptr<FibHelper>& fibHelper);

    /**
     * Given a number of knights to seat, determines the appropriate seating order
     * @param knightsNum The number of knights to seat
     */
    void determineSeatingOrder(unsigned int knightsNum);

public: // Members
    /**
     * Stores the current seating order
     * Stores in array to avoid using dynamic memory
     */
    std::array<unsigned int, Knight::kMaxNumberOfKnights> seatingOrder{{0}};

    /**
     * Stores the current index to which the seating order is valid
     */
    unsigned int seatingIndex{0};

private: // Methods
    /**
     * Initialize the knights depending on the number that
     *  want to be seated
     * @param numberKnights The number of knights that are going to
     * be seated
     */
    void initializeKnights(unsigned int numberKnights);

    /**
     * Given a seated knight and a potential neighbor, determines if that neighbor
     *  is a valid neighbor
     * @param alreadySeated The knight that is already seated that is looking for a neighbor
     * @param potentialNeighbor A potential knight that is being tested to see if it can sit next
     *  to the already seated knight
     * @return True -> The neighbor can sit next to the already seated knight
     *         False -> The neighbor is not a valid neighbor
     */
    bool determineValidSeating(const Knight &alreadySeated, const Knight &potentialNeighbor);

    /**
     * Given a seated knight, the function tries to find a suitable neighbor and seats them
     *  if it finds one
     * @param seatedKnight The knight that was just seated
     * @return True -> There is a valid neighbor that was seated
     *         False -> The knight has no valid neighbors
     */
    bool findNeighbor(Knight &seatedKnight);

    /**
     * Checks to see if there is a possible valid solution. If not then quit before checking combinations
     *  Used as an optimization to avoid checking for combinations if a combo cannot exist.
     * @return True -> There could potentially be a  possible solution
     *         False -> There could not be a valid solution
     */
    bool checkPossibleValidSolution();

private: // Members
    /**
     * Stores all the potential knights that can be seated. Actual
     *  number of knights seated is dependent on what the num_knights
     *  is initialized to
     * Stores in array to avoid using dynamic memory
     */
    std::array<Knight, Knight::kMaxNumberOfKnights> knights;

    /**
     * Stores the number of knights that want to be seated
     */
    unsigned int numKnights{0};

    /**
     * Stores the length of the char for the seating string
     */
    static constexpr int kMaxSeatingCharLength=100;
};


#endif //HOMEWORK_1_TABLE_HPP
