#include<iostream>
#include<vector>
#include <limits>
#include <cstdlib> 

class Node
{
private:
    int data;
    Node *next;
    Node *down;

public:
    Node(int data, Node *next, Node *down){
        this->data = data;
        this->next = next;
        this->down = down;
    }
    int getData(){
        return this->data;
    }
    Node *getNext(){
        return this->next;
    }
    Node *getDown(){
        return this->down;
    }
    void setnext(Node *next){
        this->next = next;
    }
    void setData(int data, Node *next, Node *down){
        this->data = data;
        this->next = next;
        this->down = down;
    }
    void append(Node *node){
        Node *temp = this;
        while(temp->next != NULL){
            temp = temp->next;
        }        
        // Node *newNode = new Node(data, NULL, NULL);
        // newNode->setData;
        temp -> next = node;
    }
    void appendDown(int data){
        Node *temp = this;
        while(temp->down != NULL){
            temp = temp->down;
        }
        Node *newNode = new Node(data, NULL, NULL);
        temp -> down = newNode;
    }
    void freeSLL(){
        if (this->next == NULL){
            delete this;
            return;
        }
        (*(this->next)).freeSLL();
        delete this;
        return;
    }

};

class skiplist
{
private:
int maxLevel;
    int maxLevel;
    std::vector<Node *> levels;

public:
    skiplist(int maxLevel , Node *head){
        this->maxLevel = maxLevel;
        // this->size = 0;
        Node *newNode = new Node(-1, head, NULL);
        levels.push_back(newNode);
        for (int i = 1; i < maxLevel; i++){
            Node *newNode = new Node(-1, NULL, NULL);
            // Node *newNode = new Node(std::numeric_limits<int>::min(), NULL, NULL);
            levels.push_back(newNode);
        }
        for (int i = 0; i < maxLevel-1; i++)
        {
            skipify(levels[i], levels[i+1]);
        }
        

    }

    void skipify(Node * bottom , Node * top){
        Node *temp = top;
        Node *bottomTemp = bottom;
        bottomTemp = bottomTemp->getNext();
        for (; bottomTemp != NULL; bottomTemp = bottomTemp->getNext()){
            Node *newNode = new Node(bottomTemp->getData(), NULL, bottomTemp);
            temp->setnext(newNode);
            temp = temp->getNext();
        }

        
    }


};



// skiplist::~skiplist()
// {
// }



int main(){
    // Node *head = new Node :: Node((1, NULL, NULL));
    Node *head = new Node(1, NULL, NULL);

    Node *newNode = new Node(2, NULL, NULL);
    (*head).append(newNode);

    Node *newNode = new Node(3, NULL, NULL);
    (*head).append(newNode);

    skiplist *sl = new skiplist(3 , head);
    // sl->~skiplist();




    return 0;
}