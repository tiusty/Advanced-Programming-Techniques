/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 9/25/2019
Description: 
*/

#include <gtest/gtest.h>

#include "lattice.h"

using LatticeNumNodesTuple = std::tuple<int, int, int>;
class LatticeNumNodesTestFixture:public ::testing::TestWithParam<LatticeNumNodesTuple > {
};

TEST_P(LatticeNumNodesTestFixture, TestNominal)
{
    // Arrange
    Lattice lat(std::get<0>(GetParam()), std::get<1>(GetParam()));

    // Act / Assert
    ASSERT_EQ(lat.numLatNodes(), std::get<2>(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
        LatticeNumNodesTests,
        LatticeNumNodesTestFixture,
        ::testing::Values(
                LatticeNumNodesTuple(2,2,9),
                LatticeNumNodesTuple(3,3,16)
        )
);