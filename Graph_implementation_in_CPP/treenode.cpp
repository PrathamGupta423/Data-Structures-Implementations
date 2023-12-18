#include<iostream>
#include<vector>
#include <utility>
#include <tuple>

class TreeNode{
    private:
        std::vector<std::pair<int , int>> path;
        float cost = 0;
        
     public:
        std::vector<TreeNode*> children;

        TreeNode(std::vector<std::pair<int , int>>path, float cost , std::vector<TreeNode*> children){
            this->path = path;
            this->cost = cost;
            this->children = children;

        }
        TreeNode(std::vector<std::pair<int , int>>path, float cost){
            this->path = path;
            this->cost = cost;
        }
        void addChild(TreeNode* node){
            children.push_back(node);
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
            std::cout << "path: " << std::endl;
            printPath();
            std::cout << "cost: " << cost << std::endl;
            std::cout << "children: " << std::endl;
            printChildren();
            std::cout << "---------------------" << std::endl;
        }

};
void printvector(std::vector<std::pair<int , int>>path){
    for(int i=0; i<path.size(); i++){
        std::cout << path[i].first << " " << path[i].second << std::endl;
    }
}
void printnodevector(std::vector<TreeNode*>path){
    for(int i=0; i<path.size(); i++){
        std::cout << path[i]->getcost() << std::endl;
    }
}

int main(){
    std::vector<std::pair<int , int>>path;
    TreeNode* node = new TreeNode(path, 10);
    std::vector<std::pair<int , int>>path2;
    TreeNode* node2 = new TreeNode(path2, 20, {node});
    std::vector<std::pair<int , int>>path3;
    TreeNode* node3 = new TreeNode(path3, 30, {node});
    std::vector<std::pair<int , int>>path4;
    TreeNode* node4 = new TreeNode(path4, 40, {node2});

    printvector(node->getpath());
    printvector(node2->getpath());
    printvector(node3->getpath());
    printvector(node4->getpath());
    printnodevector(node->children);
    printnodevector(node2->children);
    printnodevector(node3->children);
    printnodevector(node4->children);




    // node->print();

}