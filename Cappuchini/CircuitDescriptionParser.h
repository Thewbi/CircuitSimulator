#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>

#include "CircuitElement.h"



class CircuitDescriptionParser
{
public:
	std::vector<CircuitElement> circuitElements;
	void parse(const std::string& infile);
};

