#pragma once



#include <vector>
#include <chrono>
#include <stack>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <memory>




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

	void set_decide_next(bool tmp) noexcept { F_DECIDE_NEXT_ALLOW_ = tmp; }

	//Finds the first unvisited node or returns -1 if every node has been visited
	int get_next() const noexcept {
		auto&& l_it_ = std::find(m_visited_nodes_, m_visited_nodes_ + m_graph_size_, false);
		if(l_it_ == m_visited_nodes_ + m_graph_size_)
			return -1;
		else
			return std::distance(m_visited_nodes_, l_it_);
	}

/*Algorithm API for easier creating of algorithms*/
protected:
	size_t current_node_idx = 0;
	T* current_node_value_ptr = nullptr;
	P* last_edge_ptr = nullptr;
	
	std::vector<typename Graph<T,P>::Edge>& get_neighbors(size_t p_idx) const { return m_graph_->m_adj_matrix_[p_idx]; }
	void finish_algorithm() noexcept { m_algorithm_finished_ = true; }	

/*Private members to help algorithm function*/
private:
	Graph<T,P>* m_graph_ = nullptr;

	bool* m_visited_nodes_ = nullptr;
	bool* m_nodes_on_stack_ = nullptr;

	std::stack<std::pair<size_t, T*>> m_node_stack_;
	std::stack<P*> m_last_edges_;

	bool F_FIRST_ALGORITHM_VISIT_ = true;
	bool F_DECIDE_NEXT_ALLOW_ = false;

/*Public API for checking if algorithm has finished*/
private:
	bool m_algorithm_finished_ = false;
public:
	bool finished() const noexcept { return m_algorithm_finished_;}

/*Public API for starting node, graph size and check if visited*/
private:
	size_t m_start_node_ = 0;
	size_t m_graph_size_ = 0;
public:
	size_t start_node() const noexcept { return m_start_node_; }
	size_t graph_size() const noexcept { return m_graph_size_; }
	
	bool is_visited(const size_t idx) const { 
		return m_visited_nodes_[idx];
	}

	bool is_visited_on_stack(const size_t idx) const {
		return m_nodes_on_stack_[idx];
	}

/*Returns algorithm time if algorithm has reached it's end, otherwise returns 0*/
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_start_time_;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_end_time_;
	bool m_allow_time_check_ = false;
public:
	long long algorithm_time_s() const noexcept {
		return m_allow_time_check_ ? std::chrono::duration_cast<std::chrono::seconds>(m_end_time_ - m_start_time_).count() : 0;
	}

	long long algorithm_time_ms() const noexcept {
		return m_allow_time_check_ ? std::chrono::duration_cast<std::chrono::milliseconds>(m_end_time_ - m_start_time_).count() : 0;
	}

	long long algorithm_time_us() const noexcept {
		return m_allow_time_check_ ? std::chrono::duration_cast<std::chrono::microseconds>(m_end_time_ - m_start_time_).count() : 0;
	}

	long long algorithm_time_ns() const noexcept {
		return m_allow_time_check_ ? std::chrono::duration_cast<std::chrono::nanoseconds>(m_end_time_ - m_start_time_).count() : 0;
	}

public:
	virtual ~GBaseAlgorithm() {
		delete[] m_visited_nodes_;
		delete[] m_nodes_on_stack_;
	}
};

template<typename T, typename P>
inline void GBaseAlgorithm<T, P>::util_start(size_t p_node_size, size_t p_start_node, Graph<T,P>* p_graph)
{
	m_start_time_ = std::chrono::high_resolution_clock::now(); //Start algorithm timer

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
	m_end_time_ = std::chrono::high_resolution_clock::now(); //End algorithm timer

	m_allow_time_check_ = true; //Enable algorith time check

	end();

	m_allow_time_check_ = false; //Disable algorithm time check
}

template<typename T, typename P>
inline std::vector<typename Graph<T,P>::Edge> GBaseAlgorithm<T, P>::util_decide_next()
{
	std::vector<typename Graph<T,P>::Edge> l_result_; //Temporary vector in which we keep unvisited nodes
	
	//Loop through the neighbor nodes and put unvisited (or ones that aren't yet planned to be visited) into the temp vector
	for(auto&& l_edge_ : m_graph_->m_adj_matrix_[current_node_idx])
		if (!m_nodes_on_stack_[l_edge_.m_edge_next_]) {
			l_result_.push_back(l_edge_);
			m_nodes_on_stack_[l_edge_.m_edge_next_] = true;
		}

	//If flag is 1, allow modification of temp vector
	if(F_DECIDE_NEXT_ALLOW_)
		decide_next(l_result_);

	//Put last edge onto the stack
	if (!l_result_.empty())
		last_edge_ptr = l_result_.front().m_edge_value_ptr_;

	//Return temp vector (NRVO)
	return l_result_; 
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


