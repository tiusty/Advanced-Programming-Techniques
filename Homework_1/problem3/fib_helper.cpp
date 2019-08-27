/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 8/24/2019
Description:
 Contains funciontality for the fib helper class
*/

#include <iostream>
#include "fib_helper.hpp"

constexpr int FibHelper::maxFibIter;

void FibHelper::generateFibCache()
{
    fibCache.at(0) = 1;
    fibCache.at(1) = 1;
    for(int i = 2 ; i < maxFibIter; i++) {
        fibCache.at(i) = fibCache.at(i - 1) + fibCache.at(i - 2);
    }
}

bool FibHelper::checkFibPairs(unsigned int num1, unsigned int num2)
{
    unsigned int value = num1 + num2;
    for(unsigned int fibNum : fibCache) {

        // If the values match then return true
        if (value == fibNum) {
            return true;
        }

        // Exit if the fibonacci numbers are greater
        //  than the value since the array is sorted from smallest to largest
        if(fibNum > value) {
            return false;
        }
    }

    // If the array ends and a pair isn't found then throw a warning that
    //  the number of fib iterations may have been too small
    std::cout << "Warning; CheckFibPairs loop ended, the cache may have not stored enough fib numbers" << std::endl;
    return false;
}

