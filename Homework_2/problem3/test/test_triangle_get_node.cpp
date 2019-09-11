/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 9/11/2019
Description:
 Tests the get node function of the triangle class
*/

#include <gtest/gtest.h>

#include "triangle.hpp"
#include <exception>

using TriangleGetNodeTuple = std::tuple<int, int, int, bool>;
class TriangleGetNodeTestFixture:public ::testing::TestWithParam<TriangleGetNodeTuple > {
};

TEST_P(TriangleGetNodeTestFixture, TestNominalAtFourFour)
{
    // Arrange
    Triangle tri("data_triangle.txt");

    // Act
    if(std::get<3>(GetParam()))
    {
        ASSERT_EQ(tri.getNode(std::get<0>(GetParam()), std::get<1>(GetParam())).value, std::get<2>(GetParam()));
    }
    else
    {
        ASSERT_THROW(tri.getNode(std::get<0>(GetParam()), std::get<1>(GetParam())), std::out_of_range);
    }
}

INSTANTIATE_TEST_SUITE_P(
        TriangleGetNodeTests,
        TriangleGetNodeTestFixture,
        ::testing::Values(
                TriangleGetNodeTuple(1,1,3, true),
                TriangleGetNodeTuple(1,2,3, false),
                TriangleGetNodeTuple(2,-1,4, false),
                TriangleGetNodeTuple(3,1,2, true),
                TriangleGetNodeTuple(4,5,4, false),
                TriangleGetNodeTuple(4,3,9, true)
)
);


