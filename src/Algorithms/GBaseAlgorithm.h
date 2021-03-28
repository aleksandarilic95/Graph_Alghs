#pragma once



#include <vector>
#include <chrono>
#include <stack>
#include <algorithm>
#include <iterator>
#include <memory>
#include <stdexcept>




template <typename T, typename P>
class Graph;

template <typename T, typename P>
class GBaseAlgorithm
{
/*Algorithm API that needs to be overridden for the algorithm to work*/
public:
	virtual void start() = 0;
	virtual void current_node_do() = 0;
	virtual void decide_next(std::vector<typename Graph<T,P>::Edge>) {};
	virtual void end() = 0;
	virtual void callback() {};

/*Helper functions that make algorithms work*/
	void util_start(size_t, size_t, Graph<T,P>* p_graph);
	void util_end();
	std::vector<typename Graph<T,P>::Edge> util_decide_next();
	void util_current_node_do(size_t, T*);
	void util_callback(size_t, T*);

	/** Sets if algorithm should decide next nodes to visit
	 * @param p_tmp - bool if algorithm should enable decide_next()
	 */ 
	inline void set_decide_next(bool p_tmp) noexcept { F_DECIDE_NEXT_ALLOW_ = p_tmp; }

	//Finds the first unvisited node or returns -1 if every node has been visited
	int get_next() const noexcept {
		auto&& l_it = std::find(m_visited_nodes_, m_visited_nodes_ + m_graph_size_, false);
		if(l_it == m_visited_nodes_ + m_graph_size_)
			return -1;
		else
			return std::distance(m_visited_nodes_, l_it);
	}

/*Algorithm API for easier creating of algorithms*/
protected:
	size_t current_node_idx = 0; //< Index of the current node
	T* current_node_value_ptr = nullptr; //< Pointer to the value of the current node
	P* last_edge_ptr = nullptr; //< Pointer the value of the last edge
	
	/**	Returns neighbors of the given node
	 * @param p_idx - Index of the node
	 * @throws std::out_of_range if given index is out of range
	 * @returns std::vector<Edge> of neighbor edges
	 */
	std::vector<typename Graph<T,P>::Edge>& get_neighbors(size_t p_idx) const { 
		if(p_idx >= m_graph_size_)
			throw std::out_of_range("Given index is out of range");
		return m_graph_->m_adj_matrix_[p_idx]; 
		}


/*Private members to help algorithm function*/
private:
	Graph<T,P>* m_graph_ = nullptr; //Pointer to the graph for faster access to members

	bool* m_visited_nodes_ = nullptr; //< Array of if node has been visited
	bool* m_nodes_on_stack_ = nullptr; //< Array of if node is in queue to be visited (BFS and some DFS optimization)

	std::stack<std::pair<size_t, T*>> m_node_stack_; //< Stack of nodes traversed so far
	std::stack<P*> m_last_edges_; //< Stack of edges traversed so far

	bool F_FIRST_ALGORITHM_VISIT_ = true; //< Flag that indicates if it's first time visiting algorithm
	bool F_DECIDE_NEXT_ALLOW_ = false; //< Flag that indicates if decide_next() should be called

/*Public API for checking if algorithm has finished*/
private:
	bool F_ALGORITHM_FINISHED_ = false; //< Flag that indicates if algorithm is finished
protected:
	/** Sets algorithm to finished
	 */
	inline void finish_algorithm() noexcept { F_ALGORITHM_FINISHED_ = true; }	
public:
	/** Returns if algorithm is finished
	 * @return bool if algorithm is finished or not
	 */
	inline bool finished() const noexcept { return F_ALGORITHM_FINISHED_;}

/*Public API for starting node, graph size and check if visited*/
private:
	size_t m_start_node_ = 0; //< Node from which the traversal started
	size_t m_graph_size_ = 0; //< Graph size
public:
	/** Returns index of the node from which the traversal started
	 * @return index of the node from which the traversal started
	 */ 
	size_t start_node() const noexcept { return m_start_node_; }

	/** Returns the graph size
	 * @return graph size
	 */
	size_t graph_size() const noexcept { return m_graph_size_; }
	
	/** Returns if given node has been visited
	 * @param p_idx - index of the given node
	 * @throws std::out_of_range if given index is out of range
	 * @returns if given node has been visited
	 */
	bool is_visited(const size_t p_idx) const { 
		if(p_idx >= m_graph_size_)
			throw std::out_of_range("Given index is out of range");
		return m_visited_nodes_[p_idx];
	}

	/** Returns if given node is to be visited
	 * @param p_idx - index of the given node
	 * @throws std::out_of_range if given index is out of range
	 * @returns if given node is to be visited
	 */
	bool is_visited_on_stack(const size_t p_idx) const {
		if(p_idx >= m_graph_size_)
			throw std::out_of_range("Given index is out of range");
		return m_nodes_on_stack_[idx];
	}

/*Returns algorithm time if algorithm has reached it's end, otherwise returns 0*/
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_start_time_; //< Start time of the algorithm
	std::chrono::time_point<std::chrono::high_resolution_clock> m_end_time_; //< End time of the algorithm
	bool F_ALLOW_TIME_CHECK = false; //< Flag that indicates if algorithm time can be checked
public:
	/** Returns algorithm time in seconds
	 * @return algorithm time in seconds
	 */ 
	long long algorithm_time_s() const noexcept {
		return F_ALLOW_TIME_CHECK ? std::chrono::duration_cast<std::chrono::seconds>(m_end_time_ - m_start_time_).count() : 0;
	}

	/** Returns algorithm time in milliseconds
	 * @return algorithm time in milliseconds
	 */ 
	long long algorithm_time_ms() const noexcept {
		return F_ALLOW_TIME_CHECK ? std::chrono::duration_cast<std::chrono::milliseconds>(m_end_time_ - m_start_time_).count() : 0;
	}

	/** Returns algorithm time in microseconds
	 * @return algorithm time in microseconds
	 */ 
	long long algorithm_time_us() const noexcept {
		return F_ALLOW_TIME_CHECK ? std::chrono::duration_cast<std::chrono::microseconds>(m_end_time_ - m_start_time_).count() : 0;
	}

	/** Returns algorithm time in nanoseconds
	 * @return algorithm time in nanoseconds
	 */ 
	long long algorithm_time_ns() const noexcept {
		return F_ALLOW_TIME_CHECK ? std::chrono::duration_cast<std::chrono::nanoseconds>(m_end_time_ - m_start_time_).count() : 0;
	}

public:
	/** Virtual destructor
	 */
	virtual ~GBaseAlgorithm() {
		delete[] m_visited_nodes_;
		delete[] m_nodes_on_stack_;
	}
};

template<typename T, typename P>
inline void GBaseAlgorithm<T, P>::util_start(size_t p_node_size, size_t p_start_node, Graph<T,P>* p_graph)
{
	 //Start algorithm timer
	m_start_time_ = std::chrono::high_resolution_clock::now();

	//Initialize values needed for algorithm
	m_graph_size_ = p_node_size;
	m_start_node_ = p_start_node;
	m_graph_ = p_graph;

	//Initialize variables only the first time this function is visited (Allows multiple DFS with the algorithm keeping it's state)
	if (F_FIRST_ALGORITHM_VISIT_) {
		m_visited_nodes_ = new bool[m_graph_size_]();
		m_nodes_on_stack_ = new bool[m_graph_size_]();
		F_FIRST_ALGORITHM_VISIT_ = false;
	}

	start();
	
}

template<typename T, typename P>
inline void GBaseAlgorithm<T, P>::util_end()
{
	 //End algorithm timer
	m_end_time_ = std::chrono::high_resolution_clock::now();

	//Enable algorith time check
	m_allow_time_check_ = true; 

	end();

	//Disable algorithm time check
	m_allow_time_check_ = false; 
}

template<typename T, typename P>
inline std::vector<typename Graph<T,P>::Edge> GBaseAlgorithm<T, P>::util_decide_next()
{
	//Temporary vector in which we keep unvisited nodes
	std::vector<typename Graph<T,P>::Edge> l_result; 
	
	//Loop through the neighbor nodes and put unvisited (or ones that aren't yet planned to be visited) into the temp vector
	for(auto&& l_edge_ : m_graph_->m_adj_matrix_[current_node_idx])
		if (!m_nodes_on_stack_[l_edge_.edge_next]) {
			l_result.push_back(l_edge_);
			m_nodes_on_stack_[l_edge_.edge_next] = true;
		}

	//If flag is 1, allow modification of temp vector
	if(F_DECIDE_NEXT_ALLOW_)
		decide_next(l_result);

	//Put last edge onto the stack
	// if (!l_result_.empty())
	// 	last_edge_ptr = l_result_.front().m_edge_value_ptr_;

	//Return temp vector (NRVO)
	return l_result; 
}

template<typename T, typename P>
inline void GBaseAlgorithm<T, P>::util_current_node_do(size_t p_current_node_idx, T* p_current_node_value_ptr)
{
	//Initialize current node variables
	current_node_idx = p_current_node_idx;
	current_node_value_ptr = p_current_node_value_ptr;
	m_node_stack_.push(std::make_pair(p_current_node_idx, p_current_node_value_ptr));

	//Set current node to visited
	m_visited_nodes_[current_node_idx] = true; 
	
	current_node_do();
}

template<typename T, typename P>
inline void GBaseAlgorithm<T, P>::util_callback(size_t p_current_node_idx, T* p_current_node_value_ptr)
{
	//Initialize current node variables
	current_node_idx = p_current_node_idx;
	current_node_value_ptr = p_current_node_value_ptr;
	// last_edge_ptr = m_last_edges_.top();
	// m_last_edges_.pop();

	callback();
}


