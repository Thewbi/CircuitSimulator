#pragma once

#include <string>

struct CircuitElement {
	std::string id;
	std::string type;
	std::string nodeA;
	std::string nodeB;
	std::string nodeC;
	std::string group;
	double value;
	double scaleFactor;
};
