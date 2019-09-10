/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 9/10/2019
Description:
 Tests the largest product along line function
*/

#include <gtest/gtest.h>
#include "grid.hpp"

TEST(TestLargestProductAlongLine, TestNominal)
{
    // Arrange
    Grid grid("data_Problem2.txt");
    gridElement elementToCheck = std::make_pair(std::make_pair(4,4), 51);

    // Act
    grid.largestProductAlongLine(1, 1, elementToCheck);

    // Assert
    ASSERT_EQ(grid.currentLargestProduct, 1781787);
}

