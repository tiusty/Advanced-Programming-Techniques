/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 8/24/2019
Description:
 A helper class which stores a cache of the fib numbers and
 also allows basic functionality with the fib numbers
*/

#ifndef HOMEWORK_1_FIBHELPER_HPP
#define HOMEWORK_1_FIBHELPER_HPP

#include <array>

/**
 * Helper class to deal with fib numbers more easily
 *  Stores a cache of a number of fib numbers for easy access
 */
class FibHelper {
public: // Methods
    FibHelper() = default;

    /**
     * Checks two numbers and see if it is a valid fibonacci pair
     * @param num1 First number to check
     * @param num2 Second number to check
     * @return True -> The two numbers are a valid fibonacci pair
     *         False -> THe two numbers are not a valid fibonacci pair
     */
    bool checkFibPairs(unsigned int num1, unsigned int num2);

    /**
     * Generates the cache of fibonacci numbers for easy access later
     */
    void generateFibCache();
public: // Members
    /**
     * Determines the max number of fibonacci numbers to store
     */
    static constexpr int max_fib_iter{100};

    /**
     * Stores a cache of all the fib numbers so they can be easily accessed
     */
    std::array<unsigned int, max_fib_iter> fib_cache{0};
};


#endif //HOMEWORK_1_FIBHELPER_HPP
