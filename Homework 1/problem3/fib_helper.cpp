/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 8/23/2019
Description: 
*/

#include <iostream>
#include "fib_helper.hpp"

constexpr int FibHelper::max_fib_iter;

FibHelper::FibHelper()
{
    generateFibCache();
}

void FibHelper::generateFibCache()
{
    fib_cache.at(0) = 1;
    fib_cache.at(1) = 1;
    for(int i = 2 ; i<max_fib_iter; i++) {
        fib_cache.at(i) = fib_cache.at(i-1) + fib_cache.at(i-2);
    }
}

bool FibHelper::checkFibPairs(unsigned int num1, unsigned int num2)
{
    unsigned int value = num1 + num2;
    for(unsigned int fib_num : fib_cache) {

        // If the values match then return true
        if (value == fib_num) {
            return true;
        }

        // Exit if the fibonacci numbers are greater
        //  than the value since the array is sorted from smallest to largest
        if(fib_num > value) {
            return false;
        }
    }

    // If the array ends and a pair isn't found then throw a warning that
    //  the number of fib iterations may have been too small
    std::cout << "Warning; CheckFibPairs loop ended, the cache may have not stored enough fib numbers" << std::endl;
    return false;
}

