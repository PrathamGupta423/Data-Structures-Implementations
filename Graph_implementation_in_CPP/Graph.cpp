#include<iostream>
#include<vector>
#include<limits>
#include <utility>
#include <tuple>
#include <algorithm>

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
class TreeNode{
    private:
        std::vector<std::pair<int , int>> path;
        float cost = 0;
        std::vector<TreeNode*> children;
        int depth = 0;
    
    public:
        TreeNode(std::vector<std::pair<int , int>>path, float cost , std::vector<TreeNode*> children , int depth){
            this->path = path;
            this->cost = cost;
            this->children = children;
            this->depth = depth;
        }
        TreeNode(std::vector<std::pair<int , int>>path, float cost , int depth){
            this->path = path;
            this->cost = cost;
            this->depth = depth;
        }
        TreeNode(std::vector<std::pair<int , int>>path, float cost){
            this->path = path;
            this->cost = cost;
            this->depth = 0;
        }
        void addChild(TreeNode* node){
            children.push_back(node);
        }
        void setChildren(std::vector<TreeNode*> children){
            this->children = children;
        }
        std::vector<TreeNode*> getChildren(){
            return children;
        }
        void printPath(){
            for(int i=0; i<path.size(); i++){
                std::cout << path[i].first << " " << path[i].second << std::endl;
            }
        }
        void setcost(float cost){
            this->cost = cost;
        }
        float getcost(){
            return cost;
        }
        void setpath(std::vector<std::pair<int , int>>path){
            this->path = path;
        }
        std::vector<std::pair<int , int>> getpath(){
            return path;
        }
        ~TreeNode(){
            for (int i = 0; i < children.size(); i++)
            {
                delete children[i];
            }
            std::cout << "TreeNode deleted" << std::endl;
        }
        void printChildren(){
            for(int i=0; i<children.size(); i++){
                children[i]->print();
            }
        }
        void print (){
            std::cout << "---------------------" << std::endl;
            std::cout << "path: " << std::endl;
            printPath();
            std::cout << "cost: " << cost << std::endl;
            std::cout << "children: " << std::endl;
            printChildren();
            std::cout << "---------------------" << std::endl;
        }
        void setDepth(int depth){
            this->depth = depth;
        }
        int getDepth(){
            return depth;
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

// There are multiple ways of implementing a lower bound 
// We will first try to implement for a symmetric TSP --> adj[i][j] = adj[j][i]

float lowerBoundCost(float **adj, int V, std::vector<std::pair<int , int>>path= {}){
    float cost = 0;
    
    // left for visualization
    // std::vector<std::vector<int>> What_was_removed(V, std::vector<int>(V, 0));
    
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
        
        // What_was_removed[i][min_index] = 1;
        // What_was_removed[i][min2_index] = 2;
        // Used_edges.push_back(std::make_pair(i, min2_index));
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

void TSP(float **adj, int V){
    
    std::vector<int> vertexs ;
    for (int i = 0; i < V; i++)
    {
        vertexs.push_back(i);
    }
    
    float upper_bound = std::numeric_limits<float>::infinity();

    std::vector<std::pair<int , int>> currentpath = {};
    TreeNode* root = new TreeNode({}, lowerBoundCost(adj, V) , 0);
    TreeNode* temp;
    std::vector<std::pair<int , int>> temp_path = {};
    for (int i = 1; i < V; i++)
    {   
        temp = new TreeNode({{0,i}}, lowerBoundCost(adj, V, {{0,i}}), {} , 1);
        root->addChild(temp);
    }
    // root->print();
    // In the children of root we find that node with minimum cost and we branch out from there
    
    delete root;
}






TreeNode* Find_Min_cost_in_full_tree(TreeNode* root){
    if((root->getChildren()).size() == 0){
        return root;
    }
    TreeNode* minNode = root;
    float minCost = root->getcost();
    int minDepth = root->getDepth();
    for (int i = 0; i < (root->getChildren()).size(); i++)
    {
        TreeNode* child = (root->getChildren())[i];
        TreeNode* minChild = Find_Min_cost_in_full_tree(child);
        if (minChild->getcost() < minCost || (minChild->getcost() == minCost && minChild->getDepth() < minDepth)){
            minNode = minChild;
            minCost = minChild->getcost();
            minDepth = minChild->getDepth();
        }
    }
    return minNode;
}
bool isin(std::vector<int> vertexs, int node){
    for (int i = 0; i < vertexs.size(); i++)
    {
        if(vertexs[i] == node){
            return true;
        }
    }
    return false;
}
int branchForNode(float **adj, int V, TreeNode* node , std::vector<int>* vertexs) {
    std::vector<std::pair<int , int>> path = node->getpath();
    std::vector<int> visited = {};
    for (int i = 0; i < path.size(); i++)
    {
        visited.push_back(path[i].first);
        visited.push_back(path[i].second);
    }
    int did_anything_happen = 0;
    for (int i = 0; i < V; i++)
    {
        if(!isin(visited, i)){
            std::vector<std::pair<int , int>> temp_path = path;
            temp_path.push_back({path[path.size()-1].second, i});
            TreeNode* temp = new TreeNode(temp_path, lowerBoundCost(adj, V, temp_path), node->getDepth()+1);
            node->addChild(temp);
            did_anything_happen = 1;
        }
    }

    return did_anything_happen;

}

// void TSP(float **adj, int V){
//     std::vector<int> path;
//     float upper_bound = std::numeric_limits<float>::infinity();
//     std::vector<std::vector<std::pair < std::vector<int> ,float>>> level_by_level_lower_bounds = {};
//     std::vector<std::pair < std::vector<int> ,float>> temp_lower_bounds = {};
//     // For sake of generality let us assume that the starting node is 0
//     for (int i = 1; i < V; i++)
//     {
//         // checking in all branches of the tree starting from 0 
//         std::cout << "i: " << i << std::endl;
//         std::vector<std::pair<int , int>>path = {{0,i}};
//         float lower_bound = lowerBoundCost(adj, V, path);
//         std::cout << "lower_bound: " << lower_bound << std::endl;
//         std::vector<int> temp_path = {0,i};
//         temp_lower_bounds.push_back(std::make_pair(temp_path, lower_bound));
//     }
//     level_by_level_lower_bounds.push_back(temp_lower_bounds);
//     temp_lower_bounds.clear();
//     std::cout << "level_by_level_lower_bounds: " << std::endl;
//     printlevel_by_level_lower_bounds(level_by_level_lower_bounds);
// 
//     float min = std::numeric_limits<float>::infinity();
//     int min_index = -1;
//     for (int i = 0; i < level_by_level_lower_bounds[0].size(); i++)
//     {
//         if(level_by_level_lower_bounds[0][i].second < min){
//             min = level_by_level_lower_bounds[0][i].second;
//             min_index = i;
//         }
//     }
//     std::cout << "min: " << min << std::endl;
//     std::cout << "min_index: " << min_index << std::endl;
// 
//     while (true)
//     {
        // 
//     }
    // 
    // 
// 
//     // return path;

// }
// 
// void branchify(float **adj, int V, int curr_pos){
//     std::vector<std::pair<int , int>>path = {{0,i}};
//     float lower_bound = lowerBoundCost(adj, V, path);
//     std::cout << "lower_bound: " << lower_bound << std::endl;
//     temp_lower_bounds.push_back(std::make_pair(i, lower_bound));
    // 
// }

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
    // std::cout <<lowerBoundCost(g->adj, g->V)<<std::endl;
    // std::vector< std::pair <int,int>> path = {{0,2},{0,4}};
    // std::cout <<lowerBoundCost(g->adj, g->V, path)<<std::endl;
    // std::cout << "Path: " << std::endl;
    // printPath(path);

    TSP(g->adj, g->V);


    delete g;
    return 0;
}
