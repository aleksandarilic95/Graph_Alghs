#pragma once

#include "../GBaseAlgorithm.h"
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

template <typename T, typename P>
class IsCyclicAlg : public GBaseAlgorithm<T, P> {
public:

	~IsCyclicAlg() {
		delete[] m_on_stack_;
	}

	void start() {
		m_on_stack_ = new bool[this->graph_size()]();
	};

	void end() {
	};

	void decide_next(std::vector<typename Graph<T,P>::Edge>& vec) {
	};

	void current_node_do() {
		m_on_stack_[this->current_node_idx] = true;
		for(auto&& i : this->get_neighbors(this->current_node_idx))
			if(m_on_stack_[i.m_edge_next_]) {
				result = true;
				this->finish_algorithm();
			}
	};

	void callback() {
		m_on_stack_[this->current_node_idx] = false;
	};
	
	constexpr bool get_result() const noexcept { return result; }
	
	
	
private:
	bool result = false;
	bool* m_on_stack_ = 0;
};
