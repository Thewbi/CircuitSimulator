#include <iostream>
#include <iomanip>
#include <map>


#include "CircuitDescriptionParser.h"
#include "Node.h"
#include "Edge.h"

int main(int argc, char *argv[]) { 

	std::cout << "test" << std::endl;

	CircuitDescriptionParser circuitDescriptionParser;
	//circuitDescriptionParser.parse("data/circuit1.cd");
	circuitDescriptionParser.parse("data/circuit3.cd");

	std::map<std::string, std::shared_ptr<Node>> nodeMap;

	// TODO: build the index map for the group 2 itmes using a sort on the names, resistors first, voltages last
	std::map<std::string, int> columnIndexMap;
	/*columnIndexMap["R8"] = 8;
	columnIndexMap["R3"] = 9;
	columnIndexMap["V3"] = 10;
	columnIndexMap["V2"] = 11;
	columnIndexMap["V1"] = 12;*/

	columnIndexMap["V1"] = 1;

//#define SIZE 13
#define SIZE 2

	double mna[SIZE][SIZE];
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			mna[i][j] = 0;
		}
	}

	double rhs[SIZE];
	for (int i = 0; i < SIZE; i++) {
		rhs[i] = 0;
	}

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

	int nextFreeIndex = 0;
	//std::map<std::string, std::shared_ptr<Node>>::iterator startNodeIter = nodeMap.find("4");
	std::map<std::string, std::shared_ptr<Node>>::iterator startNodeIter = nodeMap.find("1");
	if (startNodeIter != nodeMap.end())
	{
		std::shared_ptr<Node> nodeStart = startNodeIter->second;

		nodeStart->traverse(nextFreeIndex, columnIndexMap, mna, rhs);
	}

	std::cout << std::fixed;
	std::cout << std::setprecision(3);

	for (int i = 0; i < SIZE; i++) {

		bool first = true;

		for (int j = 0; j < SIZE; j++) {

			if (!first) {
				std::cout << '\t';
			}
			std::cout << mna[i][j];

			first = false;
		}

		std::cout << '\t' << rhs[i] << std::endl;
	}

	std::cout << "Ende Jelende" << std::endl;

}