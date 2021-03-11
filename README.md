# **The API**
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
