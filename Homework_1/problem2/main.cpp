/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 8/23/2019
Description:
 Numerical integration. Calculate the value value of an integral using the midpoint rule
*/
#include <iostream>
#include <functional>
#include <cstdlib>

/**
 * Main Function
 * Executes the program
 */
int main()
{
    // Declare variables
    double upperLimit = 0;
    int numSubdivisions = 0;
    double indexSpacing = 0;
    double finalValue = 0;

    // Retrieve data from user
    std::cout << "Please enter the upper limit" << std::endl;
    std::cin >> upperLimit;
    std::cout << "Please enter the number of subdivisions to use" << std::endl;
    std::cin >> numSubdivisions;

    // Error check inputs
    if (numSubdivisions < 1)
    {
        std::cout << "Number of subdivisions should be greater than 0" << std::endl;
        exit(1);
    }

    // Declare the integration function to easily retrieve values
    std::function<double(double)> func = [](double x) {
        return 4 / (1 + x*x);
    };

    // Perform integration
    indexSpacing = upperLimit / numSubdivisions;
    for(int i = 1; i < numSubdivisions; i++) {
        finalValue += func(indexSpacing * i) * indexSpacing;
    }

    // Print final value
    std::cout << "Final value: " << finalValue << std::endl;

    return 0;
}

