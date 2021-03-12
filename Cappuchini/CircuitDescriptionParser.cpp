#include "CircuitDescriptionParser.h"

//template <typename Out>
//void split(const std::string &s, char delim, Out result) {
//	std::istringstream iss(s);
//	std::string item;
//	while (std::getline(iss, item, delim)) {
//		*result++ = item;
//	}
//}
//
//std::vector<std::string> split(const std::string &s, char delim) {
//	std::vector<std::string> elems;
//	split(s, delim, std::back_inserter(elems));
//	return elems;
//}

void CircuitDescriptionParser::parse(const std::string& infile) {
	std::cout << infile << std::endl;

	std::ifstream fileStream(infile);

	std::string line;
	while (std::getline(fileStream, line))
	{
		std::cout << line << std::endl;

		// VoltageSource: V<int> <node.+> <node.-> <value>

		// Current Source: I<int> <node.+> < node.-> <value> [group]

		// Resistor: R<int> <node.+> <node.-> <value> [group]

		// Capacitor: C<int> <node.+> <node.-> <value> [group]

		// Inductor: L<int> <node.+> <node.-> <value>

		// Diode: D<int> <node.+> <node.-> [<value>]

		// BJT:
		// NPN: QN<int> <node.C> <node.B> <node.E> [<value>]
		// PNP: QP<int> <node.C> <node.B> <node.E> [<value>]

		// MOSFET:
		// n-channel: MN<int> <node.D> <node.G> <node.S> [<value>]
		// p-channel: MP<int> <node.D> <node.G> <node.S> [<value>]

		// convert line to uppercase
		std::transform(line.begin(), line.end(), line.begin(), ::toupper);

		// insert the string into a stream
		std::stringstream ss(line);       

		// create vector to hold our words
		std::vector<std::string> tokens; 

		std::string buf;
		while (ss >> buf) {
			tokens.push_back(buf);
		}

		// skip empty lines and comments
		if (tokens.size() == 0 || tokens.at(0).compare("%") == 0) {
			continue;
		}		

		if (((tokens.at(0).rfind("V", 0) == 0) || (tokens.at(0).rfind("L", 0) == 0)) && (tokens.size() >= 4)) {

			std::cout << "Voltage Source / Inductor found" << std::endl;

			std::string id = tokens.at(0);
			std::string nodeA = tokens.at(1);
			std::string nodeB = tokens.at(2);
			std::string valueAsString = tokens.at(3);

			std::string::size_type sz;
			double value = std::stod(valueAsString, &sz);

			std::cout << "voltage / Inductance " << value << std::endl;

			CircuitElement circuitElement;
			circuitElement.id = id;
			circuitElement.type = (tokens.at(0).rfind("V", 0) == 0) ? "V" : "L";
			circuitElement.nodeA = nodeA;
			circuitElement.nodeB = nodeB;
			circuitElement.nodeC = "N/A";
			circuitElement.value = value;
			circuitElement.group = "N/A";
			circuitElement.scaleFactor = 1;

			// the local variable is copied and the copy is then owned by the vector
			circuitElements.push_back(circuitElement);

		}
		else if (((tokens.at(0).rfind("I", 0) == 0) || (tokens.at(0).rfind("R", 0) == 0) || (tokens.at(0).rfind("C", 0) == 0)) && (tokens.size() >= 4)) {

			std::cout << "CurrentSource / Resistor / Capacitor found " << std::endl;

			std::string id = tokens.at(0);
			std::string nodeA = tokens.at(1);
			std::string nodeB = tokens.at(2);
			std::string valueAsString = tokens.at(3);

			// alias of size_t
			std::string::size_type sz;

			double value = std::stod(valueAsString, &sz);

			std::cout << "Current / Resistance/ Capacitance " << value << std::endl;

			CircuitElement circuitElement;
			circuitElement.id = id;
			circuitElement.type = (tokens.at(0).rfind("I", 0) == 0) ? "I" : tokens.at(0).rfind("R", 0) == 0 ? "R" : "C";
			circuitElement.nodeA = nodeA;
			circuitElement.nodeB = nodeB;
			circuitElement.nodeC = "N/A";
			circuitElement.value = value;
			circuitElement.scaleFactor = 1;
			circuitElement.group = "N/A";

			if (tokens.size() >= 5) {
				circuitElement.group = tokens.at(4);
			}

			// the local variable is copied and the copy is then owned by the vector
			circuitElements.push_back(circuitElement);

		} else if ((tokens.at(0).rfind("D", 0) == 0) && (tokens.size() >= 3)) {

			std::cout << "Diode found" << std::endl;

			std::string id = tokens.at(0);
			std::string nodeA = tokens.at(1);
			std::string nodeB = tokens.at(2);
			
			CircuitElement circuitElement;
			circuitElement.id = id;
			circuitElement.type = "D";
			circuitElement.nodeA = nodeA;
			circuitElement.nodeB = nodeB;
			circuitElement.nodeC = "N/A";
			circuitElement.group = "N/A";
			circuitElement.value = 0;
			circuitElement.scaleFactor = 1;

			if (tokens.size() >= 4) {
				std::string valueAsString = tokens.at(3);
				std::string::size_type sz;
				double value = std::stod(valueAsString, &sz);
				std::cout << "ScaleFactor " << value << std::endl;
				circuitElement.scaleFactor = value;
			}

			// the local variable is copied and the copy is then owned by the vector
			circuitElements.push_back(circuitElement);

		}
		else if (((tokens.at(0).rfind("Q", 0) == 0) || (tokens.at(0).rfind("M", 0) == 0)) && (tokens.size() >= 4)) {

			std::string id = tokens.at(0);
			std::string nodeA = tokens.at(1);
			std::string nodeB = tokens.at(2);
			std::string nodeC = tokens.at(3);

			CircuitElement circuitElement;
			circuitElement.id = id;						

			// type
			if ((tokens.at(0).rfind("QN", 0) == 0)) {
				circuitElement.type = "QN";
			} else if ((tokens.at(0).rfind("QP", 0) == 0)) {
				circuitElement.type = "QP";
			} else if ((tokens.at(0).rfind("MN", 0) == 0)) {
				circuitElement.type = "MN";
			} else if ((tokens.at(0).rfind("MP", 0) == 0)) {
				circuitElement.type = "MP";
			}

			// collector / drain
			circuitElement.nodeA = nodeA;
			// base / gate
			circuitElement.nodeB = nodeB;
			// emitter / source
			circuitElement.nodeC = nodeC;
			circuitElement.scaleFactor = 1;
			circuitElement.value = 0;
			circuitElement.group = "N/A";

			if (tokens.size() >= 5) {
				std::string valueAsString = tokens.at(4);
				std::string::size_type sz;
				double value = std::stod(valueAsString, &sz);
				std::cout << "ScaleFactor " << value << std::endl;
				circuitElement.scaleFactor= value;
			}

			// the local variable is copied and the copy is then owned by the vector
			circuitElements.push_back(circuitElement);
		} 
		else {

			std::cout << "Uknown line format: " + line << std::endl;
			//throw "Uknown line format: " + line;

		}
	}
}
