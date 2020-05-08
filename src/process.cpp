#include "process.h"
#include <cassert>
#include <unistd.h>

#include <cctype>
#include <sstream>
#include <string>
#include <vector>

using std::string;
using std::to_string;
using std::vector;

void Process::set_pid(int p){
  pid = p;
  cpu_util = CpuUtilization();
  cmnd = LinuxParser::Command(Pid());
}

// TODO: Return this process's ID
int Process::Pid() { return pid; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
  long int Hz = sysconf(_SC_CLK_TCK);
  float total_time = LinuxParser::ActiveJiffies(pid)/ Hz; 
  float seconds = LinuxParser::UpTime(pid);
  return total_time/seconds;
}

// TODO: Return the command that generated this process
string Process::Command() { return cmnd; }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a [[maybe_unused]]) const {
  return cpu_util > a.cpu_util;
}