/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 9/25/2019
Description: 
*/

#include <gtest/gtest.h>

#include "lattice.h"

using LatticeGetParentSumTuple = std::tuple<int, int, int>;
class LatticeGetParentSumTestFixture:public ::testing::TestWithParam<LatticeGetParentSumTuple > {
};

TEST_P(LatticeGetParentSumTestFixture, TestNominal)
{
    // Arrange
    Lattice lat(4, 4);
    lat.latNodes.at(0) = 1;
    lat.latNodes.at(1) = 1;
    lat.latNodes.at(2) = 1;
    lat.latNodes.at(3) = 1;
    lat.latNodes.at(4) = 2;
    lat.latNodes.at(5) = 3;
    lat.latNodes.at(6) = 4;
    lat.latNodes.at(7) = 6;
    lat.latNodes.at(8) = 10;
    lat.latNodes.at(9) = 20;

    // Act / Assert
    ASSERT_EQ(lat.getParentSum(std::get<0>(GetParam()), std::get<1>(GetParam())), std::get<2>(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
        LatticeGetParentSumTests,
        LatticeGetParentSumTestFixture,
        ::testing::Values(
                LatticeGetParentSumTuple(1,1,0),
                LatticeGetParentSumTuple(1,2,1),
                LatticeGetParentSumTuple(1,3,1),
                LatticeGetParentSumTuple(1,4,1),
                LatticeGetParentSumTuple(2,2,2),
                LatticeGetParentSumTuple(2,3,3),
                LatticeGetParentSumTuple(2,4,4),
                LatticeGetParentSumTuple(3,3,6),
                LatticeGetParentSumTuple(3,4,10),
                LatticeGetParentSumTuple(4,4,20)
        )
);
