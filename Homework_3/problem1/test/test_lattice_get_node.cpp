/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 9/25/2019
Description: 
*/

#include <gtest/gtest.h>

#include "lattice.h"

using LatticeGetNodesTuple = std::tuple<int, int, int>;
class LatticeGetNodesTestFixture:public ::testing::TestWithParam<LatticeGetNodesTuple > {
};

TEST_P(LatticeGetNodesTestFixture, TestNominal)
{
    // Arrange
    Lattice lat(4, 4);

    // Act / Assert
    ASSERT_EQ(lat.getNode(std::get<0>(GetParam()), std::get<1>(GetParam())), std::get<2>(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
        LatticeGetNodesTests,
        LatticeGetNodesTestFixture,
        ::testing::Values(
        LatticeGetNodesTuple(1,1,0),
        LatticeGetNodesTuple(1,2,1),
        LatticeGetNodesTuple(1,3,2),
        LatticeGetNodesTuple(1,4,3),
        LatticeGetNodesTuple(2,2,4),
        LatticeGetNodesTuple(2,3,5),
        LatticeGetNodesTuple(2,4,6),
        LatticeGetNodesTuple(3,3,7),
        LatticeGetNodesTuple(3,4,8),
        LatticeGetNodesTuple(4,4,9)
)
);
