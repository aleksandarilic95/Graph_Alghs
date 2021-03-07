#include "Graph.h"

#include <iostream>

#include "GraphAlgorithm.h"
#include "Node.h"

using namespace std;

class DijkstrasAlgorithm : public GraphAlgorithm<int, int> {
public:
	void start() override;
	void currentNode(pair<size_t, Node<int>*> node) override { currentNode_v = node.first; };
	int decideNext(vector<pair<size_t, int>> remainingNodes, vector<bool> visitedNodes) override;
	void end() override;

	DijkstrasAlgorithm(size_t start, size_t size) : startNode(start), nodeCount(size) {};

private:
	size_t startNode;
	size_t currentNode_v;
	size_t nodeCount;
	vector<int> distanceFromStartNode;
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


	DijkstrasAlgorithm da(0, g.getNodeSize());
	g.DFS(0, da);


	return 0;
}

void DijkstrasAlgorithm::start()
{
	for (size_t i = 0; i < nodeCount; i++)
		distanceFromStartNode.push_back(INT_MAX);
	distanceFromStartNode[startNode] = 0;
	for (size_t i = 0; i < nodeCount; i++)
		lastNode.push_back(-1);
}

int DijkstrasAlgorithm::decideNext(vector<pair<size_t, int>> remainingNodes, vector<bool> visitedNodes)
{
	if (!remainingNodes.size())
		return -1;
	for (auto&& i : remainingNodes)
		if (distanceFromStartNode[currentNode_v] + i.second < distanceFromStartNode[i.first]) {
			distanceFromStartNode[i.first] = distanceFromStartNode[currentNode_v] + i.second;
			lastNode[i.first] = currentNode_v;
		}
	for (int i = 0; i < visitedNodes.size(); i++) {
		if (!visitedNodes[i])
			return i;
	}
	return -1;
}

void DijkstrasAlgorithm::end()
{
	cout << "End!" << endl;
}
