#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "linux_parser.h"
#include "process.h"
#include <vector>

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  void addProcess(Process& p);
  // TODO: Declare any necessary private members
 private:
   std::vector<int> processes;

};

#endif