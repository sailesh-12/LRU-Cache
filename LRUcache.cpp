#include<bits/stdc++.h>
using namespace std;

class LRUcache{
    private :
    struct Node{
        int key;
        int val;
        struct Node *prev;
        struct Node *next;
    }*head=NULL,*tail=NULL;
    map<int,Node*> mpp;
    int capacity;

    public:
    LRUcache(int _capacity){
        capacity=_capacity;
        head=new Node();
        tail=new Node();
        mpp.clear();

        head->key=-1;
        head->val=-1;
        head->prev=NULL;
        head->next=tail;

        tail->key=-1;
        tail->val=-1;
        tail->prev=head;
        tail->next=NULL;
    }

    void insertAfterHead(Node *);
    void deleteNode(Node *);
    int get(int);
    void put(int,int);
};

void LRUcache::insertAfterHead(struct Node *node){
    struct Node *currentAfterhead=head->next;
    head->next=node;
    node->next=currentAfterhead;
    node->prev=head;

    if(currentAfterhead) {currentAfterhead->prev=node;}

}
void LRUcache::deleteNode(struct Node *node)
{
    struct Node *prevNode=node->prev;
    struct Node *nextNode=node->next;

    prevNode->next=nextNode;
    nextNode->prev=prevNode;
}

int LRUcache::get(int key){
    if(!mpp[key]){
        return -1;
    }
    else{
        Node *node=mpp[key];
        deleteNode(node);
        insertAfterHead(node);
        return node->val;
    }
}

void LRUcache::put(int key,int val){
    if(mpp.find(key)!=mpp.end()){
        Node *node=mpp[key];
        node->val=val;
        deleteNode(node);
        insertAfterHead(node);
    }
    else
    {
        if(mpp.size()==capacity){
             mpp.erase(tail -> prev -> key);
             deleteNode(tail -> prev);
        }
        Node *node=new Node();
        node->key=key;
        node->val=val;

        insertAfterHead(node);
        mpp[key]=head->next;
    }
}

int main() {
    LRUcache l(2);
    l.put(1, 10);   // cache: [1]
    l.put(2, 20);   // cache: [2, 1]
    l.get(1);       // access 1, now cache: [1, 2]
    l.put(3, 30);   // capacity full -> evict 2 -> cache: [3, 1]

    cout << l.get(2) << endl; // ❌ should return -1 (evicted)
    cout << l.get(1) << endl; // ✅ should return 10
    cout << l.get(3) << endl; // ✅ should return 30
}
