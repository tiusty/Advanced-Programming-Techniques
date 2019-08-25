/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 8/23/2019
Description:
 Determines the number of ones needed to add to a number while dividing by 7 so that there are no reminders.
*/
#include <iostream>

/**
 * Main function
 *
 * Executes functionality
 */
int main()
{
    // Declare variables
    int input_num = 0;
    unsigned int num_increments = 0;

    // Prompt then read in a number
    std::cout << "Please enter a number positive number" << std::endl;
    std::cin >> input_num;

    // Error condition for negative numbers
    if (input_num < 0) {
        std::cout << "Error: Please enter in a positive number" << std::endl;
        // Return error status if a negative number is entered
        exit(1);
    }

    bool active = true;
    while(active) {
        // Condition for ending
        if(input_num <= 1) {
            active = false;
        // Checks if their is a remainder, if not then divide the number by 7
        } else if (input_num % 7 == 0) {
            input_num /= 7;
        // If there is a reminder then add one until there isn't a remainder
        } else {
            input_num++;
            num_increments++;
        }
    }

    // Print Results
    std::cout << "Number of increments: " << num_increments << std::endl;
    return 0;
}

