/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 8/24/2019
Description:
 Contains the functionality for the knights class
*/

#include "knights.hpp"

#include <algorithm>
#include <iostream>

/**
 * A sorting function used to sort from least number of valid neighbors to most.
 * Used to speed up matching since it tries to match the most restrictive knights
 * first
 */
bool sortKnights (const Knight& i,const Knight& j) {
    if(j.numValidKnights == 0 || i.numValidKnights == 0) {
        return false;
    } else {
        return (i.numValidKnights < j.numValidKnights);
    }
}

Knights::Knights(const std::shared_ptr<FibHelper>& fibHelper)
{
    unsigned int counter{1};

    // Give each knight access to the fib_helper and set their seat number
    for(auto &knight : knights) {
        knight.fibHelper = fibHelper;
        knight.seatNum = counter;
        counter++;
    }
}

void Knights::initializeKnights(unsigned int numberKnights)
{
    if(numberKnights > Knight::kMaxNumberOfKnights)
    {
        std::cout << "Error: Tried to set more knights then max, please increase max number to run" << std::endl;
        exit(1);
    }

    // Stores the desired number of knights to be seated
    numKnights = numberKnights;

    // Determine all the valid neighbors (fib numbers) for each knight
    // This is used later to reduce the complexity of the loop
    for(Knight &knight : knights) {
        knight.setValidFibPairs(numKnights);
    }

    // Sort Knights from least valid number of neighbors to most
    std::sort(knights.begin(), knights.begin() + numKnights, sortKnights);
}

bool Knights::determineValidSeating(const Knight& alreadySeated, const Knight& potentialNeighbor)
{
    bool valid = false;

    // If the potential neighbor is already found then they cannot be a valid neighbor
    //  so return false
    if(potentialNeighbor.found)
    {
        return false;
    }

    // For any knights waiting to be seated (not found), if that potential knight has the current knight stored
    //  as a valid neighbor (valid knight) then return true
    for(int i=0; i < potentialNeighbor.numValidKnights; i++)
    {
        if(potentialNeighbor.validKnights.at(i) == alreadySeated.seatNum)
        {
            valid = true;
            break;
        }
    }

    return valid;
}

bool Knights::findNeighbor(Knight &seatedKnight)
{
    // Since the knight is seated, mark it as found and increment the seating_index
    bool foundNeighbor{false};

    seatedKnight.found = true;
    seatingOrder.at(seatingIndex) = seatedKnight.seatNum;
    seatingIndex++;

    // End condition if all the knights are found
    // Starts chain of recursive founds to end recursive calls
    if(seatingIndex == numKnights)
    {
        return true;
    }

    // Searches for a valid neighbor
    for(unsigned int i=0; i < numKnights; i++)
    {
        // If a valid neighbor is found, then recursively call find neighbor for the
        //  new knight. If it can't find any valid neighbors then keep searching for
        //  a new knight
        if(determineValidSeating(seatedKnight, knights.at(i)))
        {
            foundNeighbor = findNeighbor(knights.at(i));
        }

        // If the neighbor was found (i.e end condition, then break)
        if(foundNeighbor)
        {
            break;
        }
    }

    // If the knight couldn't find a neighbor then subtract the seating_index since the
    //  neighbor was not found
    if(not foundNeighbor)
    {
        seatingIndex--;
        seatedKnight.found = false;
    }

    return foundNeighbor;
}

void Knights::determineSeatingOrder(unsigned int knightsNum)
{
    // Initialize the knights for the number that wants to be seated
    initializeKnights(knightsNum);

    bool result{false};
    // Start searching for potential seating orders
    for(unsigned int i=0; i < knightsNum; i++)
    {
        result = findNeighbor(knights.at(i));
        if(result)
        {
            break;
        }
    }

    // Determine result of the search
    if(result)
    {
        std::cout << "Solution found" << std::endl;

        // Create the string to output the seating order and then print it
        char outputStr[maxSeatingCharLength];
        sprintf(outputStr, "K");
        for(unsigned int i=0; i < knightsNum; i++)
        {
            sprintf(outputStr, "%s,%d", outputStr, seatingOrder.at(i));
        }
        std::cout << outputStr << std::endl;
    }
    else
    {
        std::cout << "No solution exists" << std::endl;
    }
}
