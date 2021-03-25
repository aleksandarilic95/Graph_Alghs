#include "src/Graph/Graph.h"
#include "src/Algorithms/AlgorithmLib/GraphAlgorithms.h"

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <climits>

using namespace std;







void load_graph(Graph<int, int>& g) {
	std::ifstream is("edges.txt");
	while (!is.eof()) {
		std::string current_line;
		std::getline(is, current_line);
		size_t del = current_line.find(" ");
		std::string one = current_line.substr(0, del);
		std::string two = current_line.substr(del + 1, -1);
		if (one == "144149" && two == "174147")
			break;
		g.add_edge(stoi(std::move(one)) - 1, stoi(std::move(two)) - 1, 1);
	}

}

class EmptyDFS : public GBaseAlgorithm<int,int> {
public:
	void start() {};
	void end() {
		cout << (double)algorithm_time_ns() / 1e9 << endl;
		cout << count << endl;
	};
	void current_node_do() {count++;};	
private:
	size_t count = 0;
};


int main() {
	Graph<int, int> g;
	g.reserve_nodes(174147);
	for (auto i = 0; i < 174147; i++)
		g.add_node(i);
	load_graph(g);
	cout << "is_cyclic: " << endl;
	cout << galgs::is_cyclic(g) << endl;
	cout << "all_of: " << endl;
	galgs::all_of(g,[=](int i) {return i == 1;});
	cout << "any_of: " << endl;
	galgs::any_of(g,[=](int i) {return i == 0;});
	cout << "none_of: " << endl;
	galgs::none_of(g,[=](int i) {return i == -1;});
	cout << "find: " << endl;
	galgs::find(g, 1);
	cout << "find_if: " << endl;
	galgs::find_if(g, [=](int i) {return i == 1;});	
	cout << "find_if_not: " << endl;
	galgs::find_if_not(g, [=](int i) {return i == 1;});
	cout << "top_sort: " << endl;
	cout << galgs::top_sort(g).size() << endl;
	return 0;
}
