#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

// https://leetcode.com/problems/subsets-ii

std::vector<std::vector<int>> subsetsWithDup (std::vector<int> &nums)
{
  // length of nums is 10 at most
  const size_t size = nums.size ();
  const uint32_t resultCount = 1 << size;
  std::set<std::vector<int>> resultSet;
  std::vector<std::vector<int>> result;

  std::sort (nums.begin (), nums.end ());

  std::vector<int> a;
  for (uint32_t bits = 0; bits < resultCount; bits++) {
    for (uint32_t i = 0; i < size; i++) {
      if ((1 << i) & bits) {
        a.push_back (nums [i]);
      }
    }
    resultSet.insert (a);
    a.clear ();
  }

  for (auto &r : resultSet) {
    result.push_back (r);
  }

  return result;
}

int main ()
{
  std::vector<int> test =
    {1, 2, 3, 4, 5, 6, 5, 5, 2, 1};

  const auto r = subsetsWithDup (test);
  std::cout << "r size: " << r.size () << std::endl;
  for (const auto &l : r) {
    for (const auto &i : l) {
      std::cout << " [" << i << "]";
    }
    std::cout << std::endl;
  }

  return 0;
}
