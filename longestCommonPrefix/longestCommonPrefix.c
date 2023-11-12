#include <stdio.h>
#include <string.h>


char *longest_common_prefix (const char *strs [])
{
  // max 200 character string length as per problem statement, add one
  // for trailing '\0'
  static char prefix [200 + 1];

  memset (prefix, 0x00, sizeof (prefix));

  if (strs == NULL || strs [0] == NULL) {
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
    for (j = 1; strs [j]; j++) {
      if (c != strs [j] [i]) {
        // done or different character, return what was collected in
        // prefix until this point
        return prefix;
      }
    }
    prefix [i] = c;
    i++;
  } while (c != '\0');

  return prefix;
}


int main ()
{
  const char *strs1 [] = {"flower", "flow", "flight", NULL};
  const char *strs2 [] = {"dog", "racecar", "car", NULL};
  const char *strs3 [] = {"dog", "dog", "dog", NULL};
  const char *strs4 [] = {"", "dog", NULL};
  const char *strs5 [] = {"", NULL};
  const char *strs6 [] = {NULL};

  printf ("strs1: [%s]\n", longest_common_prefix (strs1));
  printf ("strs2: [%s]\n", longest_common_prefix (strs2));
  printf ("strs3: [%s]\n", longest_common_prefix (strs3));
  printf ("strs4: [%s]\n", longest_common_prefix (strs4));
  printf ("strs5: [%s]\n", longest_common_prefix (strs5));
  printf ("strs6: [%s]\n", longest_common_prefix (strs6));

  return 0;
}
