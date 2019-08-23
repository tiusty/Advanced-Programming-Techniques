/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 8/23/2019
Description: 
*/

#ifndef HOMEWORK_1_FIBHELPER_HPP
#define HOMEWORK_1_FIBHELPER_HPP

#include <array>

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
    std::array<unsigned int, max_fib_iter> fib_cache{0};


};


#endif //HOMEWORK_1_FIBHELPER_HPP
