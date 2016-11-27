#include <stdlib.h>
#include <fstream>
#include <sstream>

#include "Energy.h"


Energy::Energy()
{
    getFileData();
}

void Energy::getFileData() {
    system("acpi -b >> energy.txt");
    std::ifstream file;
    file.open("energy.txt");

    std::string auxD;
    file >> auxD;
    file >> auxD;
    file >> auxD;
    if(auxD == "Full,") {
        file >> auxD;

        if(auxD.size() == 4) {
            if(auxD[3] == '%') {
                percentage = 100;
            }
        }
        else {
            std::string auxPercentage = "";
            auxPercentage = auxD[0] + auxD[1];

            std::stringstream ss(auxPercentage);
            ss >> percentage;
        }
    }
    else if(auxD == "Discharging,") {
        file >> auxD;

        std::string auxPercentage = "";
        for(int index = 0; index < auxD.size(); index++) {
            if(isdigit(auxD[index])) {
                auxPercentage = auxPercentage + auxD[index];
            }
        }

        std::string::size_type sz;
        percentage = std::stod(auxPercentage, &sz);

        file >> timeToDischarge;

        hourToDischarge = "";
        minutesToDischarge = "";
        int firstPoint = 0;
        for(int index = 0; index < timeToDischarge.size(); index++) {
            if(timeToDischarge[index] == ':') {
                firstPoint = index;
                break;
            }
            if(isdigit(timeToDischarge[index])) {
                hourToDischarge = hourToDischarge + timeToDischarge[index];
            }
        }

        for(int index = firstPoint; index < timeToDischarge.size(); index++) {
            if(timeToDischarge[index] == ':') {
                break;
            }
            if(isdigit(timeToDischarge[index])) {
                minutesToDischarge = minutesToDischarge + timeToDischarge[index];
            }
        }

        hourToDischargeDouble = std::stod(hourToDischarge, &sz);
        minutesToDischargeDouble = std::stod(minutesToDischarge, &sz);
        totalToDischargeDouble = hourToDischargeDouble + minutesToDischargeDouble;
    }
    else {
        file >> auxD;

        std::string auxPercentage = "";
        for(int index = 0; index < auxD.size(); index++) {
            if(isdigit(auxD[index])) {
                auxPercentage = auxPercentage + auxD[index];
            }
        }

        std::string::size_type sz;
        percentage = std::stod(auxPercentage, &sz);

        totalToDischargeDouble = 0;
    }
}

double Energy::getPercentage() {
    return percentage;
}

double Energy::getTimeToDischage() {
    return totalToDischargeDouble;
}
