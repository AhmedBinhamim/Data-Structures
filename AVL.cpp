// AVL.cpp
// Implementation of Balanced Binary Search Tree using C++
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
using namespace std;

// Node declaration
struct Node
{
    int height;  // Node height
    string data; // Node data
    Node* left;  // Pointer to Node left child
    Node* right; // Pointer to Node right child
};

// Binary Search Tree class declarations
class AVL
{
    public:
        Node* root; // Pointer to Tree node
        vector<string> emails;  // Stores tree data in inOrder traversal

    // Default constructor for AVL
    AVL()
    {
        root = NULL; // Set node to Null as tree is empty when constructed
    }

    // Default destructor for AVL
    ~AVL()
    {
        delete root;    // Delete tree node from memory
    }

    // Caculate the height from a given node
    int height(Node* node)
    {
        int h;
        // If node has left subtree and right subtree
        if (node->left != NULL && node->right != NULL) 
        {
            if (node->left->height > node->right->height)
                h = node->left->height;
            else
                h = node->right->height;
        } 
        // If node has only left subtree
        else if (node->left != NULL && node->right == NULL)
                h = node->left->height;
        // If node has only right subtree
        else if (node->left == NULL && node->right != NULL)
                h = node->right->height;
        // If node has no subtrees
        else
            h = -1;
        
        return h + 1;
    }

    // Calculate the balance factor of a given node
    int balanceFactor(Node* node) 
    {
        int bf = 0;
        if (node->left != NULL && node->right != NULL)
            bf = node->left->height - node->right->height;
        else if (node->left != NULL && node->right == NULL)
            bf = node->height;
        else if (node->left == NULL && node->right != NULL)
            bf = -node->height;
        
        return bf;
    }

    // Insert new data under the given node
    Node* insert(Node* node, string email)
    {   
        // if tree is empty
        if (node == NULL) {
            node = new Node;
            node->data = email;
            node->left = node->right = NULL;
        }
        else if (email.compare(node->data) < 0) {
            node->left = insert(node->left, email);
        }
        else if (email.compare(node->data) >= 0) {
            node->right = insert(node->right, email);
        }
        
        // Update the tree height
        node->height = height(node);
        
        // Balance the tree
        node = balance(node);
        
        return node;
    }

    // Delete a node under given node
    Node* deleteItem(Node* node, string email)
    {
        if (node == NULL) {
            return node;
        }
        else if (email.compare(node->data) < 0)
            node->left = deleteItem(node->left, email);
        else if (email.compare(node->data) > 0)
            node->right = deleteItem(node->right, email);
        else {
            // if node has no children
            if (node->left == NULL && node->right == NULL) {
                delete node;
                node = NULL;
            }
            // if node has right, left, or both children
            else if (node->left == NULL || node->right == NULL) {
                Node* temp;
                if (node->left != NULL)
                    temp = node->left;
                else
                    temp = node->right;
                delete node;
                node = temp;
            }
            else {
                Node* temp = getSuccessor(node->left);
                node->data = temp->data;
                node->left = deleteItem(node->left, temp->data);
            }
        }

        // Recalculate the height and balance the tree if current node is not the deleted node
        if (node != NULL)
        {
            node->height = height(node);
            node = balance(node);
        }

        return node;
    }

    // Balance the tree by selecting appropriate rotation to perform
    Node* balance(Node* node)
    {
        int bfParent = balanceFactor(node);

        if (bfParent > 1 && (balanceFactor(node->left) >= 0)) {
            node = rightRotation(node);
        }
        else if (bfParent > 1 && (balanceFactor(node->left) == -1)) {
            node = leftRightRotation(node);
        }
        else if (bfParent < -1 && (balanceFactor(node->right) <= 0)) {
            node = leftRotation(node);
        }
        else if (bfParent < -1 && (balanceFactor(node->right) == 1)) {
            node = rightLeftRotation(node);
        }

        return node;
    }

    // Gets the most right node from given parent
    Node* getSuccessor(Node* parent) {
        while (parent->right != NULL)
            parent = parent->right;
        
        return parent;
    }
    
    // Perform single left rotation on a given node
    Node* leftRotation(Node* node) 
    {
        Node* child = node->right;
        Node* grandChild = child->left;
        
        child->left = node;
        node->right = grandChild;

        // Recalculate hieght after performed rotation
        node->height = height(child->left);
        child->height = height(child);
        
        return child;
    }

    // Perform single right rotation on a given node
    Node* rightRotation(Node* node) 
    {
        Node* child = node->left;
        Node* grandChild = child->right;
        
        child->right = node;
        node->left = grandChild;

        // Recalculate hieght after performed rotation
        node->height = height(child->right);
        child->height = height(child);
        
        return child;
    }

    // Perform double left right rotation on a given node
    Node* leftRightRotation(Node* node) 
    {
        node->left = leftRotation(node->left);
        return rightRotation(node);
    }

    // Perform double right left rotation on a given node
    Node* rightLeftRotation(Node* node) 
    {
        node->right = rightRotation(node->right);
        return leftRotation(node);
    }

    // Search for a specific data from given node
    bool search(Node* node, string target)
    {
        if (node == NULL) {
            return false;
        }
        else if (target.compare(node->data) < 0)
            return search(node->left, target);
        else if (target.compare(node->data) > 0)
            return search(node->right, target);
        else {
            return true;
        }
    }

    // Delete the maximum element in the tree
    Node* dequeue(Node* node) {
        string target = getMax(node)->data;
        node = deleteItem(node, target);
        return node;
    }

    // Gets the maximum element in the tree
    Node* getMax(Node* parent) 
    { 
        while (parent->right != NULL)
            parent = parent->right;

        return parent;
    }
    // Displays the first 20 smallest data in the tree
    void inOrder() {
        cout << left << setw(4) << "No." << left << setw(30) << "Data" << endl;
        emails.clear();
        inOrder(this->root);
        for (int i = 0; i < 20; i++)
            cout << left << setw(4) << i+1 << left << setw(30) << emails[i] << endl;
        cout << "Tree size: " << emails.size() << endl << endl;
    }

    // Insert tree data to vector in inOrder manner
    void inOrder(Node* node)
    {
        if (node != NULL) {
            inOrder(node->left);
            emails.push_back(node->data);
            inOrder(node->right);
        }
    }

    // Displays the first 20 smallest data in the tree
    void maxOrder() {
        cout << left << setw(4) << "No." << left << setw(30) << "Data" << endl;
        emails.clear();
        maxOrder(this->root);
        for (int i = 0; i < 20; i++)
            cout << left << setw(4) << i+1 << left << setw(30) << emails[i] << endl;
        cout << "Tree size: " << emails.size() << endl << endl;
    }

    // Insert tree data to vector in inOrder manner
    void maxOrder(Node* node)
    {
        if (node != NULL) {
            maxOrder(node->right);
            emails.push_back(node->data);
            maxOrder(node->left);
        }
    }
};