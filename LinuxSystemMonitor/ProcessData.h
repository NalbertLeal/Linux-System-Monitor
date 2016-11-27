#ifndef PROCESSDATA_H
#define PROCESSDATA_H


#include <string>
#include <vector>
#include <fstream>

#include "process.h"

class ProcessData {
public:
    ProcessData();
    ~ProcessData();

    Process* getProcessByIndex(int);
    int getNumberOfProcess(void);
private:
    std::string ProcessFileData;
    std::vector<Process*> processDataVector;

    void getProcessFileData(void);
    void putOnVector(Process*&);
};

#endif // PROCESSDATA_H
