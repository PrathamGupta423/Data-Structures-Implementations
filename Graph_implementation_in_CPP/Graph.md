# What are Graphs?
- Graphs are a non-linear data structure that can be looked at as a collection of vertices (or nodes) potentially connected by line segments named edges.
- Edges may be one-way or two-way. If the edges in a graph are all one-way, then the graph is a directed graph, or a digraph. If the edges in a graph are two-way, it is called an undirected graph.    
- Edges may be weighted to show that there is a cost to go from one vertex to another.


# Graph Representation
- There are two common ways to represent a graph, one is using an adjacency list and the other is an adjacency matrix.
- There are other ways also like an edge list, incidence matrix, and adjacency set. But these are the most common ones.
- The choice of graph representation is situation-specific. It totally depends on the type of operations to be performed and ease of use.
- Adjacency List: An adjacency list is a collection of unordered lists used to represent a finite graph. Each list describes the set of neighbors of a vertex in the graph.
- Adjacency Matrix: An adjacency matrix is a square matrix used to represent a finite graph. The elements of the matrix indicate whether pairs of vertices are adjacent or not in the graph.
- Adjacency Matrix is easier to implement and follow for dense graphs. Adjacency List is easier to implement and follow for sparse graphs.

# Graph Traversal
- Graph traversal means visiting every vertex and edge exactly once in a well-defined order. While using certain graph algorithms, you must ensure that each vertex of the graph is visited exactly once. The order in which the vertices are visited are important and may depend upon the algorithm or question that you are solving.
- During a traversal, it is important that you track which vertices have been visited. The most common way of tracking vertices is to mark them.
- There are two standard methods by which you can traverse graphs: Breadth-First Search (BFS) and Depth-First Search (DFS).
- Breadth-First Search (BFS) algorithm traverses a graph in a breadthward motion and uses a queue to remember to get the next vertex to start a search when a dead end occurs in any iteration.
- Depth-First Search (DFS) algorithm traverses a graph in a depthward motion and uses a stack to remember to get the next vertex to start a search when a dead end occurs in any iteration.

# Graph Algorithms
- Graph algorithms are a set of instructions that traverse (visits nodes of a) graph. These algorithms are used to solve many real-life problems.

# Goals
- [ ] Implement Graph using Adjacency List
- [ ] Implement Graph using Adjacency Matrix
- [ ] Implement BFS
- [ ] Implement DFS
- [ ] Implement Dijkstra's Algorithm
- [ ] Implement Bellman-Ford Algorithm
- [ ] Implement Floyd-Warshall Algorithm
- [ ] Implement TSP
- [ ] Implement Branch and Bound


# References
- [DSA - Graphs](https://gtl.csa.iisc.ac.in/dsa/dsa.html)

