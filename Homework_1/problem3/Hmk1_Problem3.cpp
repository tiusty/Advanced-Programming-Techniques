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

#include "table.hpp"
#include "fib_helper.hpp"

/**
 * Main Function
 * Executes the program
 */
int main()
{
    // Declare variables
    // Create the fib helper class
    auto fibHelper = std::make_shared<FibHelper>();
    fibHelper->generateFibCache();

    // Initialize the table
    Table table{fibHelper};

    // Determines the number of knights the user desires
    unsigned long numberKnights{0};

    // Prompt User for number of knights desired
    std::cout << "How many knights do you want to seat?" << std::endl;
    std::cin >> numberKnights;

    //Error check
    if (numberKnights < 1)
    {
        std::cout << "You need to seat at least one knight" << std::endl;
        exit(1);
    }
    if (numberKnights > Knight::kMaxNumberOfKnights)
    {
        std::cout << "Too many knights, either lower amount or raise max_number_of_knights value" << std::endl;
    }

    // Initialize the number of knights and set the corresponding data
    table.determineSeatingOrder(numberKnights);

    return 0;
}

