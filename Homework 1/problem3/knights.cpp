/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 8/24/2019
Description: 
*/

#include "knights.hpp"

#include <algorithm>
#include <iostream>
#include <sstream>

bool sortKnights (const Knight& i,const Knight& j) {
    if(j.num_valid_knights == 0 || i.num_valid_knights == 0) {
        return false;
    } else {
        return (i.num_valid_knights<j.num_valid_knights);
    }
}

Knights::Knights(const std::shared_ptr<FibHelper>& fib_helper)
{
    unsigned int counter{1};
    for(auto &knight : knights) {
        knight.fib_helper = fib_helper;
        knight.seat_num = counter;
        counter++;
    }
}

void Knights::initializeKnights(unsigned int knight_num)
{
    num_knights = knight_num;
    // Determine all the valid fib numbers
    for(Knight &knight : knights) {
        knight.setValidFibPairs(num_knights);
    }

    // Sort Knights
    std::sort(knights.begin(), knights.begin() + num_knights, sortKnights);
}

bool Knights::determineValidSeating(const Knight& already_seated, const Knight& potential_neighbor)
{
    bool valid = false;

    if(potential_neighbor.found)
    {
        return false;
    }

    for(unsigned int valid_knight : potential_neighbor.valid_knights)
    {
        if(valid_knight == already_seated.seat_num)
        {
            valid = true;
            break;
        }
    }

    return valid;
}

bool Knights::findNeighbor(Knight &seated_knight)
{
    bool found_neighbor{false};
    seated_knight.found = true;
    seating_order.at(seating_index) = seated_knight.seat_num;
    seating_index++;

    if(seating_index == num_knights)
    {
        return true;
    }

    for(unsigned int i=0; i<num_knights;i++)
    {
        if(determineValidSeating(seated_knight, knights.at(i)))
        {
            found_neighbor = findNeighbor(knights.at(i));
        }
        if(found_neighbor)
        {
            break;
        }
    }

    if(not found_neighbor) {
        seating_index--;
    }

    return found_neighbor;
}

void Knights::determineSeatingOrder(unsigned int num_knights) {

    initializeKnights(num_knights);

    bool result{false};
    for(unsigned int i=0; i<num_knights;i++)
    {
        result = findNeighbor(knights.at(i));
        if(result)
        {
            break;
        }
    }

    if(result)
    {
        std::cout << "Solution found" << std::endl;
        std::stringstream ss;
        ss << "K";
        for(unsigned int i=0; i<num_knights; i++)
        {
            ss << "," << seating_order.at(i);
        }
        std::cout << ss.str() << std::endl;
    }
    else
    {
        std::cout << "No solution exists" << std::endl;
    }
}
