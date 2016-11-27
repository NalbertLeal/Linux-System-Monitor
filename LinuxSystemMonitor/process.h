#ifndef PROCESS_H
#define PROCESS_H


#include <string>

class Process {
public:
    Process() {
      /* EMPTY */
    }

    Process(std::string auxName, double auxCpu, double auxMem, int auxThread, int auxPid, int auxPpid) {
      name = auxName;
      memmory = auxCpu;
      cpu = auxMem;
      thread = auxThread;
      pid = auxPid;
      ppid = auxPpid;
    }

    std::string name;
    double memmory;
    double cpu;
    int thread;
    int pid;
    int ppid;
};

#endif // PROCESS_H
