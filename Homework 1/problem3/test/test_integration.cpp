/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 8/24/2019
Description: 
*/

#include <gtest/gtest.h>

#include <knights.hpp>
#include <fib_helper.hpp>

TEST(TestIntegration, TestKnightOrders7)
{
    // Arrange
    auto fib_helper = std::make_shared<FibHelper>();
    fib_helper->generateFibCache();
    Knights knights{fib_helper};
    unsigned int num_knights{7};

    // Act
    knights.initializeKnights(num_knights);
    knights.determineSeatingOrder();

    // Assert
    ASSERT_EQ(knights.seating_order.at(0),4);
    ASSERT_EQ(knights.seating_order.at(1),1);
    ASSERT_EQ(knights.seating_order.at(2),7);
    ASSERT_EQ(knights.seating_order.at(3),6);
    ASSERT_EQ(knights.seating_order.at(4),2);
    ASSERT_EQ(knights.seating_order.at(5),3);
    ASSERT_EQ(knights.seating_order.at(6),5);
}

TEST(TestIntegration, TestKnightOrders5)
{
    // Arrange
    auto fib_helper = std::make_shared<FibHelper>();
    fib_helper->generateFibCache();
    Knights knights{fib_helper};
    unsigned int num_knights{5};

    // Act
    knights.initializeKnights(num_knights);
    knights.determineSeatingOrder();

    // Assert
    ASSERT_EQ(knights.seating_order.at(0),4);
    ASSERT_EQ(knights.seating_order.at(1),1);
    ASSERT_EQ(knights.seating_order.at(2),2);
    ASSERT_EQ(knights.seating_order.at(3),3);
    ASSERT_EQ(knights.seating_order.at(4),5);
}

