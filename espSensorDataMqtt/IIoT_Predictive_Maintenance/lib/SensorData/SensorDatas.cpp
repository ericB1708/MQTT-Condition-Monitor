#include "SensorDatas.h"

SensorDatas::SensorDatas()
{
	dict["temperature"] = {};
	dict["humidity_in_percent"] = {};
	dict["light_in_lux"] = {};

	vectorLenght = 0;
	index = 0;
}

void SensorDatas::addItemToDict(int value, std::string name)
{
	dict[name].push_back(value);
}

std::map<std::string, int> SensorDatas::getOneSensorData()
{
	if (index == vectorLenght)
	{
		index == 0;
	}

	std::map<std::string, int> returnData;

	vectorLenght = dict["temperature"].size();
	if (vectorLenght > 0 && index <= vectorLenght - 1)
	{
		returnData["temperature"] = dict["temperature"][index];
		returnData["humidity_in_percent"] = dict["humidity_in_percent"][index];
		returnData["light_in_lux"] = dict["light_in_lux"][index];
		++index;
	}
	return returnData;
}
