#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp
  void set_pid(int p);
  void set_user(std::string s);
  void set_command(std::string c);
  void set_cpu(float);
  void set_ram(std::string r);
  void set_uptime(long int u);
  // TODO: Declare any necessary private members
 private:
  int pid;
  std::string command;
  float CpuUtil;
  std::string ram;
  long int uptime;
};

#endif