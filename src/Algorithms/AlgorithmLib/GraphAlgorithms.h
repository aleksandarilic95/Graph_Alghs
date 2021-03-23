#pragma once

#include "../../Graph/Graph.h"
#include <algorithm>

#include "IsCyclicTemplate.h"
#include "FindIfTemplate.h"
#include "AllOfTemplate.h"
#include "TopSortTemplate.h"
#include "MSTTemplate.h"

#include <vector>
#include <iostream>

using namespace std;

namespace galgs {

	template<typename T, typename P>
	constexpr bool is_cyclic(Graph<T, P>& g, size_t start = 0)
	{
		IsCyclicAlg<T, P> ica(g);
		int next = start;
		g.DFS(next, ica);
		while ((next = ica.get_next()) != -1) {
			g.DFS(next, ica);
		}
		return ica.get_result();
	}

	template<typename T, typename P>
	constexpr int find(Graph<T, P>& g, T value) 
	{
		FindAlg<T, P> f(g, value);
		int next = 0;
		g.DFS(next, f);
		while ((next = f.get_next()) != -1) {
			g.DFS(next, f);
		}
		return f.get_result();
	}

	template<typename T, typename P, class UnaryPredicate>
	constexpr int find_if(Graph<T, P>& g, UnaryPredicate p)
	{
		FindIfAlg<T, P, UnaryPredicate> fi(g, p);
		int next = 0;
		g.DFS(next, fi);
		while ((next = fi.get_next()) != -1) {
			g.DFS(next, fi);
		}
		return fi.get_result();
	}

	template<typename T, typename P, class UnaryPredicate>
	constexpr int find_if_not(Graph<T, P>& g, UnaryPredicate p)
	{
		FindIfNotAlg<T, P, UnaryPredicate> fin(g, p); 
		int next = 0;
		g.DFS(next, fin);
		while ((next = fin.get_next()) != -1) {
			g.DFS(next, fin);
		}
		return fin.get_result();
	}

	template<typename T, typename P, class UnaryPredicate>
	constexpr bool all_of(Graph<T, P>& g, UnaryPredicate p)
	{
		AllOfAlg<T, P, UnaryPredicate> ao(g, p);
		int next = 0;
		g.DFS(next, ao);
		while ((next = ao.get_next()) != -1) {
			g.DFS(next, ao);
		}
		return ao.get_result();
	}

	template<typename T, typename P, class UnaryPredicate>
	constexpr bool any_of(Graph<T, P>& g, UnaryPredicate p)
	{
		AnyOfAlg<T, P, UnaryPredicate> ao(g, p);
		int next = 0;
		g.DFS(next, ao);
		while ((next = ao.get_next()) != -1) {
			g.DFS(next, ao);
		}
		return ao.get_result();
	}

	template<typename T, typename P, class UnaryPredicate>
	constexpr bool none_of(Graph<T, P>& g, UnaryPredicate p)
	{
		NoneOfAlg<T, P, UnaryPredicate> no(g, p);
		int next = 999;
		g.DFS(next, no);
		while ((next = no.get_next()) != -1) {
			g.DFS(next, no);
		}
		return no.get_result();
	}

	template<typename T, typename P>
	vector<size_t> top_sort (Graph<T, P>& g)
	{
		if (is_cyclic(g))
			return {};
		TopSortAlg<T, P> ts(g);
		int next = 0;
		g.DFS(next, ts);
		while ((next = ts.get_next()) != -1) {
			g.DFS(next, ts);
		}
		return ts.get_result();
	}

	template <typename T, typename P>
	Graph<T, P> mst(Graph<T, P>& g) {

	}

	

	




}
