#pragma once

int main(int argc, char * argv[]);
void outputMNAandRHS(std::vector< std::vector<double> >& mna, std::vector<double>& rhs);
void prepareColumnIndexMap(std::map<std::string, int>& columnIndexMap, CircuitDescriptionParser& circuitDescriptionParser);
void constructGraphFromCircuitDesctiption(std::map<std::string, std::shared_ptr<Node>>& nodeMap, CircuitDescriptionParser& circuitDescriptionParser);
