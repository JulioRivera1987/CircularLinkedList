#include <iostream>
#include <vector>
#include <map>

class Node 
{
    public:
        int data;
        Node* next;
        
        Node(int value) : data(value), next(nullptr) {}
};

class CircularLinkedList 
{
private:
    Node* head;
    Node* tail;

public:
    CircularLinkedList()
    {   
        head=nullptr;
        tail=nullptr; 
    }

    void insert(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
            tail = newNode;
            tail->next = head; // Point to itself to form a circle
        } else {
            tail->next = newNode;
            tail = newNode;
            tail->next = head;
        }
    }

    std::vector<int> listOf()
    {
        std::vector<int> list;
        std::map<int,int> foundValue;
        // list.push_back(1);
        if (!head) 
        {
            std::cout << "List is empty." << std::endl;
            return list;
        }
        Node* temp = head;
        do 
        {
            int value = temp->data;
            if(foundValue.find(value) == foundValue.end())
            {
                foundValue[value] = value;
                printf("Added %d.\n", value);
                list.push_back(temp->data);
            }
            std::cout << temp->data << " -> ";
            temp = temp->next;
        } 
        while (temp != head);
        std::cout << "(back to head)" << std::endl;        
        return list;
    }

    void print() 
    {
        if (!head) 
        {
            std::cout << "List is empty." << std::endl;
            return;
        }
        Node* temp = head;
        do 
        {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        } 
        while (temp != head);
        std::cout << "(back to head)" << std::endl;
    }

    void merge(CircularLinkedList& other) 
    {
        if (!head) 
        {
            head = other.head;
            tail = other.tail;
            return;
        }
        if (!other.head) 
        {
            return;
        }
        tail->next = other.head;
        tail = other.tail;
        tail->next = head;
    }
};

int main() {
//    CircularLinkedList cll1;
    int count = 6;

    std::vector<std::vector<int>> points = {
            {1, 2}, {3, 4}, {5, 6}, {4,6}, {3,6}
    };   

    std::map<int,CircularLinkedList> sets;

    for(int index = 1; index <= count; index++)
    {
        CircularLinkedList newList;
        newList.insert(index);
        sets[index] = newList;
        printf("Single %d.\n", index);
    }

    for( auto currentPoint: points)
    {
        int xValue = currentPoint[0];
        int yValue = currentPoint[1];
        printf("Values: {%d} : {%d} \n",xValue,yValue);

        CircularLinkedList xList = sets[xValue];
        CircularLinkedList yList = sets[yValue];        
        // xList.insert(yValue);
        xList.merge(yList);
        sets[yValue] = xList; 
        sets[xValue] = xList;                    
        xList.print();
    }

    int finalCount = 0;
    for(int index = 1; index <= count; index++)
    {
        if(sets.find(index) != sets.end())
        {
            printf(">>>> Index %d.\n",index);
            finalCount++;
            CircularLinkedList xList = sets[index];
            std::vector<int> thisList = xList.listOf();
            for(auto item: thisList)
            {
                printf("<<< %d.\n", item);
                sets.erase(item);
            }
            xList.print();
        }
    }

    printf("Size %d.\n", finalCount);
    return 0;
}
