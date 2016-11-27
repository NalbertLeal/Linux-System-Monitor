#ifndef MEMORY_H
#define MEMORY_H

#include <string>

class Memory
{
public:
    Memory();

    void getMemory();

    double getSwapTotal();
    double getSwapNow();
    double percentageSwap();

    double getMemoryAvaliable();
    double getTotalMemory();
    double getMemoryNow();

    double getPercentageUsed();

private:

    double swapTotal;
    double swapNow;

    double memoryAvaliable;
    double totalMemory;
    double memoryNow;
};

#endif // MEMORY_H
