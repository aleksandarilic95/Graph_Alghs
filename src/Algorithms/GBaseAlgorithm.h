#pragma once

#include "../Graph/Node.h"

#include <vector>
#include <chrono>
#include <stack>
#include <iostream>
#include <algorithm>

using namespace std;

template <typename T, typename P>
class Graph;

template <typename T, typename P>
class GBaseAlgorithm
{
/*Algorithm API that needs to be overridden for the algorithm to work*/
public:
	explicit GBaseAlgorithm<T,P>(Graph<T,P>& p_graph_) : m_graph_(p_graph_){};

	virtual void start() = 0;
	virtual void current_node_do() = 0;
	virtual void decide_next(vector<pair<size_t, P>>&) {};
	virtual void end() = 0;
	virtual void callback() {}
	virtual void check_1(size_t current_node_idx_check_1) {}
/*********************************************************************/

/*Helper functions that make algorithms work*/
	void util_start(size_t, size_t, Graph<T,P>& p_graph);
	void util_end();
	vector<pair<size_t, P>> util_decide_next();
	void util_current_node_do(pair<Node<T>, size_t>);
	void util_callback();
	int get_next() {
		auto&& it = std::find_if(m_visited_nodes_.begin(), m_visited_nodes_.end(), [=](bool p_curr) {return p_curr == false;});
		if(it == m_visited_nodes_.end())
			return -1;
		else
			return std::distance(m_visited_nodes_.begin(), it);
	}
	void set_decide_next(bool tmp) noexcept { F_DECIDE_NEXT_ALLOW = tmp; }
/********************************************/

/*Algorithm API for easier creating of algorithms*/
protected:
	
	
	size_t current_node_idx;
	Node<T> current_node_value;
	P last_edge;
	vector<pair<size_t, P>> current_neighbors;
	
	bool F_DECIDE_NEXT_ALLOW = false;
	auto& get_neighbors(size_t idx) { return m_graph_.m_adj_matrix_[idx]; }	
/*************************************************/

/*Private members to help algorithm function*/
private:
	stack<pair<Node<T>, size_t>> node_stack;
	bool first = true;
	vector<vector<pair<size_t, P>>> m_adj_matrix_;
	stack<P> m_last_edges_;
	vector<bool> m_visited_nodes_;
	Graph<T,P>& m_graph_;
	
	vector<bool> m_nodes_on_stack_;
/********************************************/

/*Public API for starting node, graph size and check if visited*/
private:
	size_t m_start_node_;
	size_t m_graph_size_;
public:
	constexpr size_t start_node() const noexcept { return m_start_node_; }
	constexpr size_t graph_size() const noexcept { return m_graph_size_; }
	constexpr bool is_visited(const size_t idx) const { 
		if (idx < 0 || idx >= m_graph_size_)
			; //TODO: throw
		return m_visited_nodes_[idx];
	}
/***************************************************************/

/*Returns algorithm time if algorithm has reached it's end, otherwise returns 0*/
private:
	chrono::time_point<chrono::high_resolution_clock> m_start_time_;
	chrono::time_point<chrono::high_resolution_clock> m_end_time_;
	bool m_allow_time_check_ = false;
public:
	constexpr long long algorithm_time_s() const noexcept {
		return m_allow_time_check_ ? chrono::duration_cast<chrono::seconds>(m_end_time_ - m_start_time_).count() : 0;
	}

	constexpr long long algorithm_time_ms() const noexcept {
		return m_allow_time_check_ ? chrono::duration_cast<chrono::milliseconds>(m_end_time_ - m_start_time_).count() : 0;
	}

	constexpr long long algorithm_time_us() const noexcept {
		return m_allow_time_check_ ? chrono::duration_cast<chrono::microseconds>(m_end_time_ - m_start_time_).count() : 0;
	}

	constexpr long long algorithm_time_ns() const noexcept {
		return m_allow_time_check_ ? chrono::duration_cast<chrono::nanoseconds>(m_end_time_ - m_start_time_).count() : 0;
	}
/*******************************************************************************/

};

template<typename T, typename P>
inline void GBaseAlgorithm<T, P>::util_start(size_t p_node_size, size_t p_start_node, Graph<T,P>& p_graph)
{
	m_start_time_ = chrono::high_resolution_clock::now();
	m_graph_size_ = p_node_size;
	m_start_node_ = p_start_node;
	if (first) {
		m_visited_nodes_.assign(m_graph_size_, false);
		m_nodes_on_stack_.assign(m_graph_size_, false);
		first = false;
	}
	m_graph_ = p_graph;
	start();
	
}

template<typename T, typename P>
inline void GBaseAlgorithm<T, P>::util_end()
{
	m_end_time_ = chrono::high_resolution_clock::now();
	m_allow_time_check_ = true;

	end();

	m_allow_time_check_ = false;
}

template<typename T, typename P>
inline vector<pair<size_t, P>> GBaseAlgorithm<T, P>::util_decide_next()
{
	//Puts every non-visited neighbor into the vector

	vector<pair<size_t, P>> result_;
	
	for(auto it = m_graph_.m_adj_matrix_[current_node_idx].begin(); it != m_graph_.m_adj_matrix_[current_node_idx].end(); it++)
		if (!m_nodes_on_stack_[it->first]) {
			result_.push_back(*it);
			m_nodes_on_stack_[it->first] = true;
		}

	if(F_DECIDE_NEXT_ALLOW)
		decide_next(result_);

	

	if (!result_.empty())
		last_edge = result_.front().second;
	return move(result_);
}

template<typename T, typename P>
inline void GBaseAlgorithm<T, P>::util_current_node_do(pair<Node<T>, size_t> p_current_node)
{
	
	node_stack.push(p_current_node);
	
	current_node_idx = p_current_node.second;
	current_node_value = p_current_node.first;
	
	m_visited_nodes_[current_node_idx] = true;
	
	current_neighbors = get_neighbors(current_node_idx);
	
	current_node_do();

}

template<typename T, typename P>
inline void GBaseAlgorithm<T, P>::util_callback()
{
	auto current_node_temp = node_stack.top();
	node_stack.pop();
	current_node_idx = current_node_temp.second;
	current_node_value = current_node_temp.first;
	callback();
}


