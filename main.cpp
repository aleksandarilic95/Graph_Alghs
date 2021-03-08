#include "Graph.h"

#include <iostream>

#include "GraphAlgorithm.h"
#include "Node.h"

using namespace std;

class PrintAlgorithm : public GraphAlgorithm<int, int> {
	virtual void start() {};
	virtual void currentNodeAction();
	virtual void end() {
		cout << "end" << endl;
	};
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

	PrintAlgorithm pa;

	g.DFS(0, pa);


	return 0;
}

void PrintAlgorithm::currentNodeAction()
{
	cout << "Current Node: " << currentNode.first << " value: " << currentNode.second->getValue() << endl;
}
