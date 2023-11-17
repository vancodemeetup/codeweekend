#include <stdio.h>
#include <string.h>

/* https://leetcode.com/problems/longest-common-prefix/description/ */

char* longestCommonPrefix (char** strs, int strsSize)
{
  // max 200 character string length as per problem statement, add one
  // for trailing '\0'
  // returning a static is not good - but good enough for leetcode?
  static char prefix [200 + 1];

  if (strsSize == 0) {
    // no strings in list, return empty prefix
    return prefix;
  }

  size_t i = 0;
  char c;
  do {
    // for every character of the first word
    c = strs [0] [i];
    // check every character at the same index of every other word
    size_t j;
    for (j = 1; j < strsSize; j++) {
      if (c != strs [j] [i]) {
        // done or different character, return what was collected in
        // prefix until this point
        prefix [i] = '\0';
        return prefix;
      }
    }
    prefix [i] = c;
    i++;
  } while (c != '\0');

  prefix [i] = '\0';
  return prefix;
}


int main ()
{
  char *strs1 [] = {"flower", "flow", "flight"};
  char *strs2 [] = {"dog", "racecar", "car"};
  char *strs3 [] = {"dog", "dog", "dog"};
  char *strs4 [] = {"", "dog"};
  char *strs5 [] = {""};
  char *strs6 [] = {};

  printf ("strs1: [%s]\n", longestCommonPrefix (strs1, sizeof (strs1) / sizeof (strs1 [0])));
  printf ("strs2: [%s]\n", longestCommonPrefix (strs2, sizeof (strs2) / sizeof (strs2 [0])));
  printf ("strs3: [%s]\n", longestCommonPrefix (strs3, sizeof (strs3) / sizeof (strs3 [0])));
  printf ("strs4: [%s]\n", longestCommonPrefix (strs4, sizeof (strs4) / sizeof (strs4 [0])));
  printf ("strs5: [%s]\n", longestCommonPrefix (strs5, sizeof (strs5) / sizeof (strs5 [0])));
  printf ("strs6: [%s]\n", longestCommonPrefix (strs6, sizeof (strs6) / sizeof (strs6 [0])));

  return 0;
}
