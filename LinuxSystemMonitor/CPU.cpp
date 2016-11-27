#include "CPU.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "cpuCore.h"

CPU::CPU()
{
    totalCpu = 0;
    getDataFile(0);
    getDataFile(1);
}

long CPU::getCpuNumber() {
    return cpuNumber;
}

long CPU::getCorePercentage(int index) {
    return coresVector[index]->getPercentage();
}

void CPU::getDataFile(int ON) {
    std::ifstream file;
          file.open("/proc/stat");

          if(!(file.is_open())) {
            file.close();
            exit(1);
          }

          std::string finalString;
          std::string line;
          std::string number = "";
          std::string v1, v2, v3, v4, v5, v6, v7, v8, v9, v10;
          int counter = 1;
          while(!(file.eof())) {
            std::getline(file, line);
            finalString = finalString + "\n" + line;
            for(int index = 0; index < line.length(); index++) {
                if((line[0] == 'c' && line[1] == 'p') && line[2] == 'u') {
                    if(index < 4) {
                        if(line[index] == ' ') {
                            continue;
                        }
                        if(isdigit(line[3] && isdigit(line[4]))) {
                            number = "" + line[3] + line[4];
                        }
                        else {
                            number = line[3];
                        }
                    }
                    else {
//                      if(number == "" || number == " ") {
//                        break;
//                      }
                        if(line[index] == ' ') {
                            continue;
                        }
                        else {
                            switch (counter) {
                            case 1:
                                v1 = "";
                                for(int index2 = index; index2 < line.length(); index2++) {
                                    if(line[index2] == ' ') {
                                        index = index2;
                                        break;
                                    }
                                    else {
                                        v1 = v1 + line[index2];
                                    }
                                }
                                if(v1 == "" || v1 == " ") {
                                  v1 = "0";
                                }
                                counter++;
                                break;
                            case 2:
                                v2 = "";
                                for(int index2 = index; index2 < line.length(); index2++) {
                                    if(line[index2] == ' ') {
                                        index = index2;
                                        break;
                                    }
                                    else {
                                        v2 = v2 + line[index2];
                                    }
                                }if(v2 == "" || v2 == " ") {
                                  v2 = "0";
                                }
                                counter++;
                                break;
                            case 3:
                                v3 = "";
                                for(int index2 = index; index2 < line.length(); index2++) {
                                    if(line[index2] == ' ') {
                                        index = index2;
                                        break;
                                    }
                                    else {
                                        v3 = v3 + line[index2];
                                    }
                                }
                                if(v3 == "" || v3 == " ") {
                                  v3 = "0";
                                }
                                counter++;
                                break;
                            case 4:
                                v4 = "";
                                for(int index2 = index; index2 < line.length(); index2++) {
                                    if(line[index2] == ' ') {
                                        index = index2;
                                        break;
                                    }
                                    else {
                                        v4 = v4 + line[index2];
                                    }
                                }
                                if(v4 == "" || v4 == " ") {
                                  v4 = "0";
                                }
                                counter++;
                                break;
                            case 5:
                                v5 = "";
                                for(int index2 = index; index2 < line.length(); index2++) {
                                    if(line[index2] == ' ') {
                                        index = index2;
                                        break;
                                    }
                                    else {
                                        v5 = v5 + line[index2];
                                    }
                                }
                                if(v5 == "" || v5 == " ") {
                                  v5 = "0";
                                }
                                counter++;
                                break;
                            case 6:
                                v5 = "";
                                for(int index2 = index; index2 < line.length(); index2++) {
                                    if(line[index2] == ' ') {
                                        index = index2;
                                        break;
                                    }
                                    else {
                                        v5 = v5 + line[index2];
                                    }
                                }
                                if(v6 == "" || v6 == " ") {
                                  v6 = "0";
                                }
                                counter++;
                                break;
                            case 7:
                                v7 = "";
                                for(int index2 = index; index2 < line.length(); index2++) {
                                    if(line[index2] == ' ') {
                                        index = index2;
                                        break;
                                    }
                                    else {
                                        v7 = v7 + line[index2];
                                    }
                                }
                                if(v7 == "" || v7 == " ") {
                                  v7 = "0";
                                }
                                counter++;
                                break;
                            case 8:
                                v8 = "";
                                for(int index2 = index; index2 < line.length(); index2++) {
                                    if(line[index2] == ' ') {
                                        index = index2;
                                        break;
                                    }
                                    else {
                                        v8 = v8 + line[index2];
                                    }
                                }
                                if(v8 == "" || v8 == " ") {
                                  v8 = "0";
                                }
                                counter++;
                                break;
                            case 9:
                                v9 = "";
                                for(int index2 = index; index2 < line.length(); index2++) {
                                    if(line[index2] == ' ') {
                                        index = index2;
                                        break;
                                    }
                                    else {
                                        v9 = v9 + line[index2];
                                    }
                                }
                                if(v9 == "" || v9 == " ") {
                                  v9 = "0";
                                }
                                counter++;
                                break;
                            case 10:
                                v10 = "";
                                for(int index2 = index; index2 < line.length(); index2++) {
                                    if(line[index2] == ' ') {
                                        index = index2;
                                        break;
                                    }
                                    else {
                                        v10 = v10 + line[index2];
                                    }
                                }
                                if(v10 == "" || v10 == " ") {
                                  v10 = "0";
                                }
                                counter++;
                                break;
                            default:
                                break;
                            }
                        }
                    }
                }
                else {
                    continue;
                }
            }
            if(number == "" || number == " ") {
                continue;
            }
            long vs1 = std::stol(v1);
            long vs2 = std::stol(v2);
            long vs3 = std::stol(v3);
            long vs4 = std::stol(v4);
            long vs5 = std::stol(v5);
            long vs6 = std::stol(v6);
            long vs7 = std::stol(v7);
            long vs8 = std::stol(v8);

//            long totalCpuSinceBoot = vs1 + vs2 + vs3 + vs4 + vs5 + vs6 + vs7 + vs8;
//            long totalCpuIdle = vs4 + vs5;
//            long totalCpuTimeUsage = totalCpuSinceBoot - totalCpuIdle;
//            long percentage = totalCpuSinceBoot / totalCpuTimeUsage;

            long usage = vs1 + vs2 + vs3;
            long cp = vs1 + vs2 + vs3 + vs4 + vs5;
            if(ON == 0) {
                oldCoresVector.push_back(new CpuCore(number, usage, cp, 0));
            }
            else {
                long percentage;
                CpuCore* c2 = oldCoresVector[coresVector.size()];
                percentage = ((usage - c2->getUsage())*100)/(cp - c2->getCpu());
                coresVector.push_back(new CpuCore(number, usage, cp, percentage));
            }

            counter = 1;
            number = "";

          }
          file.close();
          dataFile = finalString;
          cpuNumber = coresVector.size();
}
