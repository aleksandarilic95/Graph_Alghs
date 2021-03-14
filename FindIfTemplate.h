#pragma once

#include "GBaseAlgorithm.h"

template <typename T, typename P>
class FindAlg : public GBaseAlgorithm<T, P> {
public:
	FindAlg(T value) : m_value(value), result(-1) {};
	void start() {};
	void end() {};
	void decide_next(vector<pair<size_t, P>>& vec) {};
	void current_node_do() {
		if (this->current_node.second.getValue() == m_value)
			result = this->current_node.first;
	};
	constexpr int get_result() const noexcept {
		return result;
	}
private:
	int result;
	T m_value;

};

template <typename T, typename P, class UnaryPredicate>
class FindIfAlg : public GBaseAlgorithm<T, P> {
public:
	FindIfAlg(UnaryPredicate p) : m_p(p), result(-1) {};
	void start() {};
	void end() {};
	void decide_next(vector<pair<size_t, P>>& vec) {};
	void current_node_do() {
		if (m_p(this->current_node.second.getValue()))
			result = this->current_node.first;
	};
	constexpr int get_result() const noexcept {
		return result;
	}
private:
	int result;
	UnaryPredicate m_p;

};

template <typename T, typename P, class UnaryPredicate>
class FindIfNotAlg : public GBaseAlgorithm<T, P> {
public:
	FindIfNotAlg(UnaryPredicate p) : m_p(p), result(-1) {};
	void start() {};
	void end() {};
	void decide_next(vector<pair<size_t, P>>& vec) {};
	void current_node_do() {
		if (!m_p(this->current_node.second.getValue()))
			result = this->current_node.first;
	};
	constexpr int get_result() const noexcept {
		return result;
	}
private:
	int result;
	UnaryPredicate m_p;

};
