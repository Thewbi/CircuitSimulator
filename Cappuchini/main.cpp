#include <iostream>
#include <iomanip>
#include <map>

#include "CircuitDescriptionParser.h"
#include "Node.h"
#include "Edge.h"
#include "main.h"

int main(int argc, char *argv[]) { 

	std::cout << "test" << std::endl;

	// load a circuit description (cd) file
	CircuitDescriptionParser circuitDescriptionParser;
	circuitDescriptionParser.parse("data/circuit1.cd");
	//circuitDescriptionParser.parse("data/circuit3.cd");
	//circuitDescriptionParser.parse("data/voltage_divider.cd");

	// from node name to node
	std::map<std::string, std::shared_ptr<Node>> nodeMap;

	// build the index map for the group 2 itmes using a sort on the names, resistors first, voltages last
	std::map<std::string, int> columnIndexMap;

	int m = circuitDescriptionParser.circuitElements.size();
	int n = m;
	std::vector< std::vector<double> > mna(m, std::vector<double>(n, 0.0));

	// right hand side (rhs) vector of the system of equations 
	std::vector<double> rhs(m, 0.0);

	// put group 2 elements at the bottom
	prepareColumnIndexMap(columnIndexMap, circuitDescriptionParser);

	// build node and edge objects from the circuit description and connect them for traversal
	constructGraphFromCircuitDesctiption(nodeMap, circuitDescriptionParser);	

	// execute the traversal of the circuit to create the MNA
	int nextFreeIndex = 0;
	//std::map<std::string, std::shared_ptr<Node>>::iterator startNodeIter = nodeMap.find("4");
	std::map<std::string, std::shared_ptr<Node>>::iterator startNodeIter = nodeMap.find("1");
	if (startNodeIter != nodeMap.end())
	{
		std::shared_ptr<Node> nodeStart = startNodeIter->second;

		nodeStart->traverse(nextFreeIndex, columnIndexMap, mna, rhs);
	}

	// DEBUG output
	outputMNAandRHS(mna, rhs);

	std::cout << "Done" << std::endl;
}

// one prerequisit of the algorithm is that group 2 elements have to go to the very bottom of the matrix
// This methode enforces this constraint.
void prepareColumnIndexMap(std::map<std::string, int>& columnIndexMap, CircuitDescriptionParser& circuitDescriptionParser) {

	int currentIndex = circuitDescriptionParser.circuitElements.size();

	// insert voltages into columnIndexMap
	for (CircuitElement circuitElement : circuitDescriptionParser.circuitElements) {

		// voltage source
		if (circuitElement.type.compare("V") == 0) {
			columnIndexMap[circuitElement.id] = currentIndex - 1;
			currentIndex--;
		}
	}

	// insert group 2 resistors into columnIndexMap
	for (CircuitElement circuitElement : circuitDescriptionParser.circuitElements) {

		// resistor in group 2
		if ((circuitElement.group.compare("G2") == 0) && (circuitElement.type.compare("R") == 0)) {
			columnIndexMap[circuitElement.id] = currentIndex - 1;
			currentIndex--;
		}
	}
}

// construct the graph from the parsed circuit description
// The graph is needed for a controlled traversal later
// The traversal yields the MNA matrix and the RHS vector.
void constructGraphFromCircuitDesctiption(std::map<std::string, std::shared_ptr<Node>>& nodeMap, CircuitDescriptionParser& circuitDescriptionParser) {

	for (CircuitElement circuitElement : circuitDescriptionParser.circuitElements) {

		// create/retrieve start node
		std::shared_ptr<Node> nodeStart;
		std::map<std::string, std::shared_ptr<Node>>::iterator startNodeIter = nodeMap.find(circuitElement.nodeA);
		if (startNodeIter != nodeMap.end())
		{
			nodeStart = startNodeIter->second;
		}
		else
		{
			nodeStart = std::make_shared<Node>();
			nodeStart->name = circuitElement.nodeA;
			nodeMap[circuitElement.nodeA] = nodeStart;
		}

		// create/retrieve start node
		std::shared_ptr<Node> nodeEnd;
		std::map<std::string, std::shared_ptr<Node>>::iterator endNodeIter = nodeMap.find(circuitElement.nodeB);
		if (endNodeIter != nodeMap.end())
		{
			nodeEnd = endNodeIter->second;
		}
		else
		{
			nodeEnd = std::make_shared<Node>();
			nodeEnd->name = circuitElement.nodeB;
			nodeMap[circuitElement.nodeB] = nodeEnd;
		}

		// edge from start node to end node
		std::shared_ptr<Edge> edgeStartEnd = std::make_shared<Edge>();
		edgeStartEnd->source = nodeStart;
		edgeStartEnd->target = nodeEnd;
		edgeStartEnd->name = circuitElement.id;
		edgeStartEnd->circuitElement = circuitElement;
		nodeStart->edges.push_back(edgeStartEnd);

		// edge from end node to start node
		std::shared_ptr<Edge> edgeEndStart = std::make_shared<Edge>();
		edgeEndStart->source = nodeEnd;
		edgeEndStart->target = nodeStart;
		edgeEndStart->name = circuitElement.id;
		edgeEndStart->circuitElement = circuitElement;
		nodeEnd->edges.push_back(edgeEndStart);

		edgeStartEnd->reverseEdge = edgeEndStart;
		edgeEndStart->reverseEdge = edgeStartEnd;
	}
}

void outputMNAandRHS(std::vector< std::vector<double> >& mna, std::vector<double>& rhs) {

	std::cout << std::fixed;
	std::cout << std::setprecision(3);

	for (size_t i = 0; i < mna.size(); i++) {

		bool first = true;

		for (size_t j = 0; j < mna.size(); j++) {

			if (!first) {
				std::cout << '\t';
			}
			std::cout << mna[i][j];

			first = false;
		}

		std::cout << '\t' << rhs[i] << std::endl;
	}
}