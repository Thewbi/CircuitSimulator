#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>

struct CircuitElement  {
	std::string id;
	std::string type;
	std::string nodeA;
	std::string nodeB;
	std::string nodeC;
	std::string group;
	double value;
	double scaleFactor;
};



class CircuitDescriptionParser
{
public:
	std::vector<CircuitElement> circuitElements;
	void parse(const std::string& infile);
};

