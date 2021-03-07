#pragma once

#include "Node.h"
#include <vector>

using namespace std;

template <typename T, typename P>
class GraphAlgorithm
{
public:
	virtual void start() = 0;
	virtual void currentNode(pair<size_t,Node<T>*> node) = 0;
	virtual int decideNext(vector<pair<size_t, P>> remainingNodes, vector<bool> visitedNodes) = 0;
	virtual void end() = 0;
};

