/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 9/11/2019
Description:
 Main function for finding maximum path sum
*/

#include "triangle.hpp"

/**
 * Function executes main functionality by creating necessary components
 * @return Exit status of the program
 */
int main()
{
    // Create the triangle
    Triangle tri("data_triangle.txt");
    // Get the largest sum
    tri.getLargestSum();
    // Exit status
    return 0;
}

