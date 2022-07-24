#include <rapidcheck.h>
#include <vector>
#include <cstdlib>

#include "solution.h"

namespace {
double median(const std::vector<int> &v) {
  if (v.size() % 2 == 0) {
    return (v[v.size() / 2] + v[v.size() / 2 - 1]) / 2.0;
  }
  return v[v.size() / 2];
}
}

int main() {
  // https://github.com/emil-e/rapidcheck/blob/master/doc/configuration.md
  putenv("RC_PARAMS=max_success=100000");
  rc::check("median of two sorted lists",
            [](std::tuple<std::vector<int>, std::vector<int>> arg) {
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

              RC_ASSERT(std::abs(median(combined) - solution(v0, v1)) < 1e-6);
            });

  return 0;
}
