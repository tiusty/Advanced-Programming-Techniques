/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 8/23/2019
Description:
 Numerical integration. Calculate the value value of an integral using the midpoint rule
*/
#include <iostream>
#include <functional>

/**
 * Main Function
 * Executes the program
 */
int main()
{
    // Declare variables
    double upper_limit = 0;
    int num_subdivisions = 0;
    double index_spacing = 0;
    double final_value = 0;

    // Retrieve data from user
    std::cout << "Please enter the upper limit" << std::endl;
    std::cin >> upper_limit;
    std::cout << "Please enter the number of subdivisions to use" << std::endl;
    std::cin >> num_subdivisions;

    // Error check inputs
    if (num_subdivisions < 1) {
        std::cout << "Number of subdivisions should be greater than 0" << std::endl;
        exit(1);
    }

    // Declare the integration function to easily retrieve values
    std::function<double(double)> func = [](double x) {
        return 4 / (1 + x*x);
    };

    // Perform integration
    index_spacing = upper_limit/num_subdivisions;
    for(int i = 1; i < num_subdivisions; i++) {
        final_value += func(index_spacing * i) * index_spacing;
    }

    // Print final value
    std::cout << "Final value: " << final_value << std::endl;

    return 0;
}

