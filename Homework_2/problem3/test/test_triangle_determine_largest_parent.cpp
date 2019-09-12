/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 9/11/2019
Description:
 Tests determine largest parent function
*/

#include <gtest/gtest.h>

#include "triangle.hpp"

using TriangleDetermineLargestParentTuple = std::tuple<int, int, int, int>;
class TriangleDetermineLargestParentTestFixture:public ::testing::TestWithParam<TriangleDetermineLargestParentTuple > {
};

TEST_P(TriangleDetermineLargestParentTestFixture, TestNominalAtFourFour)
{
    // Arrange
    Triangle tri("data_triangle.txt");
    std::shared_ptr<Node> node = std::make_shared<Node>(tri.getNode(std::get<0>(GetParam()), std::get<1>(GetParam())));


    // Manually set sums for testing
    tri.triangle.at(0).sumWithNode = 3;
    tri.triangle.at(1).sumWithNode = 10;
    tri.triangle.at(2).sumWithNode = 7;
    tri.triangle.at(3).sumWithNode = 12;
    tri.triangle.at(4).sumWithNode = 14;
    tri.triangle.at(5).sumWithNode = 13;
    tri.triangle.at(6).sumWithNode = 20;
    tri.triangle.at(7).sumWithNode = 19;
    tri.triangle.at(8).sumWithNode = 23;
    tri.triangle.at(9).sumWithNode = 16;

    // Act
    tri.determineLargestParent(*node);

    // Assert
    Node expectedResult = tri.getNode(std::get<2>(GetParam()), std::get<3>(GetParam()));
    ASSERT_EQ(node->pathToParent->index.first, expectedResult.index.first);
    ASSERT_EQ(node->pathToParent->index.second, expectedResult.index.second);

}

INSTANTIATE_TEST_SUITE_P(
        TriangleDetermineLargestParentTests,
        TriangleDetermineLargestParentTestFixture,
        ::testing::Values(
                TriangleDetermineLargestParentTuple(2,1,1,1),
                TriangleDetermineLargestParentTuple(2,2,1,1),
                TriangleDetermineLargestParentTuple(3,1,2,1),
                TriangleDetermineLargestParentTuple(3,2,2,1),
                TriangleDetermineLargestParentTuple(3,3,2,2),
                TriangleDetermineLargestParentTuple(4,1,3,1),
                TriangleDetermineLargestParentTuple(4,2,3,2),
                TriangleDetermineLargestParentTuple(4,3,3,2),
                TriangleDetermineLargestParentTuple(4,4,3,3)
        )
);


