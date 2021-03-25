#pragma once

#include "../GBaseAlgorithm.h"

template <typename T, typename P>
class FindAlg : public GBaseAlgorithm<T, P> {
public:
	FindAlg(T p_value) : m_value_(std::move(p_value)) {}
	void start() {};
	void end() {};
	void decide_next(std::vector<typename Graph<T,P>::Edge>& vec) {};
	void current_node_do() {
		if (*(this->current_node_value_ptr) == m_value_)
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
	FindIfAlg(UnaryPredicate p_predicate) : m_p_(p_predicate) {}
	void start() {};
	void end() {};
	void decide_next(std::vector<typename Graph<T,P>::Edge>& vec) {};
	void current_node_do() {
		if (m_p_(*(this->current_node_value_ptr)))
			m_result_ = this->current_node_idx;
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
	FindIfNotAlg(UnaryPredicate p_predicate) : m_p_(p_predicate) {}
	void start() {};
	void end() {};
	void decide_next(std::vector<typename Graph<T,P>::Edge>& vec) {};
	void current_node_do() {
		if (!m_p_(*(this->current_node_value_ptr)))
			m_result_ = this->current_node_idx;
	};
	constexpr int get_result() const noexcept {
		return m_result_;
	}
private:
	int m_result_;
	UnaryPredicate m_p_;

};
