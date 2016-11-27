#ifndef CPUCORE_H
#define CPUCORE_H

#include <string>

class CpuCore {
public:
    CpuCore(std::string, long, long, long);
    ~CpuCore();

    std::string getNumber();
    long getUsage();
    long getCpu();
    long getPercentage();

private:
    std::string number;
    long usage;
    long cpu;
    long percentage;
};

#endif // CPUCORE_H
