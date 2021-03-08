#pragma once

#include "Node.h"
#include <vector>

using namespace std;



template <typename T, typename P>
class GraphAlgorithm
{
public:


	virtual void start() = 0;
	virtual void currentNodeAction() = 0;
	virtual pair<int, P> decideNext();
	virtual void end() = 0;

	void startAdmin(size_t nodeSize, vector<vector<pair<size_t, P>>> adjMatrix);
	vector<int> decideNextBase();
	void currentNodeAdmin(pair<size_t, Node<T>*>);
	bool isVisited(size_t idx) { return visitedNodes[idx]; }
protected:
	pair<size_t, Node<T>*> currentNode;
	P lastEdge;
	vector<pair<size_t, P>> currentNeighbors;
private:
	vector<vector<pair<size_t, P>>> adjMatrix_;
	vector<bool> visitedNodes;
};

template<typename T, typename P>
inline pair<int, P> GraphAlgorithm<T, P>::decideNext()
{
	for (auto&& i : currentNeighbors)
		if (!isVisited(i.first))
			return i;
	return make_pair(-1, P(0));
}

template<typename T, typename P>
inline void GraphAlgorithm<T, P>::startAdmin(size_t nodeSize, vector<vector<pair<size_t, P>>> adjMatrix)
{
	for (size_t i = 0; i < nodeSize; i++)
		visitedNodes.push_back(false);
	adjMatrix_ = adjMatrix;
	start();
}

template<typename T, typename P>
inline vector<int> GraphAlgorithm<T, P>::decideNextBase()
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
inline void GraphAlgorithm<T, P>::currentNodeAdmin(pair<size_t, Node<T>*> currentNode_p)
{
	currentNode = currentNode_p;
	visitedNodes[currentNode.first] = true;
	currentNeighbors = adjMatrix_[currentNode.first];
	currentNodeAction();
}


