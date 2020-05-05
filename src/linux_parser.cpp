#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <string>
#include <vector>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  vector<int> cpus;
  float total_memory, memory_free;
  string line, garb;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    std::getline(stream, line);
    std::istringstream linestream2(line);
    linestream >> garb >> total_memory;
    linestream2 >> garb >> memory_free;
  }
  float utilization = 1 - (memory_free / total_memory);

  return utilization;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  long uptime;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime;
  }
  return uptime;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid [[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
float LinuxParser::CpuUtilization() {
  vector<int> cpus;
  int cps, total_time = 0, idle;
  string line, garb;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> garb;
    while (linestream >> cps) {
      cpus.push_back(cps);
      total_time += cps;
    }
  }
  idle = cpus[3];
  float utilization = 1.0 - (float(idle) / float(total_time));

  return utilization;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  int total;
  string line, garb;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (garb != "processes") {
      std::getline(stream, line);
      std::istringstream linestream(line);
      linestream >> garb;
      if (garb == "processes") linestream >> total;
    }
  }
  return total;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  int total = 0;
  string line, garb;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (garb != "procs_running") {
      std::getline(stream, line);
      std::istringstream linestream(line);
      linestream >> garb;
      if (garb == "procs_running") {
        linestream >> total;
        break;
      }
    }
  }
  return total;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  string line;
  std::ifstream stream((kProcDirectory + to_string(pid) + "/" + kCmdlineFilename));
  if (stream.is_open()) {
      std::getline(stream, line);
  }
  return line;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid [[maybe_unused]]) { 
  string line,garb;
  int ram;
  std::ifstream stream((kProcDirectory + to_string(pid) + "/" + kStatusFilename));
  if (stream.is_open()) {
      while(std::getline(stream, line)){
        std::istringstream linestream(line);
        linestream >> garb;
        if (garb=="VmSize:"){
          linestream >> ram;
          break;
        }

      }
  }

  ram = ram / 1024;
  return to_string(ram);
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid [[maybe_unused]]) { 
  string line,garb;
  int uid;
  std::ifstream stream((kProcDirectory + to_string(pid) + "/" + kStatusFilename));
  if (stream.is_open()) {
      while(std::getline(stream, line)){
        std::istringstream linestream(line);
        linestream >> garb;
        if (garb=="Uid:"){
          linestream >> uid;
          break;
        }

      }
  }
  return to_string(uid);
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid [[maybe_unused]]) { 
  string line, garb;
  vector<std::string> useful;
  std::ifstream stream((kPasswordPath));
  if (stream.is_open()) {
    while(std::getline(stream, line)){
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> garb;
      useful.push_back(garb);
    }
  }
  
  return useful[42];
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid [[maybe_unused]]) { 
  string line, garb;
  long useful;
  std::ifstream stream((kProcDirectory + to_string(pid) + "/" + kStatFilename));
  if (stream.is_open()) {
      std::getline(stream, line);
      std::istringstream linestream(line);
      for( int i = 0; i < 21 ; i++) stream >> garb;
      linestream >> useful;

  }
  useful = useful / sysconf(_SC_CLK_TCK);
  useful = LinuxParser::UpTime() - useful;
  return useful; 
 }