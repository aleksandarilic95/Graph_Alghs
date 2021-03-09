Implementation of templated Graph structure with templated traversal algorithms.

Graph is instantiated with parameters T, P:

        T - primitive type or structure of a Vertice.
        
        P - primitive type or structure of an Edge.
        
```cpp
Graph<int, int> g; //Graph with weighted integer edges where each node contains integer value. 
```

Graph interface:

```cpp
size_t size() //Returns graph size (number of nodes)
int getNode(T node) //Returns number of a node in a graph given the vertice T
void addNode(T node) //Adds a node to the graph given the vertice T
void addEdge(size_t first, size_t second, P connection) //Adds an edge to the graph given the numbers of node it connects and it's connection P
```

Graph traversal:

```cpp
void DFS(size_t start, DFSAlgorithmBase<T,P>& algorithm) //Depth first search traversal of the graph that takes start node and algorithm as parameters
```

For creating algorithms, they need to be inherited from DFSAlgorithmBase class and certain methods need to be implemented:

```cpp
/*4 methods that need to be implemented*/
void start() //Do any necessary work before the algorithm starts 
void currentNodeAction() //What you want to be done whenever algorithm visits a node
pair<int, P> decideNext() //Decide which node out of the available ones you want to be visited next
void end() //Do any necessary work before algorithm ends
```

DFSAlgorithmBase interface:

```cpp
bool isVisited(size_t idx) { return visitedNodes[idx]; } //given the index, check if node was already visited
  
/*Whenever you enter currentNodeAction() or decideNext() you'll be presented with:*/
size_t node_size; //Size of the node
pair<size_t, Node<T>*> currentNode; //Node you are currently on, first parameter in a pair is a number of a node in the graph, second parameter is a pointer to a Node<T> structure
P lastEdge; //The edge used to arrive to the current node
vector<pair<size_t, P>> currentNeighbors; //Neighbors of the current node
```

when you enter end(), you'll be given:

```cpp
chrono::nanoseconds algorithm_time; //Returns duration of the algorithm in nanoseconds
```

Example of Dijsktra's algorithm:

```cpp
class DijsktrasAlgorithm : public DFSAlgorithmBase<int, int> {
public:
	void start();
	void currentNodeAction();
	pair<int, int> decideNext();
	void end();

private:
	vector<int> distanceFromStart;
	vector<int> lastNode;

};

void DijsktrasAlgorithm::start()
{
	for (int i = 0; i < node_size; i++)
		distanceFromStart.push_back(INT_MAX);
	distanceFromStart[start_node] = 0;
	for (int i = 0; i < node_size; i++)
		lastNode.push_back(start_node);
}

void DijsktrasAlgorithm::currentNodeAction()
{
	for (auto&& i : currentNeighbors)
		if (distanceFromStart[i.first] > distanceFromStart[currentNode.first] + i.second) {
			distanceFromStart[i.first] = distanceFromStart[currentNode.first] + i.second;
			lastNode[i.first] = currentNode.first;
		}
}

pair<int, int> DijsktrasAlgorithm::decideNext()
{
	for (auto&& i : currentNeighbors)
		if (!isVisited(i.first))
			return i;

	return make_pair(-1, 0);
}

void DijsktrasAlgorithm::end()
{
	int j = 0;
	for (auto i : distanceFromStart)
		cout << j++ << ": " << i << endl;

	cout << "Algorithm time: " << (double)algorithm_time.count() / 1000000 << " ms" << endl;
	
}

int main() {
	Graph<int, int> g;

	g.addNode(1);
	g.addNode(1);
	g.addNode(1);
	g.addNode(1);
	g.addNode(1);
	g.addNode(1);
	g.addEdge(0, 1, 1);
	g.addEdge(0, 2, 7);
	g.addEdge(0, 3, 6);
	g.addEdge(1, 3, 4);
	g.addEdge(1, 4, 1);
	g.addEdge(2, 5, 2);
	g.addEdge(3, 2, 3);
	g.addEdge(3, 5, 2);
	g.addEdge(4, 3, 2);
	g.addEdge(4, 5, 1);

	DijsktrasAlgorithm da;

	g.DFS(0, da);
	return 0;
}
```


OUTPUT:
```
0: 0
1: 1
2: 7
3: 4
4: 2
5: 3
Algorithm time: 0.2568 ms
```
