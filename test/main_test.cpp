#include "gtest/gtest.h"

/*
 * main_test.cpp can be used for all test executables.
 */
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
