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

/**
 * A sorting function used to sort from least number of valid neighbors to most
 * Used to speed up matching since it tries to match the most restrictive knights
 * first
 */
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

    // Give each knight access to the fib_helper and set their seat number
    for(auto &knight : knights) {
        knight.fib_helper = fib_helper;
        knight.seat_num = counter;
        counter++;
    }
}

void Knights::initializeKnights(unsigned int knights_num)
{
    if(knights_num > Knight::max_number_of_knights)
    {
        std::cout << "Error: Tried to set more knights then max, please increase max number to run" << std::endl;
        exit(1);
    }

    // Stores the desired number of knights
    num_knights = knights_num;

    // Determine all the valid neighbors (fib numbers) for each knight
    for(Knight &knight : knights) {
        knight.setValidFibPairs(num_knights);
    }

    // Sort Knights from least valid number of neighbors to most
    std::sort(knights.begin(), knights.begin() + num_knights, sortKnights);
}

bool Knights::determineValidSeating(const Knight& already_seated, const Knight& potential_neighbor)
{
    bool valid = false;

    // If the potential neighbor is already found then they cannot be a valid neighbor
    //  so return false
    if(potential_neighbor.found)
    {
        return false;
    }

    // For any un-found knights search for a knight that has the already_seated knights num
    //  as a valid neighbor
    for(int i=0; i<potential_neighbor.num_valid_knights; i++)
    {
        if(potential_neighbor.valid_knights.at(i) == already_seated.seat_num)
        {
            valid = true;
            break;
        }
    }

    return valid;
}

bool Knights::findNeighbor(Knight &seated_knight)
{
    // Since the knight is seated, mark it as found and increment the seating_index
    bool found_neighbor{false};
    seated_knight.found = true;
    seating_order.at(seating_index) = seated_knight.seat_num;
    seating_index++;

    // End condition if all the knights are found
    if(seating_index == num_knights)
    {
        return true;
    }

    // Searches for a valid neighbor
    for(unsigned int i=0; i<num_knights;i++)
    {
        // If a valid neighbor is found, then recursively call find neighbor for the
        //  new knight. If it can't find any valid neighbors then keep searching for
        //  a new knight
        if(determineValidSeating(seated_knight, knights.at(i)))
        {
            found_neighbor = findNeighbor(knights.at(i));
        }

        // If the neighbor was found (i.e end condition, then break)
        if(found_neighbor)
        {
            break;
        }
    }

    // If the knight couldn't find a neighbor then subtract the seating_index since the
    //  neighbor was not found
    if(not found_neighbor) {
        seating_index--;
        seated_knight.found = false;
    }

    return found_neighbor;
}

void Knights::determineSeatingOrder(unsigned int knights_num)
{
    // Initialize the knights for the number that wants to be seated
    initializeKnights(knights_num);

    // Start brute force method of seating
    bool result{false};
    for(unsigned int i=0; i < knights_num; i++)
    {
        result = findNeighbor(knights.at(i));
        if(result)
        {
            break;
        }
    }

    // Determine result of the brute force
    if(result)
    {
        std::cout << "Solution found" << std::endl;
        std::stringstream ss;
        ss << "K";
        for(unsigned int i=0; i < knights_num; i++)
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
