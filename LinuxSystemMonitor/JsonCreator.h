#ifndef JSONCREATOR_H
#define JSONCREATOR_H


#include <string>
#include <vector>
#include <fstream>
#include <map>

#include "process.h"
#include "ProcessData.h"

class JsonCreator {
public:
    JsonCreator();
    ~JsonCreator();

    void createJson(int);
private:
    ProcessData* pd;
    int valueOfMetric;
    std::map<int, std::vector<Process*>> processInfo;

    void organizeProcess();
    std::string jsonFather(std::vector<Process*>&);
    std::string jsonSon(Process*);

};

#endif // JSONCREATOR_H
