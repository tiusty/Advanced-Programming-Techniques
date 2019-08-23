/*
Author: Alex Agudelo
Class: ECE 6122
Last date modified: 8/23/2019
Description:
Runs all unittests
*/
#include <gtest/gtest.h>

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
