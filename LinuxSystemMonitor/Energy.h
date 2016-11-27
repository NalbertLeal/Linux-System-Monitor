#ifndef ENERGY_H
#define ENERGY_H

#include <string>

class Energy
{
public:
    Energy();

    void getFileData();

    double getPercentage();
    double getTimeToDischage();

private:
    double percentage;
    double hourToDischargeDouble;
    double minutesToDischargeDouble;
    double totalToDischargeDouble;

    std::string timeToDischarge;
    std::string hourToDischarge;
    std::string minutesToDischarge;
};

#endif // ENERGY_H
