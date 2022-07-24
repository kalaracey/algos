#include "solution.h"

using std::vector;

namespace {

template <typename T> bool even(T t) { return t % 2 == 0; }
template <typename T> bool odd(T t) { return !even(t); }

struct Span {
public:
  Span(const vector<int> &v) : v(v), lb(0), ub(v.size()) {}

  Span left_strip(size_t n) {
    assert(size() > n);
    return {v, lb + n, ub};
  }

  Span right_strip(size_t n) {
    assert(size() > n);
    return {v, lb, ub - n};
  }

  double median() {
    assert(size() > 0);
    if (even(size())) {
      auto lower = v[lb + size() / 2 - 1];
      auto upper = v[lb + size() / 2];
      return lower + (upper-lower) / 2.0;
    }
    return v[lb + size() / 2];
  }

  int operator[](size_t offset) { return v[lb + offset]; }

  size_t size() { return ub - lb; }

  vector<int>::const_iterator lower_bound(int i) {
    return std::lower_bound(v.begin() + lb, v.begin()+ub, i);
  }

  vector<int>::const_iterator begin() {
    return v.begin() + lb;
  }

  vector<int>::const_iterator end() {
    return v.begin() + ub;
  }

private:
  Span(const vector<int> &v, size_t lb, size_t ub) : v(v), lb(lb), ub(ub) {
    assert(ub > lb);
  }
  const vector<int> &v;
  const size_t lb;
  const size_t ub; // Exclusive.
};

// Returns x tuple [x, y], where x.median() <= y.median()
std::tuple<Span, Span> sort(Span x, Span y) {
  return (x.median() <= y.median()) ? std::tie(x, y) : std::tie(y, x);
}

// k is an ordinal (1-based), not an index (0-based).
int kth_smallest(size_t k, Span x, Span y) {
  assert(k <= x.size() + y.size());
  if (x.size() < 3 || y.size() < 3) {
    auto &small = (x.size() < 2) ? x : y;
    auto &other = (x.size() < 2) ? y : x;

    for (auto it = small.begin(); it < small.end(); it++) {
      auto loc = other.lower_bound(*it);
      auto ordinal = loc - other.begin() + 1;
      if (ordinal > k) {
        break;
      } else if (ordinal == k) {
        return *it;
      } else {
        k--;
      }
    }

    return other[k-1];
  }

  auto sorted = sort(x, y);
  auto a = std::get<0>(sorted);
  auto b = std::get<1>(sorted);
  auto n = a.size();
  auto m = b.size();

  if (even(n) && even(m)) {
    // a_0, ..., a_lm have at least |a|/2 + |b|/2 = (|a|+|b|)/2 elements above
    // them.
    // b_um, ..., b_{|b|-1} have at least |b|/2 + |a|/2 = (|a|+|b|)/2 elements
    // below them.

    if (k < (n + m) / 2) {
      // If k < (|a| + |b|)/2, then there are < (|a|+|b|)/2 elements below it.
      // Hence it cannot be in b_um, b_{|b|-1}.
      return kth_smallest(k, a, b.right_strip(m / 2));
    }
    // If k >= (|a|+|b|)/2, then there are <= (|a|+|b|)/2 elements above it.
    // Hence, k cannot be in [a_0, ..., a_lm). (Note the ')' - hence we strip
    // n / 2 - 1.
    return kth_smallest(k - (n / 2 - 1), a.left_strip(n / 2 - 1), b);
  } else if (even(n) && odd(m)) {
    // a_0, ..., a_lm have at least |a|/2 + (|b|+1)/2 = (|a|+|b|+1)/2 elements
    // above them.
    // b_med, ..., b_{|b|-1} have at least (|b|-1)/2 + |a|/2 = (|a|+|b|-1)/2
    // elements below them.
    if (k <= (n + m) / 2) {
      // If k <= (|a|+|b|-1)/2, then there are <= (|a|+|b|-1)/2 elements below
      // it. Hence, k cannot be in (b_med, ..., b_{m-1}] - note the '('.
      return kth_smallest(k, a, b.right_strip((m - 1) / 2));
    }
    // If k > (|a|+|b|)//2, then there are <= (|a|+|b|-1)/2 elements above it.
    // Hence, k cannot be in a_0, ..., a_lm.
    return kth_smallest(k - n / 2, a.left_strip(n / 2), b);
  } else if (odd(n) && even(m)) {
    // a_0, ..., a_med have at least (|a|-1)/2+|b|/2 = (|a|+|b|-1)/2 elements
    // above them.
    // b_um, ..., b_{m-1} have at least (|a|+1)/2 + |b|/2 = (|a|+|b|+1)/2
    // elements below them.

    if (k <= (n + m) / 2) {
      // If k <= (|a|+|b|)/2, then there are < (|a|+|b|)/2 elements below it.
      // Hence, k cannot be in b_um, ..., b_{m-1}.
      return kth_smallest(k, a, b.right_strip(m / 2));
    }
    // If k > (|a|+|b|-1)/2, then there are <= (|a|+|b|-1)/2 elements above it.
    // Hence, k cannot be in [a_0, ..., a_med) (note the ')').
    return kth_smallest(k - n / 2, a.left_strip(n / 2), b);
  } else if (odd(n) && odd(m)) {

    // a_0, ..., a_med have at least (|a|-1)/2 + (|b|+1)/2 = (|a|+|b|)/2
    // elements above them.
    // b_med, ..., b_{|b|-1} have at least (|b|-1)/2 + (|a|+1)/2 = (|a|+|b|)/2
    // elements below them.
    if (k < (n + m) / 2) {
      // If k < (|a|+|b|)/2, then there are < (|a|+|b|)/2 elements below it.
      // Hence, k cannot be in b_med, ..., b_{m-1}.
      return kth_smallest(k, a, b.right_strip((m + 1) / 2));
    }
    // If k >= (|a|+|b|)/2, then there are <= (|a|+|b|)/2 elements above it.
    // Hence, k cannot be in a_0, ..., a_{med-1}.
    return kth_smallest(k - n / 2, a.left_strip(n / 2), b);
  }
  assert(false); // Unreachable,.
}

} // namespace

double solution(const vector<int>& a, const vector<int>& b) {
  auto total = a.size() + b.size();
  if (total % 2 == 0) {
    auto lower = kth_smallest(total / 2 + 0, Span(a), Span(b));
    auto upper = kth_smallest(total / 2 + 1, Span(a), Span(b));
    return (lower + upper) / 2.0;
  } else {
    return kth_smallest(total / 2 + 1, Span(a), Span(b));
  }
}
