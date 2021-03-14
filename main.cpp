#include "Graph.h"
#include "GraphAlgorithms.h"

#include <iostream>



class DijsktrasAlgorithm : public GBaseAlgorithm<std::string, int> {
public:
	void start();
	void current_node_do();
	void decide_next(vector<pair<size_t, int>>&);
	void end();
private:
	vector<int> distance_from_start;
	vector<std::string> nodes;
};


int main() {
	Graph<string, int> g({ "A", "B", "C", "D", "E", "F" });

	g.add_edge(0, 1, 1).add_edge(0, 2, 7).add_edge(0, 3, 6).add_edge(1, 3, 4).add_edge(1, 4, 1).add_edge(2, 5, 2).add_edge(3, 2, 3).add_edge(3, 5, 2).add_edge(4, 3, 2).add_edge(4, 5, 1);

	DijsktrasAlgorithm da;

	cout << galgs::is_cyclic(g) << endl;

	return 0;
}

void DijsktrasAlgorithm::start()
{
	distance_from_start.assign(graph_size(), INT_MAX);
	distance_from_start[start_node()] = 0;
	nodes.assign(graph_size(), "");
}

void DijsktrasAlgorithm::current_node_do()
{
	nodes[current_node.first] = current_node.second.getValue();
	for (auto&& i : current_neighbors)
		if (distance_from_start[i.first] > distance_from_start[current_node.first] + i.second)
			distance_from_start[i.first] = distance_from_start[current_node.first] + i.second;
}

void DijsktrasAlgorithm::decide_next(vector<pair<size_t, int>>& vec)
{
	return;
}

void DijsktrasAlgorithm::end()
{
	for (size_t i = 0; i < graph_size(); i++)
		cout << nodes.at(i) << ": " << distance_from_start.at(i) << endl;

	cout << "Algorithm time: " << algorithm_time_us() << " us" << endl;
}
