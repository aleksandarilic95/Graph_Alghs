#include "src/Graph/Graph.h"
#include "src/Algorithms/AlgorithmLib/GraphAlgorithms.h"

#include <iostream>

int main() {
	Graph<int, int> g({0,1,2,3,4,5});
	g.add_edge(0, 1, 0).add_edge(0, 2, 0).add_edge(0, 3, 0).add_edge(1, 3, 0).add_edge(3, 2, 0).add_edge(1, 4, 0).add_edge(4, 3, 0).add_edge(3, 5, 0).add_edge(2, 5, 0);
	std::cout << galgs::is_cyclic(g) << std::endl;
	return 0;
}