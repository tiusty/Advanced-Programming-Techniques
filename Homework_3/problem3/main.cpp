/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 9/11/2019
Description:
 Main function for finding maximum path sum
*/

#include "triangle.hpp"
#include <iostream>

/**
 * Function executes main functionality by creating necessary components
 * @return Exit status of the program
 */
int main(int argc, char *argv[])
{
    char filename[50];

    if(argc < 2 || argc > 2)
    {
        std::cerr << "Error with arguments: Make sure to include only on extra argument which is the filename" << std::endl;
        exit(1);
    }

    sprintf(filename, "%s", argv[1]);
    // Create the triangle
    Triangle tri(filename);
    // Get the largest sum
    tri.getLargestSum();
    // Exit status
    return 0;
}

