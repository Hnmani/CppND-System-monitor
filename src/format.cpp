#include "format.h"

#include <string>

using std::string;
using std::to_string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
  int ss = seconds % 60;
  int min = (seconds % 3600) / 60;
  int hrs = seconds / 3600;
  string time = to_string(hrs) + ":" + to_string(min) + ":" + to_string(ss);
  return time;
}