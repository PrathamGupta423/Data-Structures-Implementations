#include<iostream>
#include<vector>
#include <limits>
#include <cstdlib> 
#include <ctime>


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
        // std::cout << "Node with data " << this->data << " is deleted" << std::endl;
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
class skiplist
{
private:
    int maxLevel;
    std::vector<Node *> levels;

public:
    skiplist(int maxLevel , Node *head){
        this->maxLevel = maxLevel;
        // this->size = 0;
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
        // std::cout<<"searching"<<temp->getData()<<std::endl;
        // return temp -> getNext();
        while(temp->getNext()!= NULL or temp->getDown() != NULL){
            // std::cout<<"in loop"<<temp->getData()<<std::endl;
            if (temp->getData() == key){
                return temp ->bottomMost();
                // std::cout<<"1st if"<<temp->getData()<<std::endl;
            }
            else if (temp->getData() < key){
                // std::cout<<"in else"<<temp->getData()<<std::endl;
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
    


};
int main(){
    srand(time(NULL));
    int len = 1000;
    int *num = new int[len];
    for (int i = 0; i < len; i++)
    {
        num[i] = i;
    }
    Node *head = new Node(0, NULL, NULL);
    Node *newNode;
    for (int i = 1; i < len; i++)
    {
        newNode = new Node(num[i], NULL, NULL);
        (*head).append(newNode);
    }

    free(num);

    
    skiplist *sl = new skiplist(20, head);
    sl -> print();
    Node* b = sl -> search(101);
    if (b == NULL){
        std::cout<<"not found"<<std::endl;
    }
    else{
        std::cout<<"found"<<std::endl;
    }

    // std::cout<<"searched"<<" "<<b -> getData()<<std::endl;
    // delete b;

    delete sl;


    return 0;
}