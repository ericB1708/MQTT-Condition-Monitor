#pragma once
#include <map>
#include <string>
#include <vector>

class SensorDatas
{

public:
    SensorDatas();
    void addItemToDict(int value, std::string name);
    std::map<std::string, int> getOneSensorData();

private:
    int index;
    int vectorLenght;
    std::map<std::string, std::vector<int>> dict;
};