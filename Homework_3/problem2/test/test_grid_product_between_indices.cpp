/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 9/10/2019
Description:
 Tests that the product between indices works properly
*/

#include <gtest/gtest.h>
#include "grid.hpp"

using GridProductBetweenMatriciesTuple = std::tuple<gridIndex, gridIndex, int>;
class GridProductBetweenMatricesTestFixture:public ::testing::TestWithParam<GridProductBetweenMatriciesTuple > {
};

/**
 * Parameterized test to test various scenarios
 */
TEST_P(GridProductBetweenMatricesTestFixture, TestNominal)
{
    // Arrange
    Grid grid("data_Problem2.txt");
    int result{0};
    gridIndex startIndex = std::get<0>(GetParam());
    gridIndex endIndex = std::get<1>(GetParam());

    // Act
    result = grid.productBetweenIndices(startIndex, endIndex);

    // Assert
    ASSERT_EQ(result, std::get<2>(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
        GridProductBetweenMatricesTests,
        GridProductBetweenMatricesTestFixture,
        ::testing::Values(
                GridProductBetweenMatriciesTuple(gridIndex(4,4), gridIndex(4,1), 1796016),
                GridProductBetweenMatriciesTuple(gridIndex(4,4), gridIndex(4,7), 19159119),
                GridProductBetweenMatriciesTuple(gridIndex(4,4), gridIndex(1,4), 190740),
                GridProductBetweenMatriciesTuple(gridIndex(4,4), gridIndex(7,4), 646272),
                GridProductBetweenMatriciesTuple(gridIndex(4,4), gridIndex(2,6), 42840),
                GridProductBetweenMatriciesTuple(gridIndex(4,4), gridIndex(5,3), 3060),
                GridProductBetweenMatriciesTuple(gridIndex(4,4), gridIndex(1,1), 1781787),
                GridProductBetweenMatriciesTuple(gridIndex(4,4), gridIndex(3,3), 1173),
                GridProductBetweenMatriciesTuple(gridIndex(4,4), gridIndex(7,7), 205020),
                GridProductBetweenMatriciesTuple(gridIndex(4,4), gridIndex(5,5), 153)
        )
);


