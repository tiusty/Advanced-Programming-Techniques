/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 8/24/2019
Description:
 Integration tests to test full program
*/

#include <gtest/gtest.h>

#include "knights.hpp"
#include "fib_helper.hpp"

/**
 * Test that 7 knights are properly seated
 */
TEST(TestIntegration, TestKnightOrders7)
{
    // Arrange
    auto fib_helper = std::make_shared<FibHelper>();
    fib_helper->generateFibCache();
    Knights knights{fib_helper};
    unsigned int num_knights{7};

    // Act
    knights.determineSeatingOrder(num_knights);

    // Assert
    ASSERT_EQ(knights.seating_order.at(0),4);
    ASSERT_EQ(knights.seating_order.at(1),1);
    ASSERT_EQ(knights.seating_order.at(2),7);
    ASSERT_EQ(knights.seating_order.at(3),6);
    ASSERT_EQ(knights.seating_order.at(4),2);
    ASSERT_EQ(knights.seating_order.at(5),3);
    ASSERT_EQ(knights.seating_order.at(6),5);
}

/**
 * Test that 5 knights are properly seated
 */
TEST(TestIntegration, TestKnightOrders5)
{
    // Arrange
    auto fib_helper = std::make_shared<FibHelper>();
    fib_helper->generateFibCache();
    Knights knights{fib_helper};
    unsigned int num_knights{5};

    // Act
    knights.determineSeatingOrder(num_knights);

    // Assert
    ASSERT_EQ(knights.seating_order.at(0),4);
    ASSERT_EQ(knights.seating_order.at(1),1);
    ASSERT_EQ(knights.seating_order.at(2),2);
    ASSERT_EQ(knights.seating_order.at(3),3);
    ASSERT_EQ(knights.seating_order.at(4),5);
}

