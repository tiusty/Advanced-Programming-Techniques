/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 9/10/2019
Description:
 Tests that the product between indices works properly
*/

#include <gtest/gtest.h>
#include "grid.hpp"

TEST(TestGridProductBetweenMatrices, TestNominal)
{
    // Arrange
    Grid grid("data_Problem2.txt");
    int result{0};
    gridIndex startIndex = std::make_pair(4,4);
    gridIndex endIndex = std::make_pair(5,5);

    // Act
    result = grid.productBetweenIndices(startIndex, endIndex);

    // Assert
    ASSERT_EQ(result, 153);

}

