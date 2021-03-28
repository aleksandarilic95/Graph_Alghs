#pragma once

#include "../Algorithms/GBaseAlgorithm.h"

#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <stdexcept>

/** @brief Graph Structure class with templated parameters.\n  
    T - primitive or structure/class representing a node in the graph.\n 
	P - primitive or structure/class representing an edge in the graph.
    @author Aleksandar Ilic
    @date March 2021.
    */
template <typename T, typename P>
class Graph
{

public:
	
	/*Structure representing a node in the graph*/
	struct Node {
		Node(size_t p_node_number, T p_node_value_ptr) : node_number(p_node_number), node_value_ptr(new T(p_node_value_ptr)) {}
		constexpr Node(const Node& rhs) {
			node_number = rhs.node_number;
			node_value_ptr = new T(*rhs.node_value_ptr);
		}
		Node& operator= (Node&& rhs) noexcept {
			if(this == &rhs)
				return *this;
			delete node_value_ptr;
			node_number = std::exchange(rhs.node_number, 0);
			node_value_ptr = std::exchange(rhs.node_value_ptr, nullptr);
		}
		~Node() {
			delete node_value_ptr;
		}

		size_t node_number; //!< Index of the node in the graph
		T* node_value_ptr; //!< Pointer to the value of the node
	};

	/*Structure representing an edge in the graph*/
	struct Edge {
		Edge(size_t p_edge_next, T p_edge_value_ptr) : edge_next(p_edge_next), edge_value_ptr(new P(p_edge_value_ptr)) {}
		constexpr Edge(const Edge& rhs) {
			edge_next = rhs.edge_next;
			edge_value_ptr = new T(*rhs.edge_value_ptr);
		}
		Edge& operator= (Node&& rhs) noexcept {
			if(this == &rhs)
				return *this;
			delete edge_value_ptr;
			edge_next = std::exchange(rhs.edge_next, 0);
			edge_value_ptr = std::exchange(rhs.edge_value_ptr, nullptr);
		}
		~Edge() {
			delete edge_value_ptr;
		}

		size_t edge_next; //!< Index of the node edge is point to
		P* edge_value_ptr; //!< Pointer to the value of the edge
	};

	typedef struct Node Node;

	typedef struct Edge Edge;



public:
	
	friend class GBaseAlgorithm<T,P>;
	
	/**Default constructor*/
	Graph() {}
	
	/*Constructor taking initializer list as param*/
	explicit Graph(std::initializer_list<T> nodes);

	/**Default copy constructor*/
	constexpr Graph(const Graph& g) = default;

	/**Default copy assignment operator*/
	constexpr Graph& operator= (const Graph& rhs) = default;

	/**Default move constructor*/
	Graph(Graph&& g) noexcept = default;

	/**Default move assignment operator*/
	Graph& operator= (Graph&& rhs) noexcept = default;

	/**Default destructor*/
	~Graph() = default;

	/*Add node with the value T to the graph*/
	Graph<T, P>& add_node(T p_node) noexcept;

	/**Add nodes with the values given in the list to the graph*/
	Graph<T, P>& add_node(std::initializer_list<T> p_nodes) noexcept;

	/*Add edge with the value P to the graph*/
	Graph<T, P>& add_edge(size_t first, size_t second, P connection);

	/*Finds an index of the node with given value*/
	int get_node_idx(T p_value) const noexcept;

	/*Finds a value of the node with given index*/
	T get_node_value(size_t p_idx) const;

	/*Traverses the graph from the start node given, with an algorithm given*/
	void DFS(size_t p_start, GBaseAlgorithm<T, P>& p_algorithm);

	/*Traverses the graph from the start node given, with an algorithm given*/
	void BFS(size_t p_start, GBaseAlgorithm<T, P>& p_algorithm);

	/*Returns the size of the graph*/
	size_t size() const noexcept;

	/*Reserves given number of nodes*/
	void reserve_nodes(size_t p_idx);

private:

	/*Helps with DFS traversal*/
	void DFS_util(size_t p_start, GBaseAlgorithm<T, P>& p_algorithm);

	std::vector<Node> m_nodes_; //!< Vector of nodes in the graph
	std::vector<std::vector<Edge>> m_adj_matrix_; //!< 2D vector representing adjacency matrix
	size_t m_graph_size_ = 0; //!< Current size of the vector
};

/** Constructor taking initializer list as param
* @param p_nodes - initializer list of values to be added to the graph
*/
template<typename T, typename P>
inline Graph<T, P>::Graph(std::initializer_list<T> p_nodes)
{
	for (auto&& l_node : p_nodes) {
		m_nodes_.push_back(Node(m_graph_size_++, l_node));
		m_adj_matrix_.push_back({});
	}
}

/** Add node with the value T to the graph
* @param p_node - Value to be added to the graph
* @return reference to the graph
*/
template<typename T, typename P>
inline Graph<T, P>& Graph<T, P>::add_node(T p_node) noexcept
{
	m_nodes_.push_back(Node(m_graph_size_++, p_node));
	m_adj_matrix_.push_back({});
	return *this;
}

/** Add nodes with the values given in the list to the graph
* @param nodes - initializer list of values to be added to the graph
* @return reference to the graph
*/
template<typename T, typename P>
inline Graph<T, P>& Graph<T, P>::add_node(std::initializer_list<T> p_nodes) noexcept
{
	for (auto&& l_node : p_nodes) {
		m_nodes_.push_back(Node(m_graph_size_++, l_node));
		m_adj_matrix_.push_back({});
	}
	return *this;
}

/** Adds edge with the value P to the graph
 * @param p_first - index of the first node of the edge
 * @param p_second - index of the second node of the edge
 * @param p_connection - value of the edge
 * @return reference to the graph
*/
template<typename T, typename P>
inline Graph<T,P>& Graph<T, P>::add_edge(size_t p_first, size_t p_second, P p_connection)
{
	m_adj_matrix_[p_first].push_back(Edge(p_second, p_connection));
	return *this;
}

/** Finds an index of the node with given value
 * @param p_value - value to be searched for in graph
 * @return index of the node with the given value or -1 if no such node is found
*/
template<typename T, typename P>
inline int Graph<T, P>::get_node_idx(T p_value) const noexcept
{
	auto&& l_node_it = std::find_if(m_nodes_.begin(), m_nodes_.end(), [=](const Node& rhs) {return *rhs.node_value_ptr == p_value; });
	if(l_node_it == m_nodes_.end())
		return -1;
	else
		return std::distance(m_nodes_.begin(), l_node_it);
}

/** Finds a value of the node with given index
 * @param p_idx - index of the which value is to be returned
 * @throws std::out_of_range if given index is out of range
 * @return value of the node with the given index
 */
template<typename T, typename P>
inline T Graph<T,P>::get_node_value(size_t p_idx) const
{
	if(p_idx >= m_graph_size_)
		throw std::out_of_range("Given index is out of range");

	return *m_nodes_[p_idx].node_value_ptr;
}

/** Traverses the graph from the start node given, with an algorithm given
 * @param p_start - index of the node from which to start the traversal
 * @throws std::out_of_range if given index is out of range
 * @param p_algorithm - algorithm to be used in the traversal
 */
template<typename T, typename P>
inline void Graph<T, P>::DFS(size_t p_start, GBaseAlgorithm<T, P>& p_algorithm)
{
	if (!size())
		return;

	if(p_start >= m_graph_size_)
		throw std::out_of_range("Given index is out of range");

	p_algorithm.util_start(m_graph_size_, p_start, this);

	DFS_util(p_start, p_algorithm);

	p_algorithm.util_end();
}

/** Helps with DFS traversal
 * @param p_start - index of the node from which to start helper function
 * @param p_algorithm - parameter used in the traversal
 */
template<typename T, typename P>
inline void Graph<T, P>::DFS_util(size_t p_start, GBaseAlgorithm<T, P>& p_algorithm)
{
	
		p_algorithm.util_current_node_do(m_nodes_[p_start].node_number, m_nodes_[p_start].node_value_ptr);

		if(p_algorithm.finished())
			return;

		for (auto&& l_neighbor : p_algorithm.util_decide_next()) {
			if (!p_algorithm.is_visited(l_neighbor.edge_next))
				DFS_util(l_neighbor.edge_next, p_algorithm);
		}

		p_algorithm.util_callback(m_nodes_[p_start].node_number, m_nodes_[p_start].node_value_ptr);
}

/** Traverses the graph from the start node given, with an algorithm given
 * @param p_start - index of the node from which to start the traversal
 * @throws std::out_of_range if given index is out of range
 * @param p_algorithm - algorithm to be used in the traversal
 */
template<typename T, typename P>
inline void Graph<T, P>::BFS(size_t p_start, GBaseAlgorithm<T, P>& p_algorithm)
{
	//If there are no nodes in graph, return from the function
	if (!m_graph_size_)
		return;

	//Do start work with the algorithm
	p_algorithm.util_start(m_graph_size_, p_start, this); 

	//Create node queue and push starting node onto the queue
	std::queue<size_t> l_node_queue({ p_start });

	while (!l_node_queue.empty()) {
		

		//Pop starting node from the queue
		size_t current_node = l_node_queue.front();
		l_node_queue.pop();

		//If node is not visited, visit the node
		if (!p_algorithm.is_visited(current_node)) {
			p_algorithm.util_current_node_do(current_node, m_nodes_[current_node].node_value);
		}

		//If algorithm is finished, break from the loop
		if(p_algorithm.finished())
			break;

		//Decide which nodes will be visited next
		std::vector<typename Graph<T,P>::Edge> l_next_nodes = p_algorithm.util_decide_next();
		if (l_next_nodes.size())
			for (auto&& node : l_next_nodes)
				l_node_queue.push(node.edge_next);
	}

	//Do end work with the algorithm
	p_algorithm.util_end();
}


/** Returns the size of the graph
 * @return size of the graph 
 */ 
template<typename T, typename P>
inline size_t Graph<T,P>::size() const noexcept
{
	return m_graph_size_;
}

/** Reserves given number of nodes
 * @param p_idx - number of nodes to reserve
*/
template<typename T, typename P>
inline void Graph<T,P>::reserve_nodes(size_t p_idx) {
	m_nodes_.reserve(p_idx);
	m_adj_matrix_.reserve(p_idx);
};