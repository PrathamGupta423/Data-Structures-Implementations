#include<iostream>
#include<vector>
#include<limits>
#include <utility>
#include <tuple>

// creating graph using adjacency matrix
class Graph{
    private:
    public:
        int V;
        float **adj;
        Graph(int v){
            this->V = v;
            adj = new float*[V];
            for(int i=0; i<V; i++){
                adj[i] = new float[V];
                for(int j=0; j<V; j++){
                    adj[i][j] = std::numeric_limits<float>::infinity();
                }
            }
        }
        void addEdge(int u, int v , float Cost = 1){
            adj[u][v] = Cost;
            adj[v][u] = Cost;
        }
        void addDirectedEdge(int u, int v , float Cost = 1){
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

void printMatrix(const std::vector<std::vector<int>>& matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void printPath(std::vector<std::pair<int , int>>path){
    for(int i=0; i<path.size(); i++){
        std::cout << path[i].first << " " << path[i].second << std::endl;
    }
}
// There are multiple ways of implementing a lower bound 
// We will first try to implement for a symmetric TSP --> adj[i][j] = adj[j][i]
float lowerBoundCost(float **adj, int V, std::vector<std::pair<int , int>>path= {}){
    float cost = 0;
    std::vector<std::vector<int>> What_was_removed(V, std::vector<int>(V, 0));
    
    for (int i = 0; i < V; i++)
    {
        float min = std::numeric_limits<float>::infinity();
        int min_index = -1;
        float min2 = std::numeric_limits<float>::infinity();
        int min2_index = -1;
        for (int j = 0; j < V; j++)
        {
            if (adj[i][j] < min)
            {
                min2 = min;
                min2_index = min_index;
                min = adj[i][j];
                min_index = j;
            }
            else if (adj[i][j] < min2)
            {
                min2 = adj[i][j];
                min2_index = j;
            }
        }
        cost += 0.5*(min+min2);
        What_was_removed[i][min_index] = 1;
        What_was_removed[i][min2_index] = 2;

        // std::cout << "min: " << min << " min2: " << min2 << std::endl;
        // std::cout << "min_index: " << min_index << " min2_index: " << min2_index << std::endl;
        // std::cout << "cost: " << cost << std::endl;            
    }

    printMatrix(What_was_removed, V);

    
    return cost;

}



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
    std::cout <<lowerBoundCost(g->adj, g->V)<<std::endl;
    std::vector< std::pair <int,int>> path = {{0,1},{1,2},{2,3},{3,4},{4,0}};
    std::cout <<lowerBoundCost(g->adj, g->V, path)<<std::endl;
    std::cout << "Path: " << std::endl;
    printPath(path);


    delete g;
    return 0;
}
