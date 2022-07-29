#include <algorithm>

#include "solution.h"

namespace {
bool greater(ListNode *a, ListNode *b) { return a->val > b->val; }
}

ListNode* mergeKLists(std::vector<ListNode*>& lists) {
  std::vector<ListNode*> heads;
  for (ListNode *head : lists) {
    if (head) {
      heads.push_back(head);
    }
  }
  // Using greater causes make_heap to produce a min heap.
  std::make_heap(heads.begin(), heads.end(), greater);
  ListNode synthetic_head(0, nullptr);
  ListNode *last = &synthetic_head;

  while(!heads.empty()) {
    std::pop_heap(heads.begin(), heads.end(), greater);
    ListNode *min = heads.back();
    heads.pop_back();

    last->next = min;
    last = min;

    ListNode *min_next = min->next;
    min->next = nullptr;

    if (min_next) {
      heads.push_back(min_next);
      std::push_heap(heads.begin(), heads.end(), greater);
    }
  }

  return synthetic_head.next;
}
