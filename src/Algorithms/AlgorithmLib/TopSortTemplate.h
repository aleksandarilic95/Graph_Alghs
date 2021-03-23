#pragma once

#include "../GBaseAlgorithm.h"

template <typename T, typename P>
class TopSortAlg : public GBaseAlgorithm<T, P> {
public:
	TopSortAlg(Graph<T,P>& g) : GBaseAlgorithm<T,P>(g) {}
	void start() {};
	void end() {
		cout << (double)this->algorithm_time_us() / 1E6 << endl;
	};
	void decide_next(vector<pair<size_t, P>>& vec) {};
	void current_node_do() {};

	void callback() {
		m_result_.push_back(this->current_node_idx);
	};

	constexpr vector<size_t> get_result() const noexcept { 
		return this->m_result_; 
	}
private:
	vector<size_t> m_result_;
};
