#include "src/Graph/Graph.h"
#include "src/Algorithms/AlgorithmLib/GraphAlgorithms.h"

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <climits>

using namespace std;

class Dijkstras : public GBaseAlgorithm<int,int> {
public:
	Dijkstras(Graph<int,int>& g) : GBaseAlgorithm<int,int>(g) {}
	
	void start() {
		distance.assign(graph_size(), INT_MAX);
		distance[start_node()] = 0; 
		last.assign(graph_size(), 0);
	}
	
	void current_node_do() {
		for(auto&& i : this->get_neighbors(current_node_idx)) {
			if(distance[current_node_idx] + i.second < distance[i.first]) {
				distance[i.first] = distance[current_node_idx] + i.second;
				last[i.first] = current_node_idx;
			}
		}
	}
	
	auto max_distance() {
		return std::distance(distance.begin(), max_element(distance.begin(), distance.end()));
	}

	vector<size_t> order(size_t num) {
		vector<size_t> result;
		while(num!=start_node()) {
			result.push_back(num);
			num = last[num];
		}
		result.push_back(start_node());
		return result;

	}
 	
	void end() {
		cout << (double)algorithm_time_us() / 1e6 << endl;
	}
	
	
private:
	vector<int> distance;
	vector<size_t> last;
	

};





void load_graph(Graph<int, int>& g) {
	ifstream is("edges2.txt");
	while (!is.eof()) {
		string current_line;
		getline(is, current_line);
		size_t del = current_line.find(" ");
		string one = current_line.substr(0, del);
		string two = current_line.substr(del + 1, -1);
		if (one == "3000" && two == "458")
			break;
		g.add_edge(stoi(one) - 1, stoi(two) - 1, 1);
	}

}




int main() {
	Graph<int, int> g;
	for (auto i = 0; i < 3000; i++)
		g.add_node(i);
	load_graph(g);
	// Dijkstras da(g);
	// cout << "Dijkstra: " << endl;
	// g.DFS(0, da);
	// cout << "is_cyclic: " << endl;
	// cout << galgs::is_cyclic(g) << endl;
	// cout << "all_of: " << endl;
	// galgs::all_of(g,[=](int i) {return i == 0;});
	// cout << "any_of: " << endl;
	// galgs::any_of(g,[=](int i) {return i == 0;});
	// cout << "none_of: " << endl;
	// galgs::none_of(g,[=](int i) {return i == 0;});
	// cout << "find: " << endl;
	// galgs::find(g, 1);
	// cout << "find_if: " << endl;
	// galgs::find_if(g, [=](int i) {return i == 1;});
	// cout << "find_if_not: " << endl;
	// galgs::find_if_not(g, [=](int i) {return i == 1;});
	cout << "top_sort: " << endl;
	cout << galgs::top_sort(g).size() << endl;
	return 0;
}
