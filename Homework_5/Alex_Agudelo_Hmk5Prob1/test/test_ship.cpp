/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 10/29/19
Description: 
*/

#include <gtest/gtest.h>
#include "ship.hpp"

using ShipTimeToStopTuple = std::tuple<Coordinate, int>;
class ShipTimeToStopTestFixture:public ::testing::TestWithParam<ShipTimeToStopTuple > {
};

TEST_P(ShipTimeToStopTestFixture, TestNominalAtFourFour)
{
    // Arrange
    Ship ship;
    ship.velocity = std::get<0>(GetParam());

    // Act
    int result = ship.timeToStop();

    // Result
    ASSERT_EQ(result, std::get<1>(GetParam()));

}

INSTANTIATE_TEST_SUITE_P(
        ShipTimeToStopTests,
        ShipTimeToStopTestFixture,
        ::testing::Values(
                ShipTimeToStopTuple(Coordinate{0,0,0}, 0),
                ShipTimeToStopTuple(Coordinate{10,5,1}, 2),
                ShipTimeToStopTuple(Coordinate{10,-10,1}, 2),
                ShipTimeToStopTuple(Coordinate{10,50,1}, 10),
                ShipTimeToStopTuple(Coordinate{10,5,-70}, 14)
)
);



