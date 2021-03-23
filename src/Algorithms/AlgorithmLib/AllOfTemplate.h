#pragma once

#include "../GBaseAlgorithm.h"

template <typename T, typename P, class UnaryPredicate>
class AllOfAlg : public GBaseAlgorithm<T, P> {
public:
	AllOfAlg(Graph<T,P>& g, UnaryPredicate p) : m_p_(p), m_result_(true), GBaseAlgorithm<T,P>(g) {};
	void start() {};
	void end() {
		cout << (double)this->algorithm_time_us() / 1E6 << endl;};
	void decide_next(vector<pair<size_t, P>>& vec) {};
	void current_node_do() {
		if (!m_p_(this->current_node_value.getValue()))
			m_result_ = false;
	};
	constexpr int get_result() const noexcept {
		return m_result_;
	}
private:
	bool m_result_;
	UnaryPredicate m_p_;

};

template <typename T, typename P, class UnaryPredicate>
class AnyOfAlg : public GBaseAlgorithm<T, P> {
public:
	AnyOfAlg(Graph<T,P>& g, UnaryPredicate p) : m_p_(p), m_result_(true), GBaseAlgorithm<T,P>(g) {};
	void start() {};
	void end() {
		cout << (double)this->algorithm_time_us() / 1E6 << endl;};
	void decide_next(vector<pair<size_t, P>>& vec) {};
	void current_node_do() {
		if (m_p_(this->current_node_value.getValue()))
			m_result_ = true;
	};
	constexpr int get_result() const noexcept {
		return m_result_;
	}
private:
	bool m_result_;
	UnaryPredicate m_p_;

};

template <typename T, typename P, class UnaryPredicate>
class NoneOfAlg : public GBaseAlgorithm<T, P> {
public:
	NoneOfAlg(Graph<T,P>& g, UnaryPredicate p) : m_p_(p), m_result_(true), GBaseAlgorithm<T,P>(g) {};
	void start() {};
	void end() {
		cout << (double)this->algorithm_time_us() / 1E6 << endl;};
	void decide_next(vector<pair<size_t, P>>& vec) {};
	void current_node_do() {
		if (m_p_(this->current_node_value.getValue()))
			m_result_ = false;
	};
	constexpr int get_result() const noexcept {
		return m_result_;
	}
private:
	bool m_result_;
	UnaryPredicate m_p_;

};