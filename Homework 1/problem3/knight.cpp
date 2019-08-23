/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 8/23/2019
Description: 
*/

#include "knight.hpp"

void Knight::setValidFibPairs()
{
    unsigned int counter=0;
    for(int i=0; i<max_number_of_knights; i++)
    {
        if(fib_helper->checkFibPairs(counter, seat_num))
        {
            valid_knights.at(num_valid_knights) = counter;
            num_valid_knights++;
        }
        counter++;
    }
}
