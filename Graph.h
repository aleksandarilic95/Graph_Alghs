#pragma once

#include "Node.h"
#include "GraphAlgorithm.h"

#include <vector>
#include <stack>
#include <iostream>

using namespace std;
/**/
template <typename T, typename P>
class Graph
{
public:
	Graph() {}
	/*TODO: Implement rule of 5*/
	Graph(const Graph& g) = delete;
	Graph& operator= (const Graph& rhs) = delete;

	Graph(Graph&& g) = delete;
	Graph& operator= (Graph&& rhs) = delete;

	~Graph() {}
	/*****************************/

	void addNode(T node) noexcept;
	void addEdge(size_t first, size_t second, P connection);

	int getNode(T node) const noexcept;

	void DFS(size_t start, GraphAlgorithm<T,P>& algorithm);

	size_t getNodeSize() const noexcept { return nodes_.size(); }
private:
	vector<pair<Node<T>*, size_t>> nodes_; //Each pair holds value of the Node and it's number in the graph
	vector<vector<pair<size_t,P>>> adjMatrix_; //Adjacency matrix of pairs holding number of the node that it connects to and connection P
};

template<typename T, typename P>
inline void Graph<T, P>::addNode(T node) noexcept
{
	nodes_.push_back(make_pair(new Node<T>(node), getNodeSize()));
	adjMatrix_.push_back({});
}

template<typename T, typename P>
inline void Graph<T, P>::addEdge(size_t first, size_t second, P connection)
{
	if (first > getNodeSize() - 1 or second > getNodeSize() - 1)
		//TODO: throw exception
		;
	adjMatrix_[first].push_back(make_pair(second, connection));
}

template<typename T, typename P>
inline int Graph<T, P>::getNode(T node) const noexcept
{
	for (auto nodeIter : nodes_)
		if (*nodeIter.first == node)
			return nodeIter.second;
	return -1;
}

template<typename T, typename P>
inline void Graph<T, P>::DFS(size_t start, GraphAlgorithm<T, P>& algorithm)
{
	algorithm.start();
	vector<bool> visitedNodes(getNodeSize(), false);
	stack<size_t> nodeStack({start});
	while (!nodeStack.empty()) {
		size_t currentNode = nodeStack.top();
		nodeStack.pop();



		if (!visitedNodes[currentNode]) {
			//TODO
			algorithm.currentNode(make_pair(currentNode,(nodes_[currentNode]).first));
			visitedNodes[currentNode] = true;
		}

		
		
		size_t nextNode = algorithm.decideNext(adjMatrix_[currentNode], visitedNodes);
		if (nextNode != -1)
			nodeStack.push(nextNode);
		
	}
	algorithm.end();
}
