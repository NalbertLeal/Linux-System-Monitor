#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>

#include "memory.h"

Memory::Memory()
{
    getMemory();
}

void Memory::getMemory() {
    // swap

    system("cat /proc/meminfo >> memU1.txt");
    std::ifstream file;
    file.open("memU1.txt");

    std::string auxTotalMemory = "";
    std::string auxMemoryNow = "";
    std::string line = "";
    int count = 1;
    while(std::getline(file, line)) {
        if(count == 6) {
            std::string auxD;
            std::stringstream ss(line);
            ss >> auxMemoryNow;
            ss >> swapNow;
        }
        else if(count == 7) {
            std::string auxD;
            std::stringstream ss(line);
            ss >> auxTotalMemory;
            ss >> swapTotal;
        }
        count++;
    }
    file.close();
    system("rm memU1.txt");


    // ram
    system("free -m >> memU.txt");
    std::ifstream file2;
    file2.open("memU.txt");

    line = "";
    count = 0;
        while(std::getline(file2, line)) {
            if(count == 2) {
                std::stringstream ss(line);
                std::string auxD;
                ss >> auxD;
                ss >> auxD;

                ss >> memoryNow;

            }
            if(count == 0 || count > 1) {
              count++;
              continue;
            }
            std::stringstream ss(line);

            std::string auxD;
            ss >> auxD;
            ss >> totalMemory;

            count++;
        }
        file2.close();
        system("rm memU.txt");
}

double Memory::getMemoryAvaliable() {
    return memoryAvaliable;
}

double Memory::getTotalMemory() {
    return totalMemory;
}

double Memory::getMemoryNow() {
    return memoryNow;
}

double Memory::getPercentageUsed() {
    return (memoryNow/totalMemory) * 100.0;
}

double Memory::getSwapTotal() {
    return swapTotal;
}

double Memory::getSwapNow() {
    return swapNow;
}

double Memory::percentageSwap() {
    return (swapNow / swapTotal) * 100;
}
