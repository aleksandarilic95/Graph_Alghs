#pragma once

#include "../GBaseAlgorithm.h"
#include <iostream>
#include <vector>
#include <stack>

template <typename T, typename P>
class IsCyclicAlg : public GBaseAlgorithm<T, P> {
public:
	IsCyclicAlg<T,P>(Graph<T,P>& g) : GBaseAlgorithm<T,P>(g) {}

	void start() {
		m_on_stack_.assign(this->graph_size(), false);
	};

	void end() {
		cout << (double)this->algorithm_time_us() / 1E6 << endl;
	};

	void decide_next(vector<pair<size_t, P>>& vec) {
	};

	void current_node_do() {
		m_on_stack_[this->current_node_idx] = true;
		for(auto&& i : this->get_neighbors(this->current_node_idx))
			if(m_on_stack_[i.first])
				result = true;
	};

	void callback() {
		m_on_stack_[this->current_node_idx] = false;
	};
	
	constexpr bool get_result() const noexcept { return result; }
	
	
	
private:
	bool result = false;
	std::vector<bool> m_on_stack_;	
};
