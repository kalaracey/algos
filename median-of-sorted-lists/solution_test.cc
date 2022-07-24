#include <gtest/gtest.h>
#include <cstdlib>
#include <rapidcheck/gtest.h>
#include <vector>

#include "solution.h"

TEST(SolutionTest, EmptyAndOne) {
  EXPECT_EQ(solution({}, {1}), 1);
  EXPECT_EQ(solution({1}, {}), 1);
}

TEST(SolutionTest, EmptyAndTwo) {
  EXPECT_EQ(solution({}, {1,1}), 1);
  EXPECT_EQ(solution({1,1}, {}), 1);
}

TEST(SolutionTest, OneAndOne) {
  EXPECT_EQ(solution({1},{1}), 1);
}

TEST(SolutionTest, TwoAndOne) {
  EXPECT_EQ(solution({1,1},{1}), 1);
  EXPECT_EQ(solution({1,2},{1}), 1);
  EXPECT_EQ(solution({1,2},{2}), 2);
  EXPECT_EQ(solution({1,2},{3}), 2);

  EXPECT_EQ(solution({1},{1,1}), 1);
  EXPECT_EQ(solution({1},{1,2}), 1);
  EXPECT_EQ(solution({1},{2,2}), 2);
  EXPECT_EQ(solution({1},{2,3}), 2);
}

TEST(SolutionTest, ThreeAndTwo) {
  EXPECT_EQ(solution({1,2,3}, {4}), 2.5);
}

TEST(SolutionTest, OneTwoThenThreeFour) {
  EXPECT_EQ(solution({1,2}, {3,4}), 2.5);
  EXPECT_EQ(solution({1,4}, {2,3}), 2.5);
}

TEST(SolutionTest, OneFourThenTwoThree) {
  EXPECT_EQ(solution({1,4}, {2,3}), 2.5);
  EXPECT_EQ(solution({2,3}, {1,4}), 2.5);
}

TEST(SolutionTest, OneThreeThenTwoFour) {
  EXPECT_EQ(solution({1,3}, {2,4}), 2.5);
  EXPECT_EQ(solution({2,4}, {1,3}), 2.5);
}

TEST(SolutionTest, OneTwoThreeThenFourFive) {
  EXPECT_EQ(solution({1,2,3}, {4,5}), 3);
  EXPECT_EQ(solution({4,5}, {1,2,3}), 3);
}

TEST(SolutionTest, OneTwoFiveThenThreeFour) {
  EXPECT_EQ(solution({1,2,5}, {3,4}), 3);
  EXPECT_EQ(solution({3,4},{1,2,5}), 3);
}

TEST(SolutionTest, FourZerosAndFourOnes) {
  EXPECT_EQ(solution({0,1,1,1}, {0,0,0,1}), 0.5);
}

TEST(SolutionTest, TwoNegThreesThenTwoNegFoursThenThreeZeros) {
  EXPECT_EQ(solution({-4, -4, 0, 0}, {-3, -3, 0}), -3);
}

TEST(SolutionTest, Alpha) {
  EXPECT_EQ(solution({0,0,1,1,1}, {0, 0, 0, 0, 1042956301, 1104527347, 1104527347}), 0.5);
}

double median(const std::vector<int>& v) {
  if (v.size() % 2 == 0) {
    return (v[v.size() / 2] + v[v.size() / 2 -1]) / 2.0;
  }
  return v[v.size() / 2];
}

class SolutionTestRapidCheck : public ::testing::Test {
protected:
  SolutionTestRapidCheck() {
    putenv("RC_PARAMS=max_success=100000");
  }
};

RC_GTEST_FIXTURE_PROP(SolutionTestRapidCheck, Test, (std::tuple<std::vector<int>, std::vector<int>> arg)) {
  auto v0 = std::get<0>(arg);
  auto v1 = std::get<1>(arg);
  if (v0.empty() || v1.empty()) {
    return;
  }
  std::vector<int> combined{v0.begin(), v0.end()};
  combined.insert(combined.end(), v1.begin(), v1.end());

  std::sort(v0.begin(), v0.end());
  std::sort(v1.begin(), v1.end());
  std::sort(combined.begin(), combined.end());

//  RC_ASSERT(median(combined) == solution(v0, v1));
  RC_ASSERT(std::abs(median(combined) - solution(v0, v1)) < 1e-6);
}

