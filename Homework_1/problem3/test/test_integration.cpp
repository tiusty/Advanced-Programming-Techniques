/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 8/24/2019
Description:
 Integration tests to test full program
*/

#include <gtest/gtest.h>

#include "table.hpp"
#include "fib_helper.hpp"

/**
 * Test that 7 knights are properly seated
 */
TEST(TestIntegration, TestKnightOrders7)
{
    // Arrange
    auto fib_helper = std::make_shared<FibHelper>();
    fib_helper->generateFibCache();
    Table table{fib_helper};
    unsigned int num_knights{7};

    // Act
    table.determineSeatingOrder(num_knights);

    // Assert
    ASSERT_EQ(table.seatingOrder.at(0), 4);
    ASSERT_EQ(table.seatingOrder.at(1), 1);
    ASSERT_EQ(table.seatingOrder.at(2), 7);
    ASSERT_EQ(table.seatingOrder.at(3), 6);
    ASSERT_EQ(table.seatingOrder.at(4), 2);
    ASSERT_EQ(table.seatingOrder.at(5), 3);
    ASSERT_EQ(table.seatingOrder.at(6), 5);
}

/**
 * Test that 5 knights are properly seated
 */
TEST(TestIntegration, TestKnightOrders5)
{
    // Arrange
    auto fib_helper = std::make_shared<FibHelper>();
    fib_helper->generateFibCache();
    Table knights{fib_helper};
    unsigned int num_knights{5};

    // Act
    knights.determineSeatingOrder(num_knights);

    // Assert
    ASSERT_EQ(knights.seatingOrder.at(0), 4);
    ASSERT_EQ(knights.seatingOrder.at(1), 1);
    ASSERT_EQ(knights.seatingOrder.at(2), 2);
    ASSERT_EQ(knights.seatingOrder.at(3), 3);
    ASSERT_EQ(knights.seatingOrder.at(4), 5);
}

/**
 *
 * Test that 10 knights can't be seated
 */
TEST(TestIntegration, TestKnightOrders10)
{
    // Arrange
    auto fib_helper = std::make_shared<FibHelper>();
    fib_helper->generateFibCache();
    Table knights{fib_helper};
    unsigned int num_knights{10};

    // Act
    knights.determineSeatingOrder(num_knights);

    // Assert
    ASSERT_EQ(knights.seatingIndex, 0);
}
