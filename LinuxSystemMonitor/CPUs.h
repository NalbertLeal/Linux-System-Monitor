#ifndef CPUS_H
#define CPUS_H

#include <string>
#include <vector>
#include <thread>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>

class CPUs
{
public:
    CPUs() {
        getNumberOfCores();
        getCoresData();

        coresReady.resize(0);
        for(int index = 0; index < numberOfCores; index++) {
            cpuCore auxcore;
            auxcore.previous_idle_time = 0;
            auxcore.previous_total_time = 0;
            auxcore.idle_time = 0;
            auxcore.total_time = 0;

            coresReady.push_back(auxcore);
        }

        organizeData();
    }

    int nCores() {
        return numberOfCores;
    }

    void getNumberOfCores() {
      system("nproc >> cores.txt");
      std::ifstream file;
      file.open("cores.txt");

      file >> numberOfCores;

      system("rm cores.txt");
    }

    void getCoresData() {
        coreData.resize(0);
        system("cat /proc/stat >> cores.txt");

        std::ifstream file;
        file.open("cores.txt");

        std::string line;
        int counter = numberOfCores;
        while(getline(file, line) && 0 < counter) {
            std::string isCore;
            std::stringstream ss(line);

            ss >> isCore;
            if(isCore == "cpu") {
                continue;
            }

            std::vector<double> auxVec;

            for(int index = 0; index < 10; index++) {
                double auxData;
                ss >> auxData;
                auxVec.push_back(auxData);
            }
            coreData.push_back(auxVec);

            counter--;
        }
        file.close();
        system("rm cores.txt");
    }

    void organizeData() {
        for(int index = 0; index < numberOfCores; index++) {
            coresReady[index].idle_time = coreData[index][3];
            double auxD = 0;
            for(int index2 = 0; index2 < coreData[index].size(); index2++) {
                auxD = auxD + coreData[index][index2];
            }
            coresReady[index].total_time = auxD;
        }
    }

    double updateCpuCores() {
        getCoresData();

        for(int index = 0; index < numberOfCores; index++) {
            coresReady[index].previous_idle_time = coresReady[index].idle_time;
            coresReady[index].previous_total_time = coresReady[index].total_time;
        }

        organizeData();
    }

    double corePercentage(int coreNumber) {
        return (double) (100.0 * (1.0 - (coresReady[coreNumber-1].idle_time - coresReady[coreNumber-1].previous_idle_time) / (coresReady[coreNumber-1].total_time - coresReady[coreNumber-1].previous_total_time)));
    }


private:
    double numberOfCores;

    struct cpuCore {
        double previous_idle_time;
        double previous_total_time;
        double idle_time;
        double total_time;
    };

    std::vector<std::vector<double>> coreData;
    std::vector<cpuCore> coresReady;
    std::vector<double> percetages;
};

#endif
