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
    std::array<int, 4> myInts{3,5,7,15};
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
                GridUpdateMaxPossibleProductTuple(7, {5,7,7,15}, 3675),
                GridUpdateMaxPossibleProductTuple(0, {3,5,7,15}, 1575)
                )
        );

using GridUpdateMaxPossibleProductTupleNotEnough = std::tuple<std::array<int, Grid::numAdjNumbers>, int, std::array<int,Grid::numAdjNumbers>,int, int>;
class GridUpdateMaxPossibleProductTestFixtureNotEnough:public ::testing::TestWithParam<GridUpdateMaxPossibleProductTupleNotEnough > {
};

/**
 * Parameterized test to test various scenarios
 */
TEST_P(GridUpdateMaxPossibleProductTestFixtureNotEnough, TestNotEnoughValues)
{
    // Arrange
    Grid grid;
    std::array<int, 2> myInts{3,5};
    std::priority_queue<int, std::vector<int>, std::greater<> > priorityQueue{myInts.begin(), myInts.end()};
    int maxProduct{1};
    for (auto& n : myInts)
        if(n != 0)
        {
            maxProduct *= n;
        }
    grid.maxPossibleProduct = maxProduct;

    std::array<int, 4> newValues = std::get<0>(GetParam());

    // Act
    unsigned int counter = 0;
    for(auto &i : newValues)
    {
        if(counter >= std::get<1>(GetParam()))
        {
            break;
        }
        grid.updateMaxPossibleProduct(i, priorityQueue);
        counter++;
    }

    // Assert
    std::array<int, Grid::numAdjNumbers> expectedInts = std::get<2>(GetParam());
    ASSERT_EQ(priorityQueue.size(), std::get<3>(GetParam()));
    ASSERT_EQ(grid.maxPossibleProduct, std::get<4>(GetParam()));
    for(int i=0; i<priorityQueue.size(); ++i)
    {
        ASSERT_EQ(priorityQueue.top(), expectedInts.at(i));
        priorityQueue.pop();
    }
}

INSTANTIATE_TEST_SUITE_P(
        GridUpdateMaxPossibleProductTestsNotEnough,
        GridUpdateMaxPossibleProductTestFixtureNotEnough,
        ::testing::Values(
                GridUpdateMaxPossibleProductTupleNotEnough ({0,2,4}, 3, {2,3,4,5}, 4, 120),
                GridUpdateMaxPossibleProductTupleNotEnough ({10}, 1, {3,5,10}, 3, 150),
                GridUpdateMaxPossibleProductTupleNotEnough ({0}, 1, {0,3,5}, 3, 15),
                GridUpdateMaxPossibleProductTupleNotEnough ({0,2}, 2, {0,2,3,5}, 4, 30),
                GridUpdateMaxPossibleProductTupleNotEnough({2,3}, 2, {2,3,3,5}, 4, 90),
                GridUpdateMaxPossibleProductTupleNotEnough({2,3,4}, 3, {3,3,4,5}, 4, 180),
                GridUpdateMaxPossibleProductTupleNotEnough({10, 5, 15}, 3, {5,5,10,15}, 4, 3750),
                GridUpdateMaxPossibleProductTupleNotEnough({1,1,1,1,}, 4, {1,1,3,5}, 4, 15)
        )
);
