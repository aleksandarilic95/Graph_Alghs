#pragma once

#include "../Algorithms/GBaseAlgorithm.h"

#include <vector>
#include <stack>
#include <queue>
#include <iostream>
#include <memory>

/**/
template <typename T, typename P>
class Graph
{

public:
	typedef struct Node {
		Node(size_t p_node_number, T p_node_value) : m_node_number_(p_node_number), m_node_value_ptr_(new T(p_node_value)) {}
		constexpr Node(const Node& rhs) {
			m_node_number_ = rhs.m_node_number_;
			m_node_value_ptr_ = new T(*rhs.m_node_value_ptr_);
		}
		Node& operator= (Node&& rhs) noexcept {
			if(this == &rhs)
				return *this;
			delete m_node_value_ptr_;
			m_node_number_ = std::exchange(rhs.m_node_number_, 0);
			m_node_value_ptr_ = std::exchange(rhs.m_node_value_ptr_, nullptr);
		}
		~Node() {
			delete m_node_value_ptr_;
		}

		size_t m_node_number_;
		T* m_node_value_ptr_;
	} Node;

	typedef struct Edge {
		Edge(size_t p_edge_next, T p_edge_value) : m_edge_next_(p_edge_next), m_edge_value_ptr_(new P(p_edge_value)) {}
		constexpr Edge(const Edge& rhs) {
			m_edge_next_ = rhs.m_edge_next_;
			m_edge_value_ptr_ = new T(*rhs.m_edge_value_ptr_);
		}
		Edge& operator= (Node&& rhs) noexcept {
			if(this == &rhs)
				return *this;
			delete m_edge_value_ptr_;
			m_edge_next_ = std::exchange(rhs.m_edge_next_, 0);
			m_edge_value_ptr_ = std::exchange(rhs.m_edge_value_ptr_, nullptr);
		}
		~Edge() {
			delete m_edge_value_ptr_;
		}
		
		size_t m_edge_next_;
		P* m_edge_value_ptr_;
	} Edge;




public:

	friend class GBaseAlgorithm<T,P>;

	Graph() {}
	explicit Graph(std::initializer_list<T> nodes);
	/*TODO: Implement rule of 5*/
	Graph(const Graph& g) = default;
	Graph& operator= (const Graph& rhs) = default;

	Graph(Graph&& g) noexcept = default;
	Graph& operator= (Graph&& rhs) noexcept = default;

	~Graph() = default;
	/*****************************/

	Graph<T, P>& add_node(T node) noexcept;
	Graph<T, P>& add_node(std::initializer_list<T> nodes) noexcept;

	Graph<T, P>& add_edge(size_t first, size_t second, P connection);

	int get_node(T node) const noexcept;
	T get_node_value(size_t node_idx) const;


	void DFS(size_t start, GBaseAlgorithm<T, P>& algorithm);
	void DFS_util(size_t start, GBaseAlgorithm<T, P>& algorithm);

	void BFS(size_t start, GBaseAlgorithm<T, P>& algorithm);

	size_t size() const noexcept { return m_nodes_.size(); }

	void reserve_nodes(size_t p_reserve_idx) {
		m_nodes_.reserve(p_reserve_idx);
		m_adj_matrix_.reserve(p_reserve_idx);
	}
private:
	std::vector<Node> m_nodes_;
	std::vector<std::vector<Edge>> m_adj_matrix_; 
	size_t m_graph_size_ = 0;
};

template<typename T, typename P>
inline Graph<T, P>::Graph(std::initializer_list<T> nodes)
{
	for (auto&& node : nodes) {
		m_nodes_.push_back(Node(m_graph_size_++, node));
		m_adj_matrix_.push_back({});
	}
}

template<typename T, typename P>
inline Graph<T, P>& Graph<T, P>::add_node(T node) noexcept
{
	m_nodes_.push_back(Node(m_graph_size_++, node));
	m_adj_matrix_.push_back({});
	return *this;
}

template<typename T, typename P>
inline Graph<T, P>& Graph<T, P>::add_node(std::initializer_list<T> nodes) noexcept
{
	for (auto&& node : nodes) {
		m_nodes_.push_back(Node(m_graph_size_++, node));
		m_adj_matrix_.push_back({});
	}
	return *this;
}

template<typename T, typename P>
inline Graph<T,P>& Graph<T, P>::add_edge(size_t first, size_t second, P connection)
{
	m_adj_matrix_[first].push_back(Edge(second, connection));
	return *this;
}

template<typename T, typename P>
inline int Graph<T, P>::get_node(T node) const noexcept
{
	for (auto&& nodeIter : m_nodes_)
		if (*nodeIter.first == node)
			return nodeIter.second;
	return -1;
}

template<typename T, typename P>
inline void Graph<T, P>::DFS(size_t start, GBaseAlgorithm<T, P>& algorithm)
{
	if (!size())
		return;
	algorithm.util_start(size(), start, this);
	int next;
	DFS_util(start, algorithm);
	while(!algorithm.finished() && (next = algorithm.get_next())!= -1)
		DFS_util(next, algorithm);
	algorithm.util_end();
}

template<typename T, typename P>
inline void Graph<T, P>::DFS_util(size_t p_start, GBaseAlgorithm<T, P>& p_algorithm)
{
	
		p_algorithm.util_current_node_do(m_nodes_[p_start].m_node_number_, m_nodes_[p_start].m_node_value_ptr_);
		if(p_algorithm.finished())
			return;
		for (auto&& l_neighbor_ : p_algorithm.util_decide_next()) {
			if (!p_algorithm.is_visited(l_neighbor_.m_edge_next_))
				DFS_util(l_neighbor_.m_edge_next_, p_algorithm);
		}
		p_algorithm.util_callback(m_nodes_[p_start].m_node_number_, m_nodes_[p_start].m_node_value_ptr_);
	
}



template<typename T, typename P>
inline void Graph<T, P>::BFS(size_t start, GBaseAlgorithm<T, P>& algorithm)
{
	//If there are no nodes in graph, return from the function
	if (!m_graph_size_)
		return;

	//Do start work with the algorithm
	algorithm.util_start(size(), start, m_adj_matrix_); 

	//Create node queue and push starting node onto the queue
	std::queue<size_t> node_queue({ start });

	while (!node_queue.empty()) {
		//If algorithm is finished, break from the loop
		if(algorithm.finished())
			break;

		//Pop starting node from the queue
		size_t current_node = node_queue.front();
		node_queue.pop();

		//If node is not visited, visit the node
		if (!algorithm.is_visited(current_node)) {
			algorithm.until_current_node_do(make_pair(current_node, *(m_nodes_[current_node]).first));
		}

		//Decide which nodes will be visited next
		std::vector<typename Graph<T,P>::Edge> next_nodes = algorithm.util_decide_next();
		if (next_nodes.size())
			for (auto&& node : next_nodes)
				node_queue.push(node.m_node_number_);
	}

	//Do end work with the algorithm
	algorithm.util_end();
}
