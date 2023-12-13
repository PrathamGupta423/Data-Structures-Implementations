#include<iostream>
#include<vector>
#include <limits>

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
    void setData(int data, Node *next, Node *down){
        this->data = data;
        this->next = next;
        this->down = down;
    }
    void append(int data){
        Node *temp = this;
        while(temp->next != NULL){
            temp = temp->next;
        }        
        Node *newNode = new Node(data, NULL, NULL);
        // newNode->setData;
        temp -> next = newNode;
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
    std::vector<Node *> levels;
    int maxLevel;

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



    }
    
    // ~skiplist(){
    //     for (int i = 0; i < maxLevel; i++){
    //         (*(levels[i])).freeSLL();
    //     }
    //     free(this);
    // }

};



// skiplist::~skiplist()
// {
// }



int main(){
    // Node *head = new Node :: Node((1, NULL, NULL));
    Node *head = new Node(1, NULL, NULL);

    
    // (*head).setData(1, NULL, NULL);
    (*head).append(2);
    // (*head).append(3);
    // (*head).append(4);
    // (*head).append(5);
    // (*head).~Node();

    skiplist *sl = new skiplist(5 , head);
    // sl->~skiplist();




    return 0;
}