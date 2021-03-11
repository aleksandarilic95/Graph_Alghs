# **The API**
## **Creating the graph**

Graph can be created with no parameters:

```cpp
  Graph<std::string, int> g; 
```
*Example of creating an empty graph*

..or by initializing it with multiple elements:

```cpp
  Graph<std::string, int> g({"A","B","C","D","E"});
```
*Example of creating a graph with an initializer list*

## *Adding nodes and edges*

Nodes can be added to the graph using `Graph<T, P>& addNode(T node)` function, or by using `Graph<T, P>& add_node(initializer_list<T> nodes)` function.

```cpp
  g.add_node("P"); //Adds node with value "P" to the graph.
  g.add_node("Q", "R", "S", "T"); //Adds nodes with values "Q", "R", "S", "T" to the graph
```
*Example of adding nodes to the graph*
