/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 8/24/2019
Description:
 Contains the functionality for the knight class
*/

#include "knight.hpp"

void Knight::setValidFibPairs(unsigned int numKnights)
{
    // Finds the valid fib pairs for that knight
    for(unsigned int i=1; i <= numKnights; i++)
    {
        // Don't add the knights seat number since it is for itself
        if (i == seatNum)
        {
            continue;
        }
        else if(fibHelper->checkFibPairs(i, seatNum))
        {
            // If the number is a valid fib pair then add it to
            //  it's array for valid vib knights
            validKnights.at(numValidKnights) = i;
            numValidKnights++;
        }
    }
}
