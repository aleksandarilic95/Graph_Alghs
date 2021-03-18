#pragma once

#include "Graph.h"
#include <algorithm>

#include "IsCyclicTemplate.h"
#include "FindIfTemplate.h"
#include "AllOfTemplate.h"
#include "TopSortTemplate.h"

#include <vector>

using namespace std;

namespace galgs {

	template<typename T, typename P>
	constexpr bool is_cyclic(Graph<T, P>& g)
	{
		IsCyclicAlg<T, P> ica;
		g.DFS(0, ica);
		return ica.get_result();
	}

	template<typename T, typename P>
	constexpr int find(Graph<T, P>& g, T value) 
	{
		FindAlg<T, P> f(value);
		g.DFS(0,f);
		return f.get_result();
	}

	template<typename T, typename P, class UnaryPredicate>
	constexpr int find_if(Graph<T, P>& g, UnaryPredicate p)
	{
		FindIfAlg<T, P, UnaryPredicate> fi(p);
		g.DFS(0, fi);
		return fi.get_result();
	}

	template<typename T, typename P, class UnaryPredicate>
	constexpr int find_if_not(Graph<T, P>& g, UnaryPredicate p)
	{
		FindIfNotAlg<T, P, UnaryPredicate> fin(p);
		g.DFS(0, fin);
		return fin.get_result();
	}

	template<typename T, typename P, class UnaryPredicate>
	constexpr bool all_of(Graph<T, P>& g, UnaryPredicate p)
	{
		AllOfAlg<T, P, UnaryPredicate> ao(p);
		g.DFS(0, ao);
		return ao.get_result();
	}

	template<typename T, typename P, class UnaryPredicate>
	constexpr bool any_of(Graph<T, P>& g, UnaryPredicate p)
	{
		AnyOfAlg<T, P, UnaryPredicate> ao(p);
		g.DFS(0, ao);
		return ao.get_result();
	}

	template<typename T, typename P, class UnaryPredicate>
	constexpr bool none_of(Graph<T, P>& g, UnaryPredicate p)
	{
		NoneOfAlg<T, P, UnaryPredicate> no(p);
		g.DFS(0, no);
		return no.get_result();
	}

	template<typename T, typename P>
	vector<size_t> top_sort (Graph<T, P>& g)
	{
		if (is_cyclic(g))
			return {};
		TopSortAlg<T, P> ts;
		int next = 4;
		g.DFS(next, ts);
		while ((next = ts.get_next()) != -1) {
			g.DFS(next, ts);
		}
		return ts.get_result();
	}

	

	




}