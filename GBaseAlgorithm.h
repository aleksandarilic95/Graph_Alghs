#pragma once

#include "Node.h"
#include <vector>
#include <chrono>
#include <stack>

using namespace std;



template <typename T, typename P>
class GBaseAlgorithm
{
public:

	virtual void start() = 0;
	virtual void current_node_do() = 0;
	virtual void decide_next([[maybe_unused]] vector<pair<size_t, P>>&) {};
	virtual void end() = 0;

	void util_start(size_t, size_t, vector<vector<pair<size_t, P>>>);
	void util_end();
	vector<pair<size_t, P>> util_decide_next();
	void until_current_node_do(pair<size_t, Node<T>>);
protected:
	pair<size_t, Node<T>> current_node;
	P last_edge;
	vector<pair<size_t, P>> current_neighbors;
private:

	size_t m_start_node = 0;
	size_t m_graph_size = 0;
	vector<vector<pair<size_t, P>>> m_adj_matrix;
	stack<P> m_last_edges;
	vector<bool> m_visited_nodes;
public:
	constexpr size_t start_node() const noexcept { return m_start_node; }
	constexpr size_t graph_size() const noexcept { return m_graph_size; }
	constexpr bool is_visited(const size_t idx) const { 
		if (idx < 0 or idx >= m_graph_size)
			; //TODO: throw
		return m_visited_nodes[idx]; 
	}

/*Returns algorithm time if algorithm has reached it's end, otherwise returns 0*/
private:
	chrono::time_point<chrono::high_resolution_clock> m_start_time;
	chrono::time_point<chrono::high_resolution_clock> m_end_time;
	bool m_allow_time_check = false;
public:
	constexpr long long algorithm_time_s() const noexcept {
		return m_allow_time_check ? chrono::duration_cast<chrono::seconds>(m_end_time - m_start_time).count() : 0;
	}

	constexpr long long algorithm_time_ms() const noexcept {
		return m_allow_time_check ? chrono::duration_cast<chrono::milliseconds>(m_end_time - m_start_time).count() : 0;
	}

	constexpr long long algorithm_time_us() const noexcept {
		return m_allow_time_check ? chrono::duration_cast<chrono::microseconds>(m_end_time - m_start_time).count() : 0;
	}

	constexpr long long algorithm_time_ns() const noexcept {
		return m_allow_time_check ? chrono::duration_cast<chrono::nanoseconds>(m_end_time - m_start_time).count() : 0;
	}
/*******************************************************************************/

};

template<typename T, typename P>
inline void GBaseAlgorithm<T, P>::util_start(size_t p_node_size, size_t p_start_node, vector<vector<pair<size_t, P>>> p_adj_matrix)
{
	m_start_time = chrono::high_resolution_clock::now();
	m_graph_size = p_node_size;
	m_start_node = p_start_node;
	m_visited_nodes.assign(m_graph_size, false);
	m_adj_matrix = p_adj_matrix;

	start();
}

template<typename T, typename P>
inline void GBaseAlgorithm<T, P>::util_end()
{
	m_end_time = chrono::high_resolution_clock::now();
	m_allow_time_check = true;
	end();
	m_allow_time_check = false;
}

template<typename T, typename P>
inline vector<pair<size_t, P>> GBaseAlgorithm<T, P>::util_decide_next()
{
	//Puts every non-visited neighbor into the vector
	vector<pair<size_t, P>> result = m_adj_matrix[current_node.first];
	for (auto it = result.begin(); it != result.end();)
		if (is_visited(it->first))
			it = result.erase(it);
		else
			it++;

	//Sends vector to the user function
	decide_next(result);

	//Returns vector or empty vector if user decides so
	if (!result.empty())
		last_edge = result.front().second;
	return move(result);

}

template<typename T, typename P>
inline void GBaseAlgorithm<T, P>::until_current_node_do(pair<size_t, Node<T>> p_current_node)
{
	current_node = p_current_node;
	m_visited_nodes[current_node.first] = true;
	current_neighbors = m_adj_matrix.at(current_node.first);
	current_node_do();
}


