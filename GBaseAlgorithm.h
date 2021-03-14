#pragma once

#include "Node.h"

#include <vector>
#include <chrono>
#include <stack>

using namespace std;

template <typename T, typename P>
class GBaseAlgorithm
{
/*Algorithm API that needs to be overridden for the algorithm to work*/
public:
	virtual void start() = 0;
	virtual void current_node_do() = 0;
	virtual void decide_next([[maybe_unused]] vector<pair<size_t, P>>&) {};
	virtual void end() = 0;
/*********************************************************************/

/*Helper functions that make algorithms work*/
	void util_start(size_t, size_t, vector<vector<pair<size_t, P>>>);
	void util_end();
	vector<pair<size_t, P>> util_decide_next();
	void until_current_node_do(pair<size_t, Node<T>>);
/********************************************/

/*Algorithm API for easier creating of algorithms*/
protected:
	pair<size_t, Node<T>> current_node;
	P last_edge;
	vector<pair<size_t, P>> current_neighbors;
/*************************************************/

/*Private members to help algorithm function*/
private:
	vector<vector<pair<size_t, P>>> m_adj_matrix_;
	stack<P> m_last_edges_;
	vector<bool> m_visited_nodes_;
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
inline void GBaseAlgorithm<T, P>::util_start(size_t p_node_size, size_t p_start_node, vector<vector<pair<size_t, P>>> p_adj_matrix)
{
	m_start_time_ = chrono::high_resolution_clock::now();
	m_graph_size_ = p_node_size;
	m_start_node_ = p_start_node;
	m_visited_nodes_.assign(m_graph_size_, false);
	m_adj_matrix_ = p_adj_matrix;

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
	for(auto it = m_adj_matrix_[current_node.first].begin(); it != m_adj_matrix_[current_node.first].end();it++)
		if (!is_visited(it->first))
			result_.push_back(*it);

	decide_next(result_);

	if (!result_.empty())
		last_edge = result_.front().second;
	return move(result_);
}

template<typename T, typename P>
inline void GBaseAlgorithm<T, P>::until_current_node_do(pair<size_t, Node<T>> p_current_node)
{
	current_node = p_current_node;
	m_visited_nodes_[current_node.first] = true;
	current_neighbors = m_adj_matrix_.at(current_node.first);

	current_node_do();
}


