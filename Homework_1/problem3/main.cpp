/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 8/24/2019
Description:
 Knights of the order of Fibonacci
*/
#include <iostream>
#include <memory>
#include <cstdlib>

#include "knights.hpp"
#include "fib_helper.hpp"

/**
 * Main Function
 * Executes the program
 */
int main()
{
    // Declare variables
    // Create the fib helper class
    auto fib_helper = std::make_shared<FibHelper>();
    fib_helper->generateFibCache();

    // Initialize the Knights
    Knights knights{fib_helper};

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

    // Initialize the number of knights and set the corresponding data
    knights.determineSeatingOrder(num_knights);
    

    return 0;
}

