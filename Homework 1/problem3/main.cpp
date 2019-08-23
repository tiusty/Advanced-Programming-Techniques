/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 8/23/2019
Description:
 Knights of the order of Fibonacci
*/
#include <iostream>
#include <memory>
#include <algorithm>
#include "knight.hpp"
#include "fib_helper.hpp"

bool sortKnights (const Knight& i,const Knight& j) {
    if(j.num_valid_knights == 0 || i.num_valid_knights == 0) {
        return false;
    } else {
        return (i.num_valid_knights<j.num_valid_knights);
    }
}

/**
 * Main Function
 * Executes the program
 */
int main()
{
    // Declare variables
    // Create the fib helper class
    auto fib_helper = std::make_shared<FibHelper>();

    // Initialize the Knights
    std::array<Knight, Knight::max_number_of_knights> knights;
    unsigned int counter{1};
    for(auto &knight : knights) {
        knight.fib_helper = fib_helper;
        knight.seat_num = counter;
        counter++;
    }

    // Determines the number of knights the user desires
    unsigned long num_knights{0};

    // Prompt User for number of knights desired
    std::cout << "How many knights do you want to seat?" << std::endl;
    std::cin >> num_knights;

    //Error check
    if (num_knights < 1) {
        std::cout << "You need to seat at least one knight" << std::endl;
        exit(1);
    }
    if (num_knights > Knight::max_number_of_knights) {
        std::cout << "Too many knights, either lower amount or raise max_number_of_knights value" << std::endl;
    }

    // Determine all the valid fib numbers
    for(Knight &knight : knights) {
        knight.setValidFibPairs(num_knights);
    }

    // Sort Knights
    std::sort(knights.begin(), knights.begin() + num_knights, sortKnights);



    // Determine if fibonacci number

    // Find suitable candidates up to n
    return 0;
}

