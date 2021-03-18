#pragma once

#include "../GBaseAlgorithm.h"

template <typename T, typename P>
class IsCyclicAlg : public GBaseAlgorithm<T, P> {
public:
	void start() {
		m_node_color_.assign(this->graph_size(), 0);
		m_node_color_stack_.push(make_pair(this->start_node(), 0));
	};
	void end() {};
	void decide_next(vector<pair<size_t, P>>& vec);
	void current_node_do() {};
	constexpr bool get_result() const noexcept {
		return m_result_;
	}
private:
	stack<pair<size_t, size_t>> m_node_color_stack_;
	vector<size_t> m_node_color_;
	bool m_result_ = false;
};

template<typename T, typename P>
inline void IsCyclicAlg<T, P>::decide_next(vector<pair<size_t, P>>& vec)
{
	vector<pair<size_t, P>> return_vec;
	pair<size_t, size_t> current_stack_pair = m_node_color_stack_.top();
	m_node_color_stack_.pop();
	if (current_stack_pair.second == 1)
		m_node_color_[current_stack_pair.first] = 2;
	else if (m_node_color_[current_stack_pair.first] != 2) {
		m_node_color_[current_stack_pair.first] = 1;
		m_node_color_stack_.push(make_pair(this->current_node_idx, 1));
		for (auto&& i : this->current_neighbors)
			if (m_node_color_[i.first] == 1) {
				m_result_ = true;
				return;
			}
			else if (m_node_color_[i.first] == 0) {
				return_vec.push_back(make_pair(i.first, P(0)));
				m_node_color_stack_.push(make_pair(i.first, 0));
			}
		return_vec.insert(return_vec.begin(), make_pair(this->current_node_idx, P(0)));
		vec.clear();
		copy(return_vec.begin(), return_vec.end(), back_inserter(vec));
	}

}