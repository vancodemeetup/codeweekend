#include <iostream>
#include <vector>

// https://leetcode.com/problems/longest-common-prefix/description/

std::string longestCommonPrefix (std::vector<std::string> &strs)
{
  std::string prefix;

  if (strs.empty ()) {
    // no strings in list, return empty prefix
    return prefix;
  }

  // find minimum string length
  size_t minimum_length = strs [0].length ();
  for (size_t i = 1; i < strs.size (); i++) {
    if (strs [i].length () < minimum_length) {
      minimum_length = strs [i].length ();
    }
  }

  // for every character of the first word up to minimum length
  for (size_t i = 0; i < minimum_length; i++) {
    char c = strs [0] [i];
    // check every character at the same index of every other word
    for (size_t j = 1; j < strs.size (); j++) {
      if (c != strs [j] [i]) {
        // different character, return what was collected in prefix
        // until this point
        return prefix;
      }
    }
    // appending single characters isn't efficient, but hey
    prefix+= c;
  }

  return prefix;
}

int main ()
{
  std::cout << "main" << std::endl;

  std::vector<std::string> strs1 = {"flower", "flow", "flight"};
  std::vector<std::string> strs2 = {"dog", "racecar", "car"};
  std::vector<std::string> strs3 = {"dog", "dog", "dog"};
  std::vector<std::string> strs4 = {"", "dog"};
  std::vector<std::string> strs5 = {""};
  std::vector<std::string> strs6 = {};

  std::cout << "strs1: [" << longestCommonPrefix (strs1) << "]" << std::endl;
  std::cout << "strs2: [" << longestCommonPrefix (strs2) << "]" << std::endl;
  std::cout << "strs3: [" << longestCommonPrefix (strs3) << "]" << std::endl;
  std::cout << "strs4: [" << longestCommonPrefix (strs4) << "]" << std::endl;
  std::cout << "strs5: [" << longestCommonPrefix (strs5) << "]" << std::endl;
  std::cout << "strs6: [" << longestCommonPrefix (strs6) << "]" << std::endl;

  return 0;
}
