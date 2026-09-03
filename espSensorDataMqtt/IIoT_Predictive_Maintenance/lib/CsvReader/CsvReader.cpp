#include <Arduino.h>
#include <SPIFFS.h>
#include "CsvReader.h"
#include <sstream>
#include <vector>
#include <string>

SensorDatas readCsvData()
{
	File file = SPIFFS.open("/data.csv", FILE_READ);
	SensorDatas dataObj;

	if (!file)
	{
		Serial.println("Error file not found or open");
		return dataObj;
	}

	std::string line;
	std::vector<std::string> headersName;
	std::stringstream headerStream(line);
	std::string cell;

	if (file.available())
	{
		line = file.readStringUntil('\n').c_str();
		std::stringstream headerStream(line.c_str());
		std::string cell;

		for (int i = 0; i < 4; i++)
		{
			std::getline(headerStream, cell, ',');
			if (i < 3)
			{
				headersName.push_back(cell);
			}
		}
	}

	while (file.available())
	{
		line = file.readStringUntil('\n').c_str();
		std::stringstream lineStream(line.c_str());
		std::string cell;
		std::vector<std::string> row;

		while (std::getline(lineStream, cell, ','))
		{
			row.push_back(cell);
		}

		for (int i = 0; i < 4; i++)
		{
			if (i < 3 && i < row.size())
			{
				dataObj.addItemToDict(std::stoi(row[i]), headersName[i]);
			}
		}
	}

	file.close();
	Serial.println("CSV erfolgreich gelesen!");
	return dataObj;
}