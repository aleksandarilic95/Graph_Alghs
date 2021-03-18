#pragma once

#include "../GBaseAlgorithm.h"

template <typename T, typename P>
class FindAlg : public GBaseAlgorithm<T, P> {
public:
	FindAlg(T value) : m_value_(value), m_result_(-1) {};
	void start() {};
	void end() {};
	void decide_next(vector<pair<size_t, P>>& vec) {};
	void current_node_do() {
		if (this->current_node_value.getValue() == m_value_)
			m_result_ = this->current_node_idx;
	};
	constexpr int get_result() const noexcept {
		return m_result_;
	}
private:
	int m_result_;
	T m_value_;

};

template <typename T, typename P, class UnaryPredicate>
class FindIfAlg : public GBaseAlgorithm<T, P> {
public:
	FindIfAlg(UnaryPredicate p) : m_p_(p), m_result_(-1) {};
	void start() {};
	void end() {};
	void decide_next(vector<pair<size_t, P>>& vec) {};
	void current_node_do() {
		if (m_p_(this->current_node_value.getValue()))
			m_result_ = this->ccurrent_node_idx;
	};
	constexpr int get_result() const noexcept {
		return m_result_;
	}
private:
	int m_result_;
	UnaryPredicate m_p_;

};

template <typename T, typename P, class UnaryPredicate>
class FindIfNotAlg : public GBaseAlgorithm<T, P> {
public:
	FindIfNotAlg(UnaryPredicate p) : m_p_(p), m_result_(-1) {};
	void start() {};
	void end() {};
	void decide_next(vector<pair<size_t, P>>& vec) {};
	void current_node_do() {
		if (!m_p_(this->current_node_value.getValue()))
			m_result_ = this->current_node_idx;
	};
	constexpr int get_result() const noexcept {
		return m_result_;
	}
private:
	int m_result_;
	UnaryPredicate m_p_;

};
