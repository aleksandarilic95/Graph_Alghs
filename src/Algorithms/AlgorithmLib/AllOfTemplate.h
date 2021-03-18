#pragma once

#include "../GBaseAlgorithm.h"

template <typename T, typename P, class UnaryPredicate>
class AllOfAlg : public GBaseAlgorithm<T, P> {
public:
	AllOfAlg(UnaryPredicate p) : m_p_(p), m_result_(true) {};
	void start() {};
	void end() {};
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
	AnyOfAlg(UnaryPredicate p) : m_p_(p), m_result_(false) {};
	void start() {};
	void end() {};
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
	NoneOfAlg(UnaryPredicate p) : m_p_(p), m_result_(true) {};
	void start() {};
	void end() {};
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