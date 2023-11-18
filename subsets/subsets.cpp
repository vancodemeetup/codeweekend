#include <iostream>
#include <vector>

// https://leetcode.com/problems/subsets

std::vector<std::vector<int>> subsets (std::vector<int>& nums)
{
  // length of nums is 10 at most
  const size_t size = nums.size ();
  const uint32_t resultCount = 1 << size;
  // pre-allocate result here with resultCount
  std::vector<std::vector<int>> result (resultCount);

  std::vector<int> a;
  for (uint32_t bits = 0; bits < resultCount; bits++) {
    for (uint32_t i = 0; i < size; i++) {
      if ((1 << i) & bits) {
        a.push_back (nums [i]);
      }
    }
    result [bits] = a;
    a.clear ();
  }

  return result;
}

int main ()
{
  std::vector<int> test =
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  const auto r = subsets (test);
  std::cout << "r size: " << r.size () << std::endl;
  for (const auto &l : r) {
    for (const auto &i : l) {
      std::cout << " [" << i << "]";
    }
    std::cout << std::endl;
  }

  return 0;
}
