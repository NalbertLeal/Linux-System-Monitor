#include "cpuCore.h"
#include <string>

CpuCore::CpuCore(std::string auxNumber, long auxPUsage, long auxCpu, long auxPercentage) {
    number = auxNumber;
    usage = auxPUsage;
    cpu = auxCpu;
    percentage = percentage;
}

std::string CpuCore::getNumber() {
    return number;
}

long CpuCore::getUsage() {
    return usage;
}

long CpuCore::getCpu() {
    return cpu;
}

long CpuCore::getPercentage() {
    return cpu;
}
