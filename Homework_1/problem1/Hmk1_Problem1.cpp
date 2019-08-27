/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 8/23/2019
Description:
 Determines the number of ones needed to add to a number while dividing by 7 so that there are no reminders.
*/
#include <iostream>
#include <cstdlib>

/**
 * Main function
 *
 * Executes functionality
 */
int main()
{
    // Declare variables
    int inputNum = 0;
    unsigned int numIncrements = 0;

    // Prompt then read in a number
    std::cout << "Please enter a number positive number" << std::endl;
    std::cin >> inputNum;

    // Error condition for negative numbers
    if (inputNum < 0) {
        std::cout << "Error: Please enter in a positive number" << std::endl;
        // Return error status if a negative number is entered
        exit(1);
    }

    bool active = true;
    while(active) {
        // Condition for ending
        if(inputNum <= 1)
        {
            active = false;
        // Checks if their is a remainder, if not then divide the number by 7
        }
        else if (inputNum % 7 == 0)
        {
            inputNum /= 7;
        }
        // If there is a reminder then add one until there isn't a remainder
        else
        {
            inputNum++;
            numIncrements++;
        }
    }

    // Print Results
    std::cout << "Number of increments: " << numIncrements << std::endl;
    return 0;
}

