#include <iostream>
#include <vector>
#include <cstdint>


bool equalFrequency (std::string word)
{
  // only 2-100 characters in the input word, uint8_t as counter
  // should be enough
  std::vector<uint8_t> seen (256, 0);

  if (word.length () <= 1) {
    return true;
  }

  for (const uint8_t c : word) {
    seen [c]++;
  }

  uint8_t min_seen = ~0, max_seen = 0, num_seen = 0;
  uint32_t sum = 0;
  for (const uint8_t count : seen) {
    if (count > 0) {
      if (count < min_seen) {
        min_seen = count;
      }
      if (max_seen < count) {
        max_seen = count;
      }
      sum+= count;
      num_seen++;
    }
  }

  uint32_t num_times_min = (uint32_t) num_seen * (uint32_t) min_seen;
  uint32_t num_times_max = ((uint32_t) num_seen - 1) * (uint32_t) max_seen;
  if (num_seen == 1) { // "aaa"
    return true;
  }

  if (sum == num_times_min + 1) { // "aabbb"
    return true;
  }

  if (sum == num_times_max + 1) { // "aab"
    return true;
  }

  return false;
}


int main ()
{
  std::vector<std::string> tests = {"", "a", "acdc", "aaa", "aabbb", "aaab", "aaaxb", "aazz"};

  for (auto &s : tests) {
    std::cout << "[" << s << "] : " << equalFrequency (s) << std::endl;
  }

  return 0;
}
