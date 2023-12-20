#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib> 
#include <ctime>
#include <bits/stdc++.h>
class Node{
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
    void setDown(Node *down){
        this->down = down;
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
    ~Node(){
    }
    int getindex(int n){
        Node *temp = this;
        int index = 0;
        while (index = n or temp->next != NULL)
        {
            temp = temp->next;
            index++;
        }
        if (index == n){
            return this->data;
        }
        else{
            return -1;
        }
    }
    Node* bottomMost(){
        Node *temp = this;
        while(temp->down != NULL){
            temp = temp->down;
        }
        return temp;
    }
};
class skiplist{
private:
    int maxLevel;
    std::vector<Node *> levels;
public:
    skiplist(int maxLevel , Node *head){
        this->maxLevel = maxLevel;
        Node *newNode = new Node(std::numeric_limits<int>::min(), head, NULL);
        levels.push_back(newNode);
        for (int i = 1; i < maxLevel; i++){
            Node *newNode = new Node(std::numeric_limits<int>::min(), NULL, levels[i-1]);
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
        if (bottomTemp->getNext() == NULL){
            
        }
        bottomTemp = bottomTemp->getNext();
        for (; bottomTemp != NULL; bottomTemp = bottomTemp->getNext()){
            if (rand() % 2 == 0){
                Node *newNode = new Node(bottomTemp->getData(), NULL, bottomTemp);
                temp->setnext(newNode);
                temp = temp->getNext();
            }
        }
    }
    ~skiplist(){
        for (int i = 0; i < maxLevel; i++){
            (levels[i]) -> freeSLL();
        }
        std::cout << "Skiplist is deleted" << std::endl;
    }
    void print(){
        for (int i = 0; i < maxLevel; i++){
            Node *temp = levels[i];
            while(temp != NULL){
                std::cout << temp->getData() << " ";
                temp = temp->getNext();
            }
            std::cout << std::endl;
        }
    }
    Node* search(int key){
        Node *temp = levels[maxLevel-1];
        while(temp->getNext()!= NULL or temp->getDown() != NULL){
            if (temp->getData() == key){
                return temp ->bottomMost();
            }
            else if (temp->getData() < key){
                if (temp->getNext() != NULL){
                    if (temp -> getNext() -> getData() <= key)
                    {
                        temp = temp -> getNext();
                    }
                    else if (temp->getDown() != NULL){
                        temp = temp -> getDown();
                    }
                    else{
                        break;
                    }
                }
                else if (temp->getDown() != NULL){
                    temp = temp -> getDown();
                }
                else{
                    break;
                }
            }    
            else{
                break;
            }
        }
        return NULL;
    }
    void insert(int key){
        std::vector<Node *> path;
        Node *temp = levels[maxLevel-1];
        while (true){
            if (temp->getNext() != NULL){
                if(temp -> getNext() -> getData() < key){
                    temp = temp -> getNext();
                }
                else if (temp -> getNext() -> getData() == key){
                    return;
                }
                else{
                    path.push_back(temp);
                    if(temp -> getDown() != NULL){
                    temp = temp -> getDown();
                    }
                    else{
                        break;
                    }
                }
            }
            else if (temp -> getDown() != NULL){
                path.push_back(temp);
                temp = temp -> getDown();
            }
            else{
                path.push_back(temp);
                break;
            }
        }

        Node *newNode = new Node(key, NULL, NULL);
        Node *prev = NULL;
        std::reverse(path.begin(), path.end());
        for (int i = 0; i < path.size(); i++){
            if (i == 0){
                newNode -> setnext(path[i] -> getNext());
                path[i] -> setnext(newNode);
                prev = newNode;
            }
            else{
                
                if (rand() % 2 == 0)
                {
                    Node *newNode2 = new Node(key, NULL, NULL);
                    newNode2 -> setnext(path[i] -> getNext());
                    path[i] -> setnext(newNode2);
                    newNode2 -> setDown(prev);
                    prev = newNode2;
                }
                else{
                    return;
                }
            }
        
        }
        return;
    }        
};

void searchtest(){
    
    int len = 1000;
    int *num = new int[len];
    for (int i = 0; i < len; i++)
    {
        num[i] = 2*i;
    }
    std::cout << "The skip list contains {0,2,4,...,1998} " << std::endl;
    std::cout << "----------------------------------------------------"<< std::endl;
    Node *head = new Node(0, NULL, NULL);
    Node *newNode;
    for (int i = 1; i < len; i++)
    {
        newNode = new Node(num[i], NULL, NULL);
        (*head).append(newNode);
    }

    free(num);

    
    skiplist *sl = new skiplist(20, head);


    std::cout << "The skip list is " << std::endl;
    sl -> print();
    std::cout << "----------------------------------------------------"<< std::endl;

    std::cout << "Searching for 100" << std::endl;
    Node* b = sl -> search(100);
    if (b == NULL){
        std::cout<<"not found"<<std::endl;
    }
    else{
        std::cout<<"found"<<std::endl;
    }

    delete sl;
    std::cout << "========================================================" << std::endl;
    

}

void inserttest(){
    int len = 49;
    int num[] = {21, 41, 54, 58, 72, 79, 83, 86, 102, 157, 197, 219, 231, 251, 261, 292, 307, 338, 383, 398, 416, 435, 456, 504, 512, 582, 585, 610, 642, 710, 741, 758, 766, 784, 789, 799, 800, 834, 839, 852, 862, 890, 893, 916, 927, 942, 958, 970, 1000};
    Node *head = new Node(0, NULL, NULL);
    Node *newNode;
    for (int i = 1; i < len; i++){
        newNode = new Node(num[i], NULL, NULL);
        (*head).append(newNode);
    }

    skiplist *sl = new skiplist(4, head);
    std::cout << "The skip list is " << std::endl;
    sl -> print();
    std::cout << "----------------------------------------------------"<< std::endl;
    std::cout << "Inserting 43" << std::endl;
    sl -> insert(43);
    sl -> print();
    std::cout << "----------------------------------------------------"<< std::endl;
    std::cout << "Inserting 103" << std::endl;
    sl -> insert(103);
    sl -> print();
    std::cout << "----------------------------------------------------"<< std::endl;
    delete sl;
}

int main(){
    srand(time(NULL));

    searchtest();

    inserttest();
    
    return 0;
}