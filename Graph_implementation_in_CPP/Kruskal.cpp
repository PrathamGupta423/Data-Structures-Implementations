// Idea is to implement Kruskal's Algorithm to find the minimum spanning tree of a graph using Union-Find Algorithm
// Kruskal's Algorithm is a greedy algorithm that finds a minimum spanning tree for a connected weighted graph
// Union-Find Algorithm is used to detect cycle in a graph and to find the minimum spanning tree of a graph
// Time Complexity of Kruskal's Algorithm is O(ElogE) or O(ElogV), where E is the number of edges and V is the number of vertices
// Space Complexity of Kruskal's Algorithm is O(V), where V is the number of vertices

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Edge{
    public:
        int source;
        int destination;
        int weight;

        Edge(int source, int destination, int weight){
            this->source = source;
            this->destination = destination;
            this->weight = weight;
        }

};

class Graph{
    public:
        int V; // Number of vertices
        int E; // Number of edges
        vector<Edge> edge; // Vector to store edges

        Graph(int V, int E){
            this->V = V;
            this->E = E;
        }

        void addEdge(int source, int destination, int weight){
            Edge e = Edge(source, destination, weight);
            edge.push_back(e);
        }


        void print_graph(){
            for (int i = 0; i < E; i++){
                cout << edge[i].source << " " << edge[i].destination << " " << edge[i].weight << endl;
            }
        }

        // Graph MST(){
        //     Graph* MST = new Graph(V,0);

        //     // Task 1 is getting a list of edge sorted by weight

        //     vector<Edge> sorted_edge = edge_sort(edge);

        // }

        bool compareEdges(const Edge& a, const Edge& b) {
            return a.weight < b.weight;
        }

        vector<Edge>  edge_sort(vector<Edge> edge){
            sort(edge.begin(), edge.end(), compareEdges);
        return edge;
        }
};


int main(){
    int V, E; // Number of vertices and edges in the graph
    cout<<"enter no. of vertex and edge"<<endl;
    cin >>V >> E;

    Graph* graph = new Graph(V, E);

    for (int i = 0; i < E; i++){
        int source, destination, weight;
        cin >> source >> destination >> weight;
        graph->addEdge(source, destination, weight);
    }

    graph->print_graph();

    return 0;
}