#include "src/Graph/Graph.h"
#include "src/Algorithms/AlgorithmLib/GraphAlgorithms.h"

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <climits>

using namespace std;


class EmptyDFS : public GBaseAlgorithm<int,int> {
	void start() {}
	void end() {
		cout << (double)algorithm_time_us() / 1e6 << endl;
	}
	void current_node_do() {}
};

void load_graph(Graph<int, int>& g) {
	std::ifstream is("edges.txt");
	while (!is.eof()) {
		std::string current_line;
		std::getline(is, current_line);
		size_t del = current_line.find(" ");
		std::string one = current_line.substr(0, del);
		std::string two = current_line.substr(del + 1, -1);
		if (one == "144149" && two == "174147")
			break;
		g.add_edge(stoi(std::move(one)) - 1, stoi(std::move(two)) - 1, 1);
	}

}




int main() {
	Graph<int, int> g;
	g.reserve_nodes(174147);
	for (auto i = 0; i < 174147; i++)
		g.add_node(i);
	load_graph(g);
	EmptyDFS edfs;
	g.DFS(g.size() - 1,edfs);


	return 0;
}
