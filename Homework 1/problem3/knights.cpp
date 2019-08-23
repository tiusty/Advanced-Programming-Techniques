/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 8/23/2019
Description: 
*/

#include "knights.hpp"

#include <algorithm>

bool sortKnights (const Knight& i,const Knight& j) {
    if(j.num_valid_knights == 0 || i.num_valid_knights == 0) {
        return false;
    } else {
        return (i.num_valid_knights<j.num_valid_knights);
    }
}

Knights::Knights(const std::shared_ptr<FibHelper>& fib_helper)
{
    unsigned int counter{1};
    for(auto &knight : knights) {
        knight.fib_helper = fib_helper;
        knight.seat_num = counter;
        counter++;
    }
}

void Knights::initializeKnights(unsigned int knight_num)
{
    num_knights = knight_num;
    // Determine all the valid fib numbers
    for(Knight &knight : knights) {
        knight.setValidFibPairs(num_knights);
    }

    // Sort Knights
    std::sort(knights.begin(), knights.begin() + num_knights, sortKnights);
}
