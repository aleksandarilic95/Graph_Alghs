#pragma once

#include "../GBaseAlgorithm.h"

template <typename T, typename P>
class TopSortAlg : public GBaseAlgorithm<T, P> {
public:
	void start() {
		if (!first_iter) {
			first_iter = true;
			m_visited_nodes_help_.assign(this->graph_size(), false);
			m_perm_nodes_.assign(this->graph_size(), false);
		}
	};
	void end() {};
	void decide_next(vector<pair<size_t, P>>& vec) {
		vec.clear();
		if (!m_perm_nodes_[this->current_node_idx]) {
			size_t count = 0;
			for (auto&& i : this->current_neighbors) {
				if (!m_visited_nodes_help_[i.first]) {
					vec.push_back(i);
					count++;
				}
			}
			if (!count) {
				m_result_.push_back(this->current_node_idx);
				m_perm_nodes_[this->current_node_idx] = true;
			}
			else
				vec.insert(vec.begin(), make_pair(this->current_node_idx, P(0)));
		}
		
	};
	void current_node_do() { m_visited_nodes_help_[this->current_node_idx] = true; };
	constexpr vector<size_t> get_result() const noexcept { return this->m_result_; }
	int get_next() {
		for (size_t i = 0; i < m_visited_nodes_help_.size(); i++)
			if (m_visited_nodes_help_[i] == false)
				return i;
		return -1;
	}
private:
	vector<bool> m_visited_nodes_help_;
	vector<bool> m_perm_nodes_;
	vector<size_t> m_result_;
	bool first_iter = false;
};
