/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 9/10/2019
Description:
 Tests the largest product along line function
*/

#include <gtest/gtest.h>
#include "grid.h"

using GridLargestProductAlongLineTuple = std::tuple<int, int, int>;
class GridLargestProductAlongLineTestFixture:public ::testing::TestWithParam<GridLargestProductAlongLineTuple > {
};

TEST_P(GridLargestProductAlongLineTestFixture, TestNominalAtFourFour)
{
    // Arrange
    Grid grid("data_Problem2.txt");
    gridElement elementToCheck = std::make_pair(std::make_pair(4,4), 51);

    // Act
    grid.largestProductAlongLine(std::get<0>(GetParam()), std::get<1>(GetParam()), elementToCheck);

    // Assert
    ASSERT_EQ(grid.currentLargestProduct, std::get<2>(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
        GridLargestProductAlongLineTests,
        GridLargestProductAlongLineTestFixture,
        ::testing::Values(
                GridLargestProductAlongLineTuple(1,-1,14871600),
                GridLargestProductAlongLineTuple(1,0,1292544),
                GridLargestProductAlongLineTuple(0,1,19159119),
                GridLargestProductAlongLineTuple(1,1,1781787)
        )
);


