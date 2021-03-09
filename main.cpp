#include "Graph.h"

#include <iostream>


using namespace std;

class DijsktrasAlgorithm : public DFSAlgorithmBase<int, int> {
public:
	void start();
	void currentNodeAction();
	pair<int, int> decideNext();
	void end();

private:
	vector<int> distanceFromStart;
	vector<int> lastNode;

};


int main() {
	Graph<int, int> g;

	g.addNode(1);
	g.addNode(1);
	g.addNode(1);
	g.addNode(1);
	g.addNode(1);
	g.addNode(1);
	g.addEdge(0, 1, 1);
	g.addEdge(0, 2, 7);
	g.addEdge(0, 3, 6);
	g.addEdge(1, 3, 4);
	g.addEdge(1, 4, 1);
	g.addEdge(2, 5, 2);
	g.addEdge(3, 2, 3);
	g.addEdge(3, 5, 2);
	g.addEdge(4, 3, 2);
	g.addEdge(4, 5, 1);

	DijsktrasAlgorithm da;

	g.DFS(0, da);


	return 0;
}

void DijsktrasAlgorithm::start()
{
	for (int i = 0; i < node_size; i++)
		distanceFromStart.push_back(INT_MAX);
	distanceFromStart[start_node] = 0;
	for (int i = 0; i < node_size; i++)
		lastNode.push_back(start_node);
}

void DijsktrasAlgorithm::currentNodeAction()
{
	for (auto&& i : currentNeighbors)
		if (distanceFromStart[i.first] > distanceFromStart[currentNode.first] + i.second) {
			distanceFromStart[i.first] = distanceFromStart[currentNode.first] + i.second;
			lastNode[i.first] = currentNode.first;
		}
}

pair<int, int> DijsktrasAlgorithm::decideNext()
{
	for (auto&& i : currentNeighbors)
		if (!isVisited(i.first))
			return i;

	return make_pair(-1, 0);
}

void DijsktrasAlgorithm::end()
{
	int j = 0;
	for (auto i : distanceFromStart)
		cout << j++ << ": " << i << endl;

	cout << "Algorithm time: " << (double)algorithm_time.count() / 1000000 << " ms" << endl;
	
}
