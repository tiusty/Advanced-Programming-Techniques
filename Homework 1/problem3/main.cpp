/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 8/23/2019
Description:
 Knights of the order of Fibonacci
*/
#include <iostream>
#include "knight.hpp"

/**
 * Main Function
 * Executes the program
 */

int main()
{
    // Declare variables
    std::array<Knight, Knight::max_number_of_knights> knights;
    std::array<bool, Knight::max_number_of_knights> found{false};
    unsigned long num_knights;

    // Prompt User
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
    // Determine if fibonacci number

    // Find suitable candidates up to n
    return 0;
}

