#pragma once

#include "Node.h"
#include "GBaseAlgorithm.h"

#include <vector>
#include <stack>
#include <queue>
#include <iostream>

using namespace std;
/**/
template <typename T, typename P>
class Graph
{
public:
	Graph() {}
	explicit Graph(initializer_list<T> nodes);
	/*TODO: Implement rule of 5*/
	Graph(const Graph& g) = delete;
	Graph& operator= (const Graph& rhs) = delete;

	Graph(Graph&& g) = delete;
	Graph& operator= (Graph&& rhs) = delete;

	~Graph() {}
	/*****************************/

	Graph<T, P>& add_node(T node) noexcept;
	Graph<T, P>& add_node(initializer_list<T> nodes) noexcept;

	Graph<T, P>& add_edge(size_t first, size_t second, P connection);

	int get_node(T node) const noexcept;
	T get_node(size_t node_idx) const;


	void DFS(size_t start, GBaseAlgorithm<T, P>& algorithm);

	void BFS(size_t start, GBaseAlgorithm<T, P>& algorithm);

	size_t size() const noexcept { return m_nodes_.size(); }
private:
	vector<pair<Node<T>*, size_t>> m_nodes_; 
	vector<vector<pair<size_t,P>>> m_adj_matrix_; 
};

template<typename T, typename P>
inline Graph<T, P>::Graph(initializer_list<T> nodes)
{
	for (const T& node : nodes) {
		m_nodes_.push_back(make_pair(new Node<T>(node), size()));
		m_adj_matrix_.push_back({});
	}
}

template<typename T, typename P>
inline Graph<T, P>& Graph<T, P>::add_node(T node) noexcept
{
	
	return *this;
}

template<typename T, typename P>
inline Graph<T, P>& Graph<T, P>::add_node(initializer_list<T> nodes) noexcept
{
	for (const T& node : nodes) {
		m_nodes_.push_back(make_pair(new Node<T>(node), size()));
		m_adj_matrix_.push_back({});
	}
	return *this;
}

template<typename T, typename P>
inline Graph<T,P>& Graph<T, P>::add_edge(size_t first, size_t second, P connection)
{
	m_adj_matrix_[first].push_back(make_pair(second, connection));
	return *this;
}

template<typename T, typename P>
inline int Graph<T, P>::get_node(T node) const noexcept
{
	for (auto nodeIter : m_nodes_)
		if (*nodeIter.first == node)
			return nodeIter.second;
	return -1;
}

template<typename T, typename P>
inline void Graph<T, P>::DFS(size_t start, GBaseAlgorithm<T, P>& algorithm)
{
	if (!size())
		; //TODO: Throw: Can't call DFS on empty graph
	algorithm.util_start(size(), start, m_adj_matrix_);
	stack<size_t> node_stack({start});
	while (!node_stack.empty()) {
		//Pop starting node from the stack
		size_t current_node = node_stack.top();
		node_stack.pop();

		//If node is not visited, visit the node
		algorithm.util_current_node_do(make_pair(current_node, *(m_nodes_[current_node]).first));
		if (!algorithm.is_visited(current_node)) {
			algorithm.current_node_do();
		}
		
		vector<pair<size_t, P>> next_nodes = algorithm.util_decide_next();
		if(next_nodes.size())
			for (auto i : next_nodes)
				node_stack.push(i.first);
	}
	algorithm.util_end();
}

template<typename T, typename P>
inline void Graph<T, P>::BFS(size_t start, GBaseAlgorithm<T, P>& algorithm)
{
	if (!size())
		; //TODO
	algorithm.util_start(size(), start, m_adj_matrix_);
	queue<size_t> node_queue({ start });
	while (!node_queue.empty()) {
		//Pop starting node from the queue
		size_t current_node = node_queue.front();
		node_queue.pop();

		//If node is not visited, visit the node
		if (!algorithm.is_visited(current_node)) {
			algorithm.until_current_node_do(make_pair(current_node, *(m_nodes_[current_node]).first));
		}

		vector<pair<size_t, P>> next_nodes = algorithm.util_decide_next();
		if (next_nodes.size())
			for (auto i : next_nodes)
				node_queue.push(i.first);
	}
	algorithm.util_end();
}
