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

Graph can be traversed using `void DFS(size_t start, GBaseAlgorithm<T,P>& algorithm);` or `void BFS(size_t start, GBaseAlgorithm<T,P>& algorithm);` where *algorithm* is an object of a user class that inherits from 'GBaseAlgorithm'.

```cpp
  DijkstrasAlgorithm da; //Instance of a class DijsktrasAlgorithm that inherits from GBaseAlgorithm.
  g.DFS(0, da); //Starts traversal from node 0 using DijkstrasAlgorithm.
```


# Creating Algorithms
## **GBaseAlgorithm**

Creating algorithms for Depth First Search traversal can be done by inheriting from GBaseAlgorithm class. To show an example, we're going to implement Dijkstra's Algorithm:

```cpp
class DijsktrasAlgorithm : public GBaseAlgorithm<int, int> {
public:
	void start();
	void current_node_do();
	void decide_next(vector<Graph<int, int>::Edge>&) {};
	void end();
private:
	vector<int> distance_from_start;
	vector<int> nodes;
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
	nodes.assign(graph_size(), -1);
}
```

`void current_node_do()`:

When you land on a node during traversal, do necessary stuff so your algorithm works.

```cpp
void DijsktrasAlgorithm::current_node_do()
{
	nodes[current_node_idx] = *current_node_value_ptr;
	for (auto&& edge : get_neighbors(current_node_idx))
		if (distance_from_start[edge.m_edge_next_] > distance_from_start[current_node_idx] + *edge.m_edge_value_ptr_)
			distance_from_start[edge.m_edge_next_] = distance_from_start[current_node_idx] + *edge.m_edge_value_ptr_;
}
```

`void decide_next(vector<Graph<int, int>::Edge>& vec)`:

Given a vector of possible next nodes, decide which nodes you want visited. Algorithm will visit first node in the vector next. If you want no nodes visited, empty the vector and return from the function. Vector is made out of structure Edge, containing number of the node that's about to be visited (`m_edge_next_`) and pointer to an edge weight (`m_edge_value_ptr_`).

```cpp
void DijsktrasAlgorithm::decide_next(vvector<Graph<int, int>::Edge>& vec)
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
	cout << "Algorithm time: " << (double)algorithm_time_us() / 1e6 << " us" << endl;
}
```

With a simple main function:

```cpp
int main() {
	Graph<int, int> g({ 0,1,2,3,4,5 });
	g.add_edge(0, 1, 1).add_edge(0, 2, 7).add_edge(0, 3, 6).add_edge(1, 3, 4).add_edge(1, 4, 1).add_edge(2, 5, 2).add_edge(3, 2, 3).add_edge(3, 5, 2).add_edge(4, 3, 2).add_edge(4, 5, 1);
	DijsktrasAlgorithm da;
	g.DFS(0, da);

	return 0;
}
```

we get the following output:

```
0: 0
1: 1
2: 7
3: 4
4: 2
5: 3
Algorithm time: 9e-06 us
```

## *API For Algorithms*
`size_t start_node()` - *Returns index of a starting node*

`size_t graph_size()` - *Returns size of the graph*

`size_t current_node_idx;` - *Index of a current node in traversal.*

`T* current_node_value_ptr;` - *Value of a current node in traversal.*

`int get_next() const noexcept` - *Returns next unvisited node in graph.*

`std::vector<typename Graph<T,P>::Edge>& get_neighbors(size_t p_idx)` - *Returns a reference to neighbors of node with index p_idx.*

`bool finished()` - *Returns whether algorithm finished it's job.*

`void finish_algorithm()` - *Sets algorithm to finished.*

`bool is_visited(const size_t idx)` - *Returns whether a node with given index is visited.*



`vector<pair<size_t, P>> current_neighbors;` - *All of the neighbors of the current node. First item is index of the neighbor, second item is the weight of the edge.*

## *Algorithm time*
During the `void end()` function, users can call:

`long long algorithm_time_s()` - *Returns time of the algorithm in seconds*

`long long algorithm_time_ms()` - *Returns time of the algorithm in milliseconds*

`long long algorithm_time_us()` - *Returns time of the algorithm in microseconds*

`long long algorithm_time_ns()` - *Returns time of the algorithm in nanoseconds*

Calling these functions before `void end()` will return 0.

## *Currently implemented Algorithms*
Algorithms are found in `GraphAlgorithms.h` under namespace `galgs`:

*All of these algorithms can be called with additional parameter `start`*

*If the parameter `start` is omitted, it defaults to 0.*

`bool is_cyclic(Graph<T,P>& g)` - *Checks if a given graph is cyclic*

`bool any_of(Graph<T,P>& g, UnaryPredicate p)` - *Checks if any of the nodes in a graph fulfils given unary predicate p*

`bool all_of(Graph<T,P>& g, UnaryPredicate p)` - *Checks if all of the nodes in a graph fulfils given unary predicate p*

`bool none_of(Graph<T,P>& g, UnaryPredicate p)` - *Checks if none of the nodes in a graph fulfils given unary predicate p*

`int find(Graph<T,P>& g, T value)` - *Returns index of a node with a given value or returns -1 if the given value can't be found*

`int find_if(Graph<T,P>& g, UnaryPredicate p)` - *Returns index of a node that fulfils given unary predicate or returns -1 if no such node can be found*

`int find_if_not(Graph<T,P>& g, UnaryPredicate p)` - *Returns index of a node that doesn't fulfil given unary predicate or returns -1 if no such node can be found*

`vector<size_t> top_sort(Graph<T,P>& g)` - *Returns vector of size_t objects of a given graph in topological sort or returns empty vector if graph is cyclic*

# Benchmarks

The next tests are done with a graph containing 174K nodes and 8M edges:

#### Empty DFS Traversal: 0.20s

#### is_cyclic(): 0.07s (Stopped at node #25708 when it found a cycle)

#### all_of(): 0.22s

#### find_if(): 0.23s