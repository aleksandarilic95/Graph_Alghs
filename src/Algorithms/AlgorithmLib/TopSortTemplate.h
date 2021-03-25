#pragma once

#include "../GBaseAlgorithm.h"

template <typename T, typename P>
class TopSortAlg : public GBaseAlgorithm<T, P> {
public:
	void start() {};
	void end() {};
	void decide_next(std::vector<typename Graph<T,P>::Edge>& vec) {};
	void current_node_do() {};

	void callback() {
		m_result_.push_back(this->current_node_idx);
	};

	constexpr std::vector<size_t> get_result() const noexcept { 
		return this->m_result_; 
	}
private:
	std::vector<size_t> m_result_;
};
