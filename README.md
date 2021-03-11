# The API
## *Creating the graph*

Graph can be created with no parameters:

```cpp
  Graph<std::string, int> g; 
```



..or by initializing it with multiple elements:

```cpp
  Graph<std::string, int> g({"A","B","C","D","E"});
```


## *Adding nodes and edges*

Nodes can be added to the graph using `Graph<T, P>& addNode(T node)` function, or by using `Graph<T, P>& add_node(initializer_list<T> nodes)` function:

```cpp
  g.add_node("P"); //Adds node with value "P" to the graph.
  g.add_node("Q", "R", "S", "T"); //Adds nodes with values "Q", "R", "S", "T" to the graph
```


Edges can be added to the graph using `Graph<T, P>& add_edge(size_t first, size_t second, P connection);` function:

```cpp
  g.add_edge(0,1,1);
```
*first - first node of the connection*, 
*second - second node of the connection*, 
*P - weight of the connection*.

Additionally, `add_node()` and `add_edge()` can be appended to one another:

```cpp
  g.add_node({"A","B","C"}).add_edge(0,1,1).add_edge(1,2,5); //Adds 3 nodes to the graph and connects "A"->"B" and "B"->"C".
```



## *Graph traversal*

Graph can be traversed using `void DFS(size_t start, DFSAlgorithmBase<T,P>& algorithm);` where *algorithm* is an object of a user class that inherits from the `DFSAlgorithmBase` class. More on inhereting algorithms later. Currently only Depth First Search traversal is implemented:

```cpp
  DijkstrasAlgorithm da; //Instance of a class DijsktrasAlgorithm that inherits from DFSAlgorithmBase.
  g.DFS(0, da); //Starts traversal from node 0 using DijkstrasAlgorithm.
```


# Creating Algorithms
## **DFSBaseAlgorithm**

Creating algorithms for Depth First Search traversal can be done by inheriting from DFSBaseAlgorithm class. To show an example, we're going to implement Dijkstra's Algorithm:

```cpp
class DijsktrasAlgorithm : public DFSAlgorithmBase<std::string, int> {
public:
	void start();
	void current_node_do();
	void decide_next(vector<pair<size_t, int>>&);
	void end();
private:
	vector<int> distance_from_start;
	vector<std::string> nodes;
};
```

Implementing user-defined algorithm requires overriding 4 functions, we'll go over them in chronological order:

`void start()`:

Do any necessary prep work before algorithm starts, such as initializing variables your going to need.

```cpp
void DijsktrasAlgorithm::start()
{
	distance_from_start.assign(graph_size(), INT_MAX);
	distance_from_start[start_node()] = 0;
	nodes.assign(graph_size(), "");
}
```

`void current_node_do()`:

When you land on a node during traversal, do necessary stuff so your algorithm works.

```cpp
void DijsktrasAlgorithm::current_node_do()
{
	nodes[current_node.first] = current_node.second.getValue();
	for (auto&& i : current_neighbors)
		if (distance_from_start[i.first] > distance_from_start[current_node.first] + i.second)
			distance_from_start[i.first] = distance_from_start[current_node.first] + i.second;
}
```

`void decide_next(vector<pair<size_t, int>>& vec)`:

Given a vector of possible next nodes, decide which nodes you want visited. Algorithm will visit first node in the vector next. If you want no nodes visited, empty the vector and return from the function. Vector is made out of pairs, first element in pair represents next node, second pair represents the weight of the edge.

```cpp
void DijsktrasAlgorithm::decide_next(vector<pair<size_t, int>>& vec)
{
	return;
}
```
*We don't want to influence anything here, so we just return*

`void end()`:

After the algorithm finishes, do all the necessary work.

```cpp
void DijsktrasAlgorithm::end()
{
	for (size_t i = 0; i < graph_size(); i++)
		cout << nodes.at(i) << ": " << distance_from_start.at(i) << endl;

	cout << "Algorithm time: " << algorithm_time_us() << " us" << endl;
}
```

With a simple main function:

```cpp
int main() {
	Graph<string, int> g({ "A", "B", "C", "D", "E", "F" });
	g.add_edge(0, 1, 1).add_edge(0, 2, 7).add_edge(0, 3, 6).add_edge(1, 3, 4).add_edge(1, 4, 1).add_edge(2, 5, 2).add_edge(3, 2, 3).add_edge(3, 5, 2).add_edge(4, 3, 2).add_edge(4, 5, 1);
	DijsktrasAlgorithm da;
	g.DFS(0, da);

	return 0;
}
```

we get the following output:

```
A: 0
B: 1
C: 7
D: 4
E: 2
F: 3
Algorithm time: 230 us
```
