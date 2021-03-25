#include "src/Graph/Graph.h"
#include "src/Algorithms/AlgorithmLib/GraphAlgorithms.h"

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <climits>

using namespace std;


class DijsktrasAlgorithm : public GBaseAlgorithm<int, int> {
public:
	void start();
	void current_node_do();
	void decide_next(vector<Graph<int, int>::Edge>&) {};
	void end();
private:
	vector<int> distance_from_start;
	vector<int> nodes;
};

void DijsktrasAlgorithm::start()
{
	distance_from_start.assign(graph_size(), INT_MAX);
	distance_from_start[start_node()] = 0;
	nodes.assign(graph_size(), -1);
}

void DijsktrasAlgorithm::current_node_do()
{
	nodes[current_node_idx] = *current_node_value_ptr;
	for (auto&& edge : get_neighbors(current_node_idx))
		if (distance_from_start[edge.m_edge_next_] > distance_from_start[current_node_idx] + *edge.m_edge_value_ptr_)
			distance_from_start[edge.m_edge_next_] = distance_from_start[current_node_idx] + *edge.m_edge_value_ptr_;
}

void DijsktrasAlgorithm::end()
{
	for (size_t i = 0; i < graph_size(); i++)
		cout << nodes.at(i) << ": " << distance_from_start.at(i) << endl;

	cout << "Algorithm time: " << (double)algorithm_time_us() / 1e6 << " us" << endl;
}

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
	// Graph<int, int> g;
	// g.reserve_nodes(174147);
	// for (auto i = 0; i < 174147; i++)
	// 	g.add_node(i);
	// load_graph(g);
	// DijsktrasAlgorithm da;
	// g.DFS(0, da);
	// int next; 
	// while((next = da.get_next()) != -1)
	// 	g.DFS(next, da);
	// return 0;

	Graph<int, int> g({ 0,1,2,3,4,5 });
	g.add_edge(0, 1, 1).add_edge(0, 2, 7).add_edge(0, 3, 6).add_edge(1, 3, 4).add_edge(1, 4, 1).add_edge(2, 5, 2).add_edge(3, 2, 3).add_edge(3, 5, 2).add_edge(4, 3, 2).add_edge(4, 5, 1);
	DijsktrasAlgorithm da;
	g.DFS(0, da);

	return 0;
}
