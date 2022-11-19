#ifndef NODE_H 
#define NODE_H 

#include <iostream> 
#include <string> 

using namespace std;
class Node {
    friend class BSTree;
    private:
        string data;
        int count;
        Node *left;
        Node *right;
        Node *parent;
    public:
        Node();
        string getString();
        int getCount();
        void setData(const string&);
        void deCount();
        void inCount();
};

#endif