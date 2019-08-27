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
    for(unsigned int i=1; i <= numKnights; i++)
    {
        if (i == seatNum)
        {
            continue;
        }
        else if(fibHelper->checkFibPairs(i, seatNum))
        {
            validKnights.at(numValidKnights) = i;
            numValidKnights++;
        }
    }
}
