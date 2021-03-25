#pragma once

#include "../../Graph/Graph.h"

#include "IsCyclicTemplate.h"
#include "FindIfTemplate.h"
#include "AllOfTemplate.h"
#include "TopSortTemplate.h"
#include "MSTTemplate.h"

#include <vector>
#include <iostream>
#include <algorithm>


namespace galgs {

	template<typename T, typename P>
	constexpr bool is_cyclic(Graph<T, P>& g, size_t start = 0)
	{
		IsCyclicAlg<T, P> ica;
		int next = start;
		g.DFS(next, ica);
		while (!ica.finished() && (next = ica.get_next()) != -1) {
			g.DFS(next, ica);
		}
		return ica.get_result();
	}

	template<typename T, typename P>
	constexpr int find(Graph<T, P>& g, T value, size_t start = 0) 
	{
		FindAlg<T, P> f(value);
		int next = start;
		g.DFS(next, f);
		while ((next = f.get_next()) != -1) {
			g.DFS(next, f);
		}
		return f.get_result();
	}

	template<typename T, typename P, class UnaryPredicate>
	constexpr int find_if(Graph<T, P>& g, UnaryPredicate p, size_t start = 0)
	{
		FindIfAlg<T, P, UnaryPredicate> fi(p);
		int next = start;
		g.DFS(next, fi);
		while ((next = fi.get_next()) != -1) {
			g.DFS(next, fi);
		}
		return fi.get_result();
	}

	template<typename T, typename P, class UnaryPredicate>
	constexpr int find_if_not(Graph<T, P>& g, UnaryPredicate p, size_t start = 0)
	{
		FindIfNotAlg<T, P, UnaryPredicate> fin(p); 
		int next = start;
		g.DFS(next, fin);
		while ((next = fin.get_next()) != -1) {
			g.DFS(next, fin);
		}
		return fin.get_result();
	}

	template<typename T, typename P, class UnaryPredicate>
	constexpr bool all_of(Graph<T, P>& g, UnaryPredicate p, size_t start = 0)
	{
		AllOfAlg<T, P, UnaryPredicate> ao(p);
		int next = start;
		g.DFS(next, ao);
		while (!ao.finished() && (next = ao.get_next()) != -1) {
			g.DFS(next, ao);
		}
		return ao.get_result();
	}

	template<typename T, typename P, class UnaryPredicate>
	constexpr bool any_of(Graph<T, P>& g, UnaryPredicate p, size_t start = 0)
	{
		AnyOfAlg<T, P, UnaryPredicate> ao(p);
		int next = start;
		g.DFS(next, ao);
		while (!ao.finished() && (next = ao.get_next()) != -1) {
			g.DFS(next, ao);
		}
		return ao.get_result();
	}

	template<typename T, typename P, class UnaryPredicate>
	constexpr bool none_of(Graph<T, P>& g, UnaryPredicate p, size_t start = 0)
	{
		NoneOfAlg<T, P, UnaryPredicate> no(p);
		int next = start;
		g.DFS(next, no);
		while (!no.finished() && (next = no.get_next()) != -1) {
			g.DFS(next, no);
		}
		return no.get_result();
	}

	template<typename T, typename P>
	std::vector<size_t> top_sort (Graph<T, P>& g, size_t start = 0)
	{
		if (is_cyclic(g))
			return {};
		TopSortAlg<T, P> ts;
		int next = start;
		g.DFS(next, ts);
		while (!ts.finished() && (next = ts.get_next()) != -1) {
			g.DFS(next, ts);
		}
		return ts.get_result();
	}

	template <typename T, typename P>
	Graph<T, P> mst(Graph<T, P>& g) {

	}

	

	




}
