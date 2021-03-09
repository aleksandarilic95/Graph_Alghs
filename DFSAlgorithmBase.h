#pragma once

#include "Node.h"
#include <vector>
#include <chrono>

using namespace std;



template <typename T, typename P>
class DFSAlgorithmBase
{
public:


	virtual void start() = 0;
	virtual void currentNodeAction() = 0;
	virtual pair<int, P> decideNext();
	virtual void end() = 0;

	void startAdmin(size_t nodeSize, size_t startNode, vector<vector<pair<size_t, P>>> adjMatrix);
	void endAdmin();
	vector<int> decideNextBase();
	void currentNodeAdmin(pair<size_t, Node<T>*>);
	bool isVisited(size_t idx) { return visitedNodes[idx]; }
protected:
	size_t start_node;
	size_t node_size;
	pair<size_t, Node<T>*> currentNode;
	P lastEdge;
	vector<pair<size_t, P>> currentNeighbors;
	chrono::nanoseconds algorithm_time;
private:
	vector<vector<pair<size_t, P>>> adjMatrix_;
	vector<bool> visitedNodes;
	chrono::time_point<chrono::high_resolution_clock> startTime;
	chrono::time_point<chrono::high_resolution_clock> endTime;

};

template<typename T, typename P>
inline pair<int, P> DFSAlgorithmBase<T, P>::decideNext()
{
	for (auto&& i : currentNeighbors)
		if (!isVisited(i.first))
			return i;
	return make_pair(-1, P(0));
}

template<typename T, typename P>
inline void DFSAlgorithmBase<T, P>::startAdmin(size_t nodeSize, size_t startNode, vector<vector<pair<size_t, P>>> adjMatrix)
{
	startTime = chrono::high_resolution_clock::now();
	node_size = nodeSize;
	start_node = startNode;
	for (size_t i = 0; i < nodeSize; i++)
		visitedNodes.push_back(false);
	adjMatrix_ = adjMatrix;

	start();
}

template<typename T, typename P>
inline void DFSAlgorithmBase<T, P>::endAdmin()
{

	endTime = chrono::high_resolution_clock::now();

	algorithm_time = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime);
	end();
}

template<typename T, typename P>
inline vector<int> DFSAlgorithmBase<T, P>::decideNextBase()
{

	pair<int, P> result = decideNext();
	lastEdge = result.second;
	vector<int> returnVec;
	for (auto&& i : currentNeighbors)
		if (!isVisited(i.first) && i.first != result.first)
			returnVec.push_back(i.first);
	returnVec.push_back(result.first);
	return returnVec;

}

template<typename T, typename P>
inline void DFSAlgorithmBase<T, P>::currentNodeAdmin(pair<size_t, Node<T>*> currentNode_p)
{
	currentNode = currentNode_p;
	visitedNodes[currentNode.first] = true;
	currentNeighbors = adjMatrix_[currentNode.first];
	currentNodeAction();
}


