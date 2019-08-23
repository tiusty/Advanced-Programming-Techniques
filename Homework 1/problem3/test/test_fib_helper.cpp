/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 8/23/2019
Description:
 Tests fib_helper class
*/
#include <gtest/gtest.h>

#include "fib_helper.hpp"

TEST(FibHelper, TestCheckFibPairs)
{
    // Arrange
    FibHelper fib_helper;
    fib_helper.fib_cache.at(0) = 1;
    fib_helper.fib_cache.at(1) = 1;
    fib_helper.fib_cache.at(2) = 2;
    fib_helper.fib_cache.at(3) = 3;
    fib_helper.fib_cache.at(4) = 5;

    // Act / Assert
    ASSERT_TRUE(fib_helper.checkFibPairs(1,1));
    ASSERT_TRUE(fib_helper.checkFibPairs(1,2));
    ASSERT_TRUE(fib_helper.checkFibPairs(1,4));
    ASSERT_TRUE(fib_helper.checkFibPairs(2,1));
    ASSERT_TRUE(fib_helper.checkFibPairs(2,3));
    ASSERT_TRUE(fib_helper.checkFibPairs(3,2));
    ASSERT_TRUE(fib_helper.checkFibPairs(2,3));

    ASSERT_FALSE(fib_helper.checkFibPairs(1,3));
    ASSERT_FALSE(fib_helper.checkFibPairs(2,4));
    ASSERT_FALSE(fib_helper.checkFibPairs(1,5));
    ASSERT_FALSE(fib_helper.checkFibPairs(4,2));
}

