#ifndef CPU_H
#define CPU_H


#include <string>
#include <vector>
#include "cpuCore.h"

class CPU
{
public:
    CPU();
    ~CPU();

    void getDataFile(int);
    long getCorePercentage(int);
    long getCpuNumber();
    void getDataNow();
private:
    std::string dataFile;
    long totalCpu;
    long cpuNumber;
    std::vector<CpuCore*> oldCoresVector;
    std::vector<CpuCore*> coresVector;
};

#endif // CPU_H
