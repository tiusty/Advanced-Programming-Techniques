/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 9/11/2019
Description:
 Test determine valid index function
*/

#include <gtest/gtest.h>

#include "triangle.hpp"

using TriangleDetermineValidIndexTuple = std::tuple<int, int, bool>;
class TriangleDetermineValidIndexTestFixture:public ::testing::TestWithParam<TriangleDetermineValidIndexTuple > {
};

TEST_P(TriangleDetermineValidIndexTestFixture, TestNominalAtFourFour)
{
    // Arrange
    Triangle tri;
    nodeIndex index = std::make_pair(std::get<0>(GetParam()), std::get<1>(GetParam()));


    // Act / Assert
    ASSERT_EQ(tri.determineValidIndex(index), std::get<2>(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
        TriangleDetermineValidIndexTests,
        TriangleDetermineValidIndexTestFixture,
        ::testing::Values(
        TriangleDetermineValidIndexTuple(1,1, true),
        TriangleDetermineValidIndexTuple(-1,1, false),
        TriangleDetermineValidIndexTuple(1,-1, false),
        TriangleDetermineValidIndexTuple(2,1, true),
        TriangleDetermineValidIndexTuple(3,-1, false),
        TriangleDetermineValidIndexTuple(4,5, false),
        TriangleDetermineValidIndexTuple(4,2, true),
        TriangleDetermineValidIndexTuple(1,2, false)
)
);


