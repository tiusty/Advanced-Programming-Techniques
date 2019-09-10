/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 9/10/2019
Description:
 Tests the grid class
*/

#include <gtest/gtest.h>

#include <queue>
#include <array>
#include "grid.hpp"

using GridUpdateMaxPossibleProductTuple = std::tuple<int, std::array<int,Grid::numAdjNumbers>,int>;
class GridUpdateMaxPossibleProductTestFixture:public ::testing::TestWithParam<GridUpdateMaxPossibleProductTuple > {
};

/**
 * Parameterized test to test various scenarios
 */
TEST_P(GridUpdateMaxPossibleProductTestFixture, TestNominal)
{
    // Arrange
    Grid grid;
    std::array<int, Grid::numAdjNumbers> myInts{3,5,7,15};
    std::priority_queue<int, std::vector<int>, std::greater<> > priorityQueue{myInts.begin(), myInts.end()};
    int maxProduct{1};
    for (auto& n : myInts)
        maxProduct *= n;
    grid.maxPossibleProduct = maxProduct;

    int newValue = std::get<0>(GetParam());

    // Act
    grid.updateMaxPossibleProduct(newValue, priorityQueue);

    // Assert
    std::array<int, Grid::numAdjNumbers> expectedInts = std::get<1>(GetParam());
    ASSERT_EQ(priorityQueue.size(), Grid::numAdjNumbers);
    ASSERT_EQ(grid.maxPossibleProduct, std::get<2>(GetParam()));
    for(int i=0; i<priorityQueue.size(); ++i)
    {
        ASSERT_EQ(priorityQueue.top(), expectedInts.at(i));
        priorityQueue.pop();
    }
}

INSTANTIATE_TEST_SUITE_P(
        GridUpdateMaxPossibleProductTests,
        GridUpdateMaxPossibleProductTestFixture,
        ::testing::Values(
                GridUpdateMaxPossibleProductTuple(10, {5,7,10,15}, 5250),
                GridUpdateMaxPossibleProductTuple(1, {3,5,7,15}, 1575),
                GridUpdateMaxPossibleProductTuple(3, {3,5,7,15}, 1575),
                GridUpdateMaxPossibleProductTuple(20, {5,7,15,20}, 10500),
                GridUpdateMaxPossibleProductTuple(7, {5,7,7,15}, 3675)
                )
        );
