#include "JsonCreator.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>

#include "process.h"
#include "ProcessData.h"

JsonCreator::JsonCreator() {
    valueOfMetric = 0;
    pd = new ProcessData();

    organizeProcess();
    createJson(1);
}

JsonCreator::~JsonCreator() {
  /* EMPTY */
}

void JsonCreator::organizeProcess() {
    int numberOfProcess = pd->getNumberOfProcess();

    for(int index = 0; index < numberOfProcess; index++) {
        Process* auxP = pd->getProcessByIndex(index);
        processInfo[auxP->ppid].push_back(auxP);
    }
}

void JsonCreator::createJson(int auxValueOfMetric) {
    valueOfMetric = auxValueOfMetric;
    pd = new ProcessData();
    organizeProcess();

    std::ofstream fileJson("/home/nalbert/programacao/c++/projetosC++/TesteWeb/processos.json");

    int i = 0;
    fileJson << "{\"name\": \"processos\", \"children\": [";
    for (auto auxProcess : processInfo) {
        if(i++ == 0) {
            fileJson << jsonFather(auxProcess.second);
        }
        else {
            fileJson << "," << jsonFather(auxProcess.second);
        }
    }
    fileJson << "]}";

    fileJson.close();
}

std::string JsonCreator::jsonFather(std::vector<Process*> &vec) {
    // Verify if the vector isn't empty
    if (vec.empty()) {
        return "";
    }

    std::ostringstream ss;
    int i = 0;

    ss << "{\"name\":\"" << vec[0]->name << "\",\"children\":[";
    for (Process* auxProcess : vec) {
        if(i++ == 0) {
            ss << jsonSon(auxProcess);
        }
        else {
            ss << "," << jsonSon(auxProcess);
        }

    }
    ss << "]}";

    return ss.str();
}

std::string JsonCreator::jsonSon(Process *auxProcess) {
    int value;
    switch (valueOfMetric) {
      case 0:
          value = (auxProcess->cpu + 0.1)*1000;
      case 1:
          value = auxProcess->thread;
      case 2:
          value = (auxProcess->memmory + 0.1)*1000;
      default:
          value = (auxProcess->cpu + 0.1)*1000;
    }

    std::ostringstream ss;
    ss << "{\"name\":\"";
    ss << auxProcess->name;
    ss << "\",\"size\":";
    ss << value;
    ss << ",\"pid\":";
    ss << auxProcess->pid;
    ss << "}";

    return ss.str();
}

