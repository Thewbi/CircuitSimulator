#include "Node.h"
#include "Edge.h"

// Performs a pre-order traversal of the node graph to assemble the MNA matrix and the RHS vector, which
// are then used to solve the system for voltages and currents.
//
// The traversal starts at a node which has to be different from the reference node 0.
//
// For a node, first the lumped elements connected to that node via edges are converted to their stamps
// and values are inserted/added into the MNA according to the stamp.
// A lumped element/edge is then marked as processed to prevent it from being inserted/added twice.
// Then the node itself is marked as processed to prevent it from being inserted/added twice.
//
// After the connected lumped elements are inserted, the child nodes are recursed over to finalize the
// graph traversal. Once all reachable nodes have been processed and the recursion ascends from the start
// node, the process is finished and the MNA and RHS have been constructed.
//
// Lumped elements and nodes that have already been inserted/added are ignored when they are encountered for the second time.
// The reference node 0 is ignored if it is encountered always, in general.
//
// For elemnts that have different stamps depending on which group they are contained in, the relevant
// stamp is used (group 1 or group 2). A element is in group 2 if it's current is of interest in addition to the voltage over it.
// The current is of importance for voltage sources (V) and for lumped elements which are used to control current controlled sources.
// Such elements are somehow measured (not necessary via an physical trace/edge in the circuit/graph) and that measured current
// is then used to control a current controlled source. Whenever an element's current is has to be known, that element
// has to go into group 2.
//
// It is also possible to put a resistor into group 2 without it being used to control a source. This is just
// if you want to know the current or if you want to test your algorithm. Putting a resistor into group 2 when it 
// is not used to controll a current controlled source is optional!
//
// If a lumped element is connected to the reference node (node 0) with one of it's terminals, the stamp is reduced and the voltage
// parts of the terminal connected to the reference node is ignored, which yields a simpler compacted/reduced stamp.
// That stamp contributes less values to the MNA as opposed to a stamp where both terminals are connected to non-reference
// nodes.
// 
//void Node::traverse(int& nextFreeIndex, std::map<std::string, int>& columnIndexMap, double(&mna)[SIZE][SIZE], double(&rhs)[SIZE])
void Node::traverse(int& nextFreeIndex, std::map<std::string, int>& columnIndexMap, std::vector< std::vector<double> >& mna, std::vector<double>& rhs)
{
	// no operation for node 0
	if (name.compare("0") == 0) {
		std::cout << "NODE 0 NOP" << std::endl;
		processed = true;
		return;
	}

	// only process once
	if (processed) {
		return;
	}
	processed = true;

	std::cout << "Node " << name << " started!" << std::endl;

	// insert all lumped elements
	for (std::shared_ptr<Edge> edge : edges) {

		// only insert once
		if (edge->processed) {
			continue;
		}
		edge->processed = true;
		edge->reverseEdge->processed = true;

		// remember the alignment / order of the columns and rows and their indexes in the matrix
		// so that lumped elements can insert their stamps correctly
		if (edge->source->name.compare("0") != 0) {
			if (columnIndexMap.find(edge->source->name) == columnIndexMap.end()) {
				columnIndexMap[edge->source->name] = nextFreeIndex;
				nextFreeIndex++;
			}
		}

		if (edge->target->name.compare("0") != 0) {
			if (columnIndexMap.find(edge->target->name) == columnIndexMap.end()) {
				columnIndexMap[edge->target->name] = nextFreeIndex;
				nextFreeIndex++;
			}
		}

		// insert
		std::cout << "Inserting lumped element " << edge->name << std::endl;

		// resistor
		if (edge->circuitElement.type.compare("R") == 0) {

			// N/A == group 1
			if (edge->circuitElement.group.compare("N/A") == 0) {

				// stamp group 1 resistor

				//			v+			v-			RHS
				// -----------------------------------------
				// v+		1/R			-1/R
				// v-		-1/R		1/R

				if (edge->source->name.compare("0") == 0) {

					// TODO source terminal connected to reference
					throw 1;

				} else if (edge->target->name.compare("0") == 0) {

					// target terminal connected to reference
						
					int vplus = columnIndexMap[edge->source->name];

					std::cout << "v+ (" << edge->source->name << ") Index(" << vplus << ")" << std::endl;

					std::cout << "v+ v+ value: " << 1.0 / edge->circuitElement.value << std::endl;

					mna[vplus][vplus] += 1.0 / edge->circuitElement.value;

				}
				else {

					std::cout << "Not connected to 0 " << edge->name << std::endl;

					int vplus = columnIndexMap[edge->source->name];
					int vminus = columnIndexMap[edge->target->name];

					std::cout << "v+ (" << edge->source->name << ") Index(" << vplus << ")" << std::endl;
					std::cout << "v- (" << edge->target->name << ") Index(" << vminus << ")" << std::endl;

					std::cout << "v+ v+ value: " << 1.0 / edge->circuitElement.value << std::endl;
					mna[vplus][vplus] += 1.0 / edge->circuitElement.value;

					std::cout << "v+ v- value: " << -1.0 / edge->circuitElement.value << std::endl;
					mna[vplus][vminus] += -1.0 / edge->circuitElement.value;

					std::cout << "v- v+ value: " << -1.0 / edge->circuitElement.value << std::endl;
					mna[vminus][vplus] += -1.0 / edge->circuitElement.value;

					std::cout << "v- v- value: " << 1.0 / edge->circuitElement.value << std::endl;
					mna[vminus][vminus] += 1.0 / edge->circuitElement.value;
				}

			} else {

				// group 2 resistor

				// Stamp for group 2 resistor:

				//          v+       v-      i		  RHS
				// ---------------------------------------
				// v+                        +1
				// v-						 -1
				// i        +1      -1       -R

				if (edge->source->name.compare("0") == 0) {

					// TODO source terminal connected to reference
					throw 1;

				}
				else if (edge->target->name.compare("0") == 0) {

					// target terminal connected to reference
						
					int vplus = columnIndexMap[edge->source->name];
					int i = columnIndexMap[edge->circuitElement.id];

					std::cout << "v+ (" << edge->source->name << ") Index(" << vplus << ")" << std::endl;
					std::cout << "i (" << edge->circuitElement.id << ") Index(" << i << ")" << std::endl;

					std::cout << "v+ i value: " << 1 << std::endl;
					mna[vplus][i] += 1.0;

					std::cout << "i i value: " << -edge->circuitElement.value << std::endl;
					mna[i][i] += -edge->circuitElement.value;

					std::cout << "i v+ value: " << 1 << std::endl;
					mna[i][vplus] += 1.0;

				}
				else {

					int vplus = columnIndexMap[edge->source->name];
					int vminus = columnIndexMap[edge->target->name];
					int i = columnIndexMap[edge->circuitElement.id];

					std::cout << "v+ (" << edge->source->name << ") Index(" << vplus << ")" << std::endl;
					std::cout << "v- (" << edge->target->name << ") Index(" << vminus << ")" << std::endl;
					std::cout << "i (" << edge->circuitElement.id << ") Index(" << i << ")" << std::endl;

					std::cout << "v+ i value: " << 1 << std::endl;
					mna[vplus][i] += 1.0;

					std::cout << "v- i value: " << -1 << std::endl;
					mna[vminus][i] += -1.0;

					std::cout << "i v+ value: " << 1 << std::endl;
					mna[i][vplus] += 1.0;

					std::cout << "i v- value: " << -1 << std::endl;
					mna[i][vminus] += -1.0;

					std::cout << "i i value: " << -edge->circuitElement.value << std::endl;
					mna[i][i] += -edge->circuitElement.value;

				}

			}

		}
		else if (edge->circuitElement.type.compare("I") == 0) {

			// independant current source group 1

			//			v+		v-		RHS
			// ---------------------------------
			// v+						-I
			// v-						+I

			// N/A == group 1
			if (edge->circuitElement.group.compare("N/A") == 0) {

				if (edge->source->name.compare("0") == 0) {

					// TODO source terminal connected to reference
					throw 1;

				}
				else if (edge->target->name.compare("0") == 0) {

					// target terminal connected to reference
					int vplus = columnIndexMap[edge->source->name];
					//int vminus = columnIndexMap[edge->target->name];

					std::cout << "v+ (" << edge->source->name << ") Index(" << vplus << ")" << std::endl;
					// TODO:
					//std::cout << "v- (" << edge->target->name << ") Index(" << vminus << ")" << std::endl;

					std::cout << "v+ RHS value: " << -edge->circuitElement.value << std::endl;
					rhs[vplus] += -edge->circuitElement.value;
					
					//std::cout << "v- RHS value: " << edge->circuitElement.value << std::endl;

				}
				else {

					std::cout << "Not connected to 0 " << edge->name << std::endl;

					int vplus = columnIndexMap[edge->source->name];
					int vminus = columnIndexMap[edge->target->name];

					std::cout << "v+ (" << edge->source->name << ") Index(" << vplus << ")" << std::endl;
					std::cout << "v- (" << edge->target->name << ") Index(" << vminus << ")" << std::endl;

					std::cout << "v+ RHS value: " << -edge->circuitElement.value << std::endl;
					rhs[vplus] += -edge->circuitElement.value;
					
					std::cout << "v- RHS value: " << edge->circuitElement.value << std::endl;
					rhs[vminus] += edge->circuitElement.value;

				}

			} 
			else {

				// TODO: group 2
				throw 1;

			}

		}
		else if (edge->circuitElement.type.compare("V") == 0) {

			// voltage source

			//			v+		v-		i		RHS
			// ----------------------------------------
			// v+						+1
			// v-						-1
			// i		+1		-1				V

			if (edge->source->name.compare("0") == 0) {

				// TODO source terminal connected to reference
				throw 1;

			}
			else if (edge->target->name.compare("0") == 0) {

				// target terminal connected to reference
				
				int vplus = columnIndexMap[edge->source->name];
				//int vminus = columnIndexMap[edge->target->name];
				int i = columnIndexMap[edge->circuitElement.id];

				std::cout << "v+ (" << edge->source->name << ") Index(" << vplus << ")" << std::endl;
				//std::cout << "v- (" << edge->target->name << ") Index(" << vminus << ")" << std::endl;
				std::cout << "i (" << edge->circuitElement.id << ") Index(" << i << ")" << std::endl;

				std::cout << "v+ i value: " << 1 << std::endl;
				mna[vplus][i] += 1.0;
				//std::cout << "v- i value: " << -1 << std::endl;

				std::cout << "i v+ value: " << 1 << std::endl;
				mna[i][vplus] += 1.0;
				//std::cout << "i v- value: " << -1 << std::endl;

				std::cout << "i RHS: " << edge->circuitElement.value << std::endl;
				rhs[i] += edge->circuitElement.value;

			}
			else {

				int vplus = columnIndexMap[edge->source->name];
				int vminus = columnIndexMap[edge->target->name];
				int i = columnIndexMap[edge->circuitElement.id];

				std::cout << "v+ (" << edge->source->name << ") Index(" << vplus << ")" << std::endl;
				std::cout << "v- (" << edge->target->name << ") Index(" << vminus << ")" << std::endl;
				std::cout << "i (" << edge->circuitElement.id << ") Index(" << i << ")" << std::endl;

				std::cout << "v+ i value: " << 1 << std::endl;
				mna[vplus][i] += 1.0;
				std::cout << "v- i value: " << -1 << std::endl;
				mna[vminus][i] += -1.0;
				
				std::cout << "i v+ value: " << 1 << std::endl;
				mna[i][vplus] += 1.0;
				std::cout << "i v- value: " << -1 << std::endl;
				mna[i][vminus] += -1.0;

				std::cout << "i RHS: " << edge->circuitElement.value << std::endl;
				rhs[i] += edge->circuitElement.value;

			}

		} 
		else {

			// TODO not a resistor
			throw 1;

		}

	}

	// traverse children
	for (std::shared_ptr<Edge> edge : edges) {
		edge->target->traverse(nextFreeIndex, columnIndexMap, mna, rhs);
	}

	std::cout << "Node " << name << " done!" << std::endl;
}
