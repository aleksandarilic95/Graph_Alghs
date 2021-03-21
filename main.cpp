#include "src/Graph/Graph.h"
#include "src/Algorithms/AlgorithmLib/GraphAlgorithms.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class PrintAlgorithm : public GBaseAlgorithm<int, int> {
	virtual void start() { cout << "Algorithm Start" << endl; };
	virtual void current_node_do() { cout << "Current node :" << current_node_idx << endl; };
	virtual void decide_next([[maybe_unused]] vector<pair<size_t, int>>& vec) { return; };
	virtual void end() { cout << "Algorithm End" << endl; };
};

void load_graph(Graph<int, int>& g) {
	ifstream is("C1000-9.txt");
	while (!is.eof()) {
		string current_line;
		getline(is, current_line);
		size_t del = current_line.find(" ");
		string one = current_line.substr(0, del);
		string two = current_line.substr(del + 1, -1);
		g.add_edge(stoi(one) - 1, stoi(two) - 1, 0);
	}


}




int main() {
	Graph<int, int> g;
	for (auto i = 0; i < 1000; i++)
		g.add_node(i);
	load_graph(g);
	PrintAlgorithm pa;
	g.DFS(999, pa);
	return 0;
}