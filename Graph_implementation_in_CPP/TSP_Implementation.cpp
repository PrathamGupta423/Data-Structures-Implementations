#include<iostream>
#include<vector>
#include<limits>
#include <utility>
#include <tuple>
#include <algorithm>

// creating a graph with adjacency matrix
class Graph
{
private:
    int V;
    float **adj;
public:
    Graph(int v);
    ~Graph();
    void addEdge(int u, int v, float w){
        adj[u][v] = w;
        adj[v][u] = w;
    }
    void printGraph(){
        for(int i=0; i<V; i++){
            for(int j=0; j<V; j++){
                std::cout << adj[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
    void addDirectedEdge(int u, int v , float Cost = 1){
        adj[u][v] = Cost;
    }
    int getV(){
        return V;
    }
    float** getAdj(){
        return adj;
    }
};
Graph::Graph(int v){
    this->V = v;
    adj = new float*[V];
    for(int i=0; i<V; i++){
        adj[i] = new float[V];
        for(int j=0; j<V; j++){
            adj[i][j] = std::numeric_limits<float>::infinity();
        }
    }
}
Graph::~Graph(){
    for(int i=0; i<V; i++){
        delete [] adj[i];
    }
    delete [] adj;
    std::cout << "Graph deleted" << std::endl;
}

class Path
{
private:
    std::vector<int> path;
    float cost;
public:
    Path(std::vector<int> p, float c){
        path = p;
        cost = c;
    }
    ~Path();
    void printPath(){
        for(int i=0; i<path.size(); i++){
            std::cout << path[i] << " ";
        }
        std::cout << std::endl;
    }
    float getCost(){
        return cost;
    }
    std::vector<int> getPath(){
        return path;
    }
};
// class WorkingPath{
//     private:
//         std::vector<int> path;
//         float lowerBoundCost;
//     public:
//         WorkingPath(std::vector<int> p, float c){
//             path = p;
//             cost = c;
//         }
//         ~WorkingPath();
//         void printPath(){
//             for(int i=0; i<path.size(); i++){
//                 std::cout << path[i] << " ";
//             }
//             std::cout << std::endl;
//         }
//         float getCost(){
//             return cost;
//         }
//         std::vector<int> getPath(){
//             return path;
//         }
// };


void printpath(std::vector<std::pair<int , int>>path){
    for (int i = 0; i < path.size(); i++)
    {
        std::cout << path[i].first << " " << path[i].second << std::endl;
    }
    
}
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
void printUsedEges(std::vector<std::pair< std::pair<int, int> , std::pair<int, int>>> Used_edges){
    for(int i=0; i<Used_edges.size(); i++){
        std::cout << Used_edges[i].first.first << " " << Used_edges[i].first.second << " " << Used_edges[i].second.first << " " << Used_edges[i].second.second << std::endl;
    }
}
void printlevel_by_level_lower_bounds(std::vector<std::vector<std::pair < std::vector<int> ,float>>> level_by_level_lower_bounds){
    for(int i=0; i<level_by_level_lower_bounds.size(); i++){
        for(int j=0; j<level_by_level_lower_bounds[i].size(); j++){
            std::cout << "path: ";
            for(int k=0; k<level_by_level_lower_bounds[i][j].first.size(); k++){
                std::cout << level_by_level_lower_bounds[i][j].first[k] << " ";
            }
            std::cout << "cost: " << level_by_level_lower_bounds[i][j].second << std::endl;
        }
    }
    
}


float lowerBoundCost(float **adj, int V, std::vector<std::pair<int , int>>path= {}){
    float cost = 0;
    
    // left for visualization
    std::vector<std::vector<int>> What_was_removed(V, std::vector<int>(V, 0));
    
    std::vector<std::pair< std::pair<int, int> , std::pair<int, int>>> Used_edges;

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
        Used_edges.push_back(std::make_pair(std::make_pair(i, min_index),std::make_pair(i, min2_index)));
        
        What_was_removed[i][min_index] = 1;
        What_was_removed[i][min2_index] = 2;
        // // Used_edges.push_back(std::make_pair(i, min2_index));
        // std::cout << "min: " << min << " min2: " << min2 << std::endl;
        // std::cout << "min_index: " << min_index << " min2_index: " << min2_index << std::endl;
        // std::cout << "cost: " << cost << std::endl;            
    }

    // printMatrix(What_was_removed, V);
    // printUsedEges(Used_edges);
    // std::cout << "cost: " << cost << std::endl;

    for (int i = 0; i < path.size(); i++)
    {
        int node = path[i].first;
        int next_node = path[i].second;

        if(Used_edges[node].first.first == node && Used_edges[node].first.second == next_node){
            continue;
        }
        else if(Used_edges[node].second.first == node && Used_edges[node].second.second == next_node){
            continue;
        }
        else{
            cost += 0.5*adj[node][next_node];
            cost -= 0.5*adj[Used_edges[node].second.first][Used_edges[node].second.second];
            // std::cout << "cost: " << cost << std::endl;
            Used_edges[node].second.first = Used_edges[node].first.first;
            Used_edges[node].second.second = Used_edges[node].first.second;
            // std::cout << "change has occured: " << std::endl;
            // printUsedEges(Used_edges);
            Used_edges[node].first.first = node;
            Used_edges[node].first.second = next_node;
            // std::cout << "change has occured: " << std::endl;
            // printUsedEges(Used_edges);
        }
    }
    // std::cout << "cost: " << cost << std::endl;
    return cost;
}

std::vector< std::pair <int,int>> generic_path_to_pair_points(std::vector<int> path){
    std::vector< std::pair <int,int>> pair_points;
    for (int i = 0; i < path.size()-1; i++)
    {
        pair_points.push_back(std::make_pair(path[i], path[i+1]));
    }
    return pair_points;
}

float pathCost(float **adj, int V, std::vector<std::pair<int , int>>path){
    float cost = 0;
    for (int i = 0; i < path.size(); i++)
    {
        cost += adj[path[i].first][path[i].second];
    }
    // also adding the return 
    cost += adj[path[path.size()-1].second][path[0].first];
    return cost;
}


void TSPRecursion(int V, float **adj, float Lower_Bound, int level, std::vector<int> current_path , std::vector<int> *best_path, float *best_cost, std::vector<bool> visited){
    if(level == V){
        if(adj[current_path[level-1]][current_path[0]] != std::numeric_limits<float>::infinity()){
            float current_cost = pathCost(adj, V, generic_path_to_pair_points(current_path));
            if(current_cost < *best_cost){
                *best_cost = current_cost;
                *best_path = current_path;
            }
        }
        return;
    }
    std::vector<int> current_path_copy ;
    for(int i=0; i<V; i++){
        if(adj[current_path[level-1]][i] != std::numeric_limits<float>::infinity() && !visited[i]){
            
            current_path_copy = current_path;
            current_path_copy.push_back(i);
            float lower_bound = lowerBoundCost(adj, V, generic_path_to_pair_points(current_path_copy));

            if(lower_bound < *best_cost){
                current_path.push_back(i);
                visited[i] = true;
                TSPRecursion(V ,adj, Lower_Bound, level+1, current_path , best_path, best_cost, visited);
                current_path.pop_back();
                visited[i] = false;
            }
        }
    }
}


Path *TSP(float **adj, int V){  

    std::vector<int> current_path;
    std::vector<int> best_path;
    float best_cost = std::numeric_limits<float>::infinity();
    float Lower_Bound = 0;
    std::vector<bool> visited(V, false);
    visited[0] = true;
    current_path.push_back(0);

    std::vector<std::pair<int, int>> pair_points = generic_path_to_pair_points(current_path);
    Lower_Bound= lowerBoundCost(adj, V, pair_points);
    std::cout << "Lower_Bound: " << Lower_Bound << std::endl;
    std::cout << "best_cost: " << best_cost << std::endl;

    TSPRecursion(V ,adj, Lower_Bound, 1, current_path , &best_path, &best_cost, visited);

    return new Path(best_path, best_cost);

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
    std::cout <<lowerBoundCost(g->getAdj(), g->getV())<<std::endl;
    auto path = generic_path_to_pair_points({2,0,4});
    printpath(path);
    g -> printGraph();  
    std::cout <<lowerBoundCost(g->getAdj(), g->getV(), path)<<std::endl;
    path = {{2,0},{0,4}};
    g -> printGraph();  
    std::cout <<lowerBoundCost(g->getAdj(), g->getV(), path)<<std::endl;

    Path *p = TSP(g->getAdj(), g->getV());
    p->printPath();
    std::cout << p->getCost() << std::endl;
    

    delete g;
    return 0;
}