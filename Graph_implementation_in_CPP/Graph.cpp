#include<iostream>
// using namespace std;

// creating graph using adjacency matrix
class Graph{
    private:
        int V;
        int **adj;

    public:
        Graph(int v){
            this->V = v;
            adj = new int*[V];
            for(int i=0; i<V; i++){
                adj[i] = new int[V];
                for(int j=0; j<V; j++){
                    adj[i][j] = 0;
                }
            }
        }
        void addEdge(int u, int v , int Cost = 1){
            adj[u][v] = Cost;
            adj[v][u] = Cost;
        }
        void addDirectedEdge(int u, int v , int Cost = 1){
            adj[u][v] = Cost;
        }
        void printGraph(){
            for(int i=0; i<V; i++){
                for(int j=0; j<V; j++){
                    std::cout << adj[i][j] << " ";
                }
                std::cout << std::endl;
            }
        }
        ~Graph(){
            for(int i=0; i<V; i++){
                delete [] adj[i];
            }
            delete [] adj;
            std::cout << "Graph deleted" << std::endl;
        }
};


int main(){

    Graph *g = new Graph(5);
    g -> addEdge(0,1,3);
    g -> addEdge(0,2,4);
    g -> addEdge(0,3,2);
    g -> addEdge(0,4,7);
    g -> addEdge(1,2,4);
    g -> addEdge(1,3,6);
    g -> addEdge(1,4,3);
    g -> addEdge(2,3,5);
    g -> addEdge(2,4,8);
    g -> addEdge(3,4,6);
    g -> printGraph();  

    // Goal is to implement TSP using Branch and Bound on this graph
    
    delete &g;

    return 0;
}
