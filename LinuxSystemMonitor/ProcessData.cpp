#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <stdio.h>

#include "ProcessData.h"
#include "process.h"

ProcessData::ProcessData() {
    ProcessFileData = "";
    processDataVector.resize(0);

    getProcessFileData();
}

void ProcessData::putOnVector(Process *&p) {
    processDataVector.push_back(p);
}

int ProcessData::getNumberOfProcess(void) {
  return processDataVector.size();
}

Process* ProcessData::getProcessByIndex(int index) {
    if(index  < processDataVector.size()) {
      return processDataVector[index];
    }
    else {
      Process *p = new Process();
      return p;
    }
}

void ProcessData::getProcessFileData(void) {
    processDataVector.resize(0);

    std::string auxSystemProcessData;

    std::ifstream fileTxt;
    fileTxt.open("text.txt");

    bool txtExist = false;
    if(fileTxt.is_open()) {
      txtExist = true;
    }
    fileTxt.close();

    if(txtExist) {
      system("rm text.txt");
    }

    auxSystemProcessData = system("ps axo comm,pcpu,pmem,pid,ppid,nlwp >> text.txt");

    //read file
    std::ifstream file;
    file.open("text.txt");

    std::string line;
    int counter = 0;
    while(getline(file, line)) {
      if(counter == 0) {
          counter++;
          continue;
      }
      std::stringstream ss(line);

      std::string name = "";
      double memmory;
      double cpu;
      int thread;
      int pid;
      int ppid;

      ss >> name;
      ss >> cpu;
      ss >> memmory;
      ss >> ppid;
      ss >> thread;
      ss >> pid;

      Process *p = new Process(name, memmory, cpu, pid, ppid, thread);
      putOnVector(p);

      ss.clear();
    }
    file.close();

    system("rm text.txt");

}
