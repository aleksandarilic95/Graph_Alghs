#pragma once

#include "GBaseAlgorithm.h"

template <typename T, typename P, class UnaryPredicate>
class AllOfAlg : public GBaseAlgorithm<T, P> {
public:
	AllOfAlg(UnaryPredicate p) : m_p(p), result(true) {};
	void start() {};
	void end() {};
	void decide_next(vector<pair<size_t, P>>& vec) {};
	void current_node_do() {
		if (!m_p(this->current_node.second.getValue()))
			result = false;
	};
	constexpr int get_result() const noexcept {
		return result;
	}
private:
	bool result;
	UnaryPredicate m_p;

};

template <typename T, typename P, class UnaryPredicate>
class AnyOfAlg : public GBaseAlgorithm<T, P> {
public:
	AnyOfAlg(UnaryPredicate p) : m_p(p), result(false) {};
	void start() {};
	void end() {};
	void decide_next(vector<pair<size_t, P>>& vec) {};
	void current_node_do() {
		if (m_p(this->current_node.second.getValue()))
			result = true;
	};
	constexpr int get_result() const noexcept {
		return result;
	}
private:
	bool result;
	UnaryPredicate m_p;

};

template <typename T, typename P, class UnaryPredicate>
class NoneOfAlg : public GBaseAlgorithm<T, P> {
public:
	NoneOfAlg(UnaryPredicate p) : m_p(p), result(true) {};
	void start() {};
	void end() {};
	void decide_next(vector<pair<size_t, P>>& vec) {};
	void current_node_do() {
		if (m_p(this->current_node.second.getValue()))
			result = false;
	};
	constexpr int get_result() const noexcept {
		return result;
	}
private:
	bool result;
	UnaryPredicate m_p;

};