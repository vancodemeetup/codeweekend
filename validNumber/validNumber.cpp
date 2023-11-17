#include <iostream>
#include <vector>


bool isNumber (std::string s)
{
  // typed up from hand-drawn deterministic automaton

  enum State { S0, S1, S2, S3, S4, S5, S6, S7, S8 };
  State state {S0};

  std::string::iterator it = s.begin ();

  for (;;) {
    // std::cout << "c: " << *it << ", state: " << state << std::endl;

    switch (state) {
    case S0:
      if (it == s.end ()) {
        return false;
      } else if (*it == '+' || *it == '-') {
        state = S1;
      } else if (isdigit (*it)) {
        state = S2;
      } else if (*it == '.') {
        state = S3;
      } else {
        return false;
      }
      break;

    case S1:
      if (it == s.end ()) {
        return false;
      } else if (isdigit (*it)) {
        state = S2;
      } else if (*it == '.') {
        state = S3;
      } else {
        return false;
      }
      break;

    case S2:
      if (it == s.end ()) {
        // integer
        return true;
      } else if (isdigit (*it)) {
        // state = S2;
      } else if (*it == '.') {
        state = S6;
      } else if (*it == 'e' || *it == 'E') {
        state = S5;
      } else {
        return false;
      }
      break;

    case S3:
      if (it == s.end ()) {
        return false;
      } else if (isdigit (*it)) {
        state = S4;
      } else {
        return false;
      }
      break;

    case S4:
      if (it == s.end ()) {
        return true;
      } else if (isdigit (*it)) {
        state = S4;
      } else if (*it == 'e' || *it == 'E') {
        state = S5;
      } else {
        return false;
      }
      break;

    case S5:
      // at least one digit after e/E
      if (it == s.end ()) {
        return false;
      } else if (isdigit (*it)) {
        state = S8;
      } else if (*it == '+' || *it == '-') {
        state = S7;
      } else {
        return false;
      }
      break;

    case S6:
      if (it == s.end ()) {
        return true;
      } else if (isdigit (*it)) {
        // state = S6;
      } else if (*it == 'e' || *it == 'E') {
        state = S5;
      } else {
        return false;
      }
      break;

    case S7:
      if (it == s.end ()) {
        return false;
      } else if (isdigit (*it)) {
        state = S8;
      } else {
        return false;
      }
      break;

    case S8:
      if (it == s.end ()) {
        return true;
      } else if (isdigit (*it)) {
        // state = S8;
      } else {
        return false;
      }
      break;

    default:
      // std::cout << "out default" << std::endl;
      return false;
    }

    it++;
  }

  return true;
}


int main ()
{
  std::vector<std::string> valids =
    {"2", "0089", "-0.1", "+3.14", "4.", "-.9", "2e10", "-90E3", "3e+7", "+6e-1", "53.5e93", "-123.456e789"};

  std::vector<std::string> invalids =
    {"", ".", "-", "e", "x", "abc", "1a", "1e", "e3", "99e2.5", "--6", "-+3", "95a54e53"};

  for (const auto &test : valids) {
    std::cout << "testing valid " << test << ":" << isNumber (test) << std::endl;
  }

  for (const auto &test : invalids) {
    std::cout << "testing invalid " << test << ":" << isNumber (test) << std::endl;
  }

  return 0;
}
