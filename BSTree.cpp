#include "BSTree.h"
#include <queue>

// private data functions
// private:
// Node *root;

/* Constructors */
/* Default constructor */
BSTree::BSTree()
{
    root = nullptr;
}

BSTree::~BSTree()
{
    if (root)
        while (root->left)
        {
            delete root->left;
        }
        while (root->right)
        {
            delete root->right;
        }

        delete root;
}

    //cout << "Deleting " << this->getString() << endl; //TAKE OFF


/* Mutators */
/* Insert an item into the binary search tree. 
    Be sure to keep BST properties. 
    When an item is first inserted into the tree the count should be set to 1. 
    When adding a duplicate string (case sensitive), rather than adding another node, 
    the count variable should be incremented 
    */
void BSTree::insert(const string &key)
{
    Node* currNode = new Node();
    currNode->setData(key); 

   if (root == nullptr) {
      root = currNode;
   }
   else if (search(key))
   {
        currNode->inCount();
   }
   else {
      Node* temp = new Node();
      temp = root; 
      
      while (temp != nullptr) {
         if (key < temp->getString()) {
            if (temp->left == nullptr) {
               temp->left = currNode;
               temp = nullptr;
            }
            else {
               temp = temp->left;
            }
         }
         else {
            if (temp->left == nullptr) {
               temp->right = currNode;
               temp = nullptr;
            }
            else {
               temp = temp->right;
            }
         }
      }
   }
}

//check if string already exists 
    //if it does: appearence++
    //if it doesnt: insert it into the tree 
    


/* Remove a specified string from the tree. 
    Be sure to maintain all bianry search tree properties. 
    If removing a node with a count greater than 1, just decrement the count, otherwise, 
    if the count is simply 1, remove the node. 
    You MUST follow the remove algorithm shown in the slides and discussed in class or else 
    your program will not pass the test functions. 
    When removing, 
        if removing a leaf node, simply remove the leaf. Otherwise, 
        if the node to remove has a left child, replace the node to remove with the largest 
        string value that is smaller than the current string to remove 
        (i.e. find the largest value in the left subtree of the node to remove). 
        If the node has no left child, replace the node to remove with the smallest value 
        larger than the current string to remove 
        (i.e. find the smallest value in the right subtree of the node to remove. 
    */
void BSTree::remove(const string &key)
{
   remove(root,key);
}

void BSTree::remove(Node* node,const string &key) {
  
    // If the key to be deleted is 
    // smaller than the root's
    // key, then it lies in left subtree
    if (node == nullptr)
    {
       return;
    }
    else if (key < node->getString())
    {
        //node->left = remove(node->left, key);
        remove(node->left, key);
    }
    else if (key > node->getString())
    {
        //node->right = remove(node->right, key);
        remove(node->right, key);
    }
    else //has 
    {
        //no children
         if (node->getCount() > 1 ) 
        {
            node->deCount();
            cout << node->getString();
        }
        else if (node->left == nullptr && node->right == nullptr)
        {
            delete node;
            node = nullptr;
            cout << node->getString();
        }
        else if (node->left == nullptr) // 1 child
        {
            Node* temp = new Node();
            temp = node;
            node = node->right;
            delete node;
        }
        else if (root->right == nullptr)
        {
            Node* temp = new Node();
            temp = node;
            node = node->left;
            delete temp;
        }
        else
        {
            Node* temp = new Node();
            temp = minValue(node->right);
            string tmpData = temp->getString();
            node->setData(tmpData);
            //node->right = remove(node->right, temp->getString());
            remove(node->right, temp->getString());
            
        }

       cout << node->getString();
    }
}

    /* PREVIOUS CODE 
    if(!search(key)) {
        return nullptr;
    }
    else if (search(key) && node->getCount() > 1 ) {
        node->deCount();
        return nullptr;
    }
    else {
        if (key < root->getString())
            node->left = remove(node->left, key);
    
        // If the key to be deleted is
        // greater than the root's
        // key, then it lies in right subtree
        else if (key > node->getString())
            node->right = remove(node->right, key);
    
        // if key is same as root's key, then This is the node
        // to be deleted
        else {
            Node* temp = new Node();
            // node has no child
            if (node->left== nullptr && node->right== nullptr)
            {
                return nullptr;
            }
            // node with only one child or no child
            else if (node->left == nullptr) {
                temp = root->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                temp = node->left;
                delete node;
                return temp;
            }
    
            // node with two children: Get the inorder successor
            // (smallest in the right subtree)
            //Node* temp = minValueNode(node->right);
    
            // Copy the inorder successor's content to this node
            string min; 
            min = smallest();
            node->setData(min);
    
            // Delete the inorder successor
            node->right = remove(node->right, temp->getString());
        }
        
    }
    return nullptr;
    */


   

/* Accessors */
/* Search for a string in the binary search tree. 
    It should return true if the string is in the tree, and false otherwise. 
    */
bool BSTree::search(const string &key) const
{
    //search(root, key);
    return search(root, key);
}

bool BSTree::search(Node* currNode, const string &key) const
{
    if (currNode != nullptr) {
        if (currNode->data == key){
                return true;
            } else if (currNode->data > key) {
                search(currNode->left, key);
            } else {
                search(currNode->right, key);
            }
            return false;
    }
    
    return false;
    
}

/* Find and return the largest value in the tree. Return an empty string if the tree is empty */
string BSTree::largest() const
{
    string max = "";
     //If the root is null then simply return
    if(root == nullptr){
        return max;
    }
    //Do level order traversal using a single queue
    queue<Node*> q;
    q.push(root);
    
    while(!q.empty())
    {   
        for(int i = 0; i < q.size(); i++)
        {
            Node *temp = q.front();
            q.pop();
             
            //If it is leftmost corner value or rightmost corner value then print it
            if( i == q.size()-1)
               max = temp->getString();
 
            //push the left and right children of the temp node
            if(temp->left)
            {
                q.push(temp->left);
            }
            if(temp->right)
            {
                q.push(temp->right);
            }
        }
    }

    return max;

}

int BSTree::numOfNodes(Node* currNode) const
{
    return 0;
}

/* Find and return the smallest value in the tree. Return an emtpy string if the tree is empty */
string BSTree::smallest() const
{
    string max = "";
     //If the root is null then simply return
    if(root == nullptr){
        return max;
    }
    //Do level order traversal using a single queue
    queue<Node*> q;
    q.push(root);
    
    while(!q.empty())
    {   
        for(int i = 0; i < q.size(); i++)
        {
            Node *temp = q.front();
            q.pop();
             
            //If it is leftmost corner value or rightmost corner value then print it
            if(i == 0)
            {
               max = temp->getString();
            }
 
            //push the left and right children of the temp node
            if(temp->left)
            {
                q.push(temp->left);
            }
            if(temp->right)
            {
                q.push(temp->right);
            }
        }
    }

    return max;
}
Node* BSTree::minValue(Node* currNode) 
{
   if (currNode->left == nullptr) {
        return currNode;
   }
   return minValue(currNode->left);
}

void BSTree::preOrder(Node* currNode) const
{
    if (currNode != nullptr)
    {
        cout << currNode->getString() << "(" << currNode->getCount() << ")" << " ";
        preOrder(currNode->left);
        preOrder(currNode->right);
    }
}



void BSTree::postOrder() const {
    postOrder(root);
}

void BSTree::postOrder(Node* currNode) const
{
    if (currNode != nullptr)
    {
        postOrder(currNode->left);
        postOrder(currNode->right);
        cout << currNode->getString() << "(" << currNode->getCount() << ")" << " ";
    }
}

void BSTree::inOrder() const{
    inOrder(root);
    
}

void BSTree::inOrder(Node* currNode) const 
{
    if(currNode != nullptr){
        inOrder(currNode->left);
        cout << currNode->getString() << " " << currNode->getCount();
        inOrder(currNode->right);   
    }
}