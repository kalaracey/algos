#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>
#include <cstdlib>
#include <iostream>

#include "solution.h"

std::vector<std::unique_ptr<ListNode>>
vector_to_list(const std::vector<int> &v) {
  std::vector<std::unique_ptr<ListNode>> result;
  std::vector<int> sorted(v.begin(), v.end());
  std::sort(sorted.begin(), sorted.end());
  ListNode *last = nullptr;
  for (int i : sorted) {
    auto node = std::make_unique<ListNode>(i);
    node->val = i;
    if (last) {
      last->next = &(*node);
    }
    last = &(*node);
    result.push_back(std::move(node));
  }
  if (!v.empty()) {
    last->next = nullptr;
  }
  return result;
}

std::vector<int> list_to_vector(ListNode *list) {
  std::vector<int> result;
  while (list) {
    result.push_back(list->val);
    list = list->next;
  }
  return result;
}

TEST(SolutionTest, Empty) {
  std::vector<ListNode *> v;
  EXPECT_EQ(mergeKLists(v), nullptr);
}

void run(const std::vector<std::vector<int>> &vs, std::function<void(const std::vector<int>& a, const std::vector<int>& b)> assertion) {
  std::vector<std::vector<std::unique_ptr<ListNode>>> memory;
  for (const std::vector<int> &v : vs) {
    memory.push_back(vector_to_list(v));
  }
  std::vector<ListNode *> heads;
  for (std::vector<std::unique_ptr<ListNode>> &v : memory) {
    if (!v.empty()) {
      heads.push_back(&(*v[0]));
    }
  }
  std::vector<int> expected;
  for (const std::vector<int> &v : vs) {
    expected.insert(expected.end(), v.begin(), v.end());
  }
  std::sort(expected.begin(), expected.end());

  //  std::cerr << "foo" << std::endl;
  auto result = mergeKLists(heads);
  //  std::cerr << "bar" << std::endl;
  auto result2 = list_to_vector(result);
  //  std::cerr << "baz" << std::endl;
  assertion(result2, expected);
}

void run(const std::vector<std::vector<int>> &vs) {
  run(vs, [](const std::vector<int>& a, const std::vector<int>& b) {
    EXPECT_EQ(a, b);
  });
}

TEST(SolutionTest, One) { run({{5, 2, 8, 6, 6, 4, 9}}); }

TEST(SolutionTest, Two) { run({{5, 2, 8, 6, 6, 4, 9}, {8, 6, 6}}); }

RC_GTEST_PROP(SolutionTest, RapidCheck, (std::vector<std::vector<int>> vs)) {
  run(vs, [](const std::vector<int>& a, const std::vector<int>& b) {
    RC_ASSERT(a == b);
  });
}

int main(int argc, char **argv) {
//  putenv("RC_PARAMS=max_success=1000");
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
