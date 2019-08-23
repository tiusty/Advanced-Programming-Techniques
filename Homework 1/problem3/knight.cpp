/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 8/23/2019
Description: 
*/

#include "knight.hpp"

void Knight::setValidFibPairs(unsigned int num_knights)
{
    for(unsigned int i=1; i<=num_knights; i++)
    {
        if (i == seat_num)
        {
            continue;
        }
        else if(fib_helper->checkFibPairs(i, seat_num))
        {
            valid_knights.at(num_valid_knights) = i;
            num_valid_knights++;
        }
    }
}
