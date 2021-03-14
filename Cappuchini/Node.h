#pragma once

#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <map>

#include "Edge.fwd.h"
#include "Node.fwd.h"

#define SIZE 2

class Node
{
public:
	int id;
	std::string name;
	std::vector<std::shared_ptr<Edge>> edges;
	bool processed;

	void traverse(int& nextFreeIndex, std::map<std::string, int>& columnIndexMap, double (&mna)[SIZE][SIZE], double(&rhs)[SIZE]);
};

