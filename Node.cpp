#include "Node.h"

//Node constructor here
Node::Node()
{
    data = " ";
    count = 0; 
    left = nullptr;
    right = nullptr;
    parent = nullptr;

}
string Node::getString() {
    return data;
}

int Node::getCount()
{
    return count;
}

void Node::setData(const string& setKey)
{
    data = setKey;
    inCount();
}

void Node::inCount()
{
    ++count;
}

void Node::deCount()
{
    --count;
}