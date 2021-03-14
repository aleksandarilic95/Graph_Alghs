#pragma once

#include "GBaseAlgorithm.h"

template <typename T, typename P>
class IsCyclicAlg : public GBaseAlgorithm<T, P> {
public:
	void start() {
		node_color.assign(this->graph_size(), 0);
		node_color_stack.push(make_pair(this->start_node(), 0));
	};
	void end() {};
	void decide_next(vector<pair<size_t, P>>& vec);
	void current_node_do() {};
	constexpr bool get_result() const noexcept {
		return result;
	}
private:
	stack<pair<size_t, size_t>> node_color_stack;
	vector<size_t> node_color;
	bool result = false;
};

template<typename T, typename P>
inline void IsCyclicAlg<T, P>::decide_next(vector<pair<size_t, P>>& vec)
{
	vector<pair<size_t, P>> return_vec;
	pair<size_t, size_t> current_stack_pair = node_color_stack.top();
	node_color_stack.pop();
	if (current_stack_pair.second == 1)
		node_color[current_stack_pair.first] = 2;
	else if (node_color[current_stack_pair.first] != 2) {
		node_color[current_stack_pair.first] = 1;
		node_color_stack.push(make_pair(this->current_node.first, 1));
		for (auto&& i : this->current_neighbors)
			if (node_color[i.first] == 1) {
				result = true;
				return;
			}
			else if (node_color[i.first] == 0) {
				return_vec.push_back(make_pair(i.first, P(0)));
				node_color_stack.push(make_pair(i.first, 0));
			}
		return_vec.insert(return_vec.begin(), make_pair(this->current_node.first, P(0)));
		vec.clear();
		copy(return_vec.begin(), return_vec.end(), back_inserter(vec));
	}

}