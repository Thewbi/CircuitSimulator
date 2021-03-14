#pragma once

#include <memory>
#include <string>

#include "CircuitElement.h"
#include "Node.fwd.h"
#include "Edge.fwd.h"

class Edge
{
public:
	std::string name;
	std::shared_ptr<Node> source;
	std::shared_ptr<Node> target;
	std::shared_ptr<Edge> reverseEdge;
	CircuitElement circuitElement;
	bool processed;
};

