#pragma once

#include "../GBaseAlgorithm.h"

template <typename T, typename P, class UnaryPredicate>
class AllOfAlg : public GBaseAlgorithm<T, P> {
public:

	AllOfAlg(UnaryPredicate p_predicate) : m_p_(p_predicate) {}
	void start() {};
	void end() {};
	void decide_next(std::vector<typename Graph<T,P>::Edge>& vec) {};
	void current_node_do() {
		if (!m_p_(*(this->current_node_value_ptr))) {
			m_result_ = false;
			this->finish_algorithm();
		}
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

	AnyOfAlg(UnaryPredicate p_predicate) : m_p_(p_predicate) {}
	void start() {};
	void end() {};
	void decide_next(std::vector<typename Graph<T,P>::Edge>& vec) {};
	void current_node_do() {
		if (m_p_(*(this->current_node_value_ptr)))
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
	NoneOfAlg(UnaryPredicate p_predicate) : m_p_(p_predicate) {}
	void start() {};
	void end() {};
	void decide_next(std::vector<typename Graph<T,P>::Edge>& vec) {};
	void current_node_do() {
		if (m_p_(*(this->current_node_value_ptr))) {
			m_result_ = false;
			this->finish_algorithm();
		}
	}
	constexpr int get_result() const noexcept {
		return m_result_;
	}
private:
	bool m_result_;
	UnaryPredicate m_p_;

};