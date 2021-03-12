#include <iostream>
#include "CircuitDescriptionParser.h"

int main(int argc, char *argv[]) { 
	std::cout << "test" << std::endl;

	CircuitDescriptionParser circuitDescriptionParser;
	circuitDescriptionParser.parse("circuit1.cd");

	std::cout << "Ende Jelende" << std::endl;
}