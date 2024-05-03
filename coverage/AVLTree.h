#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#include <string>

class AVLTree
{
public: // For testing purposes
    struct Node
    {
        int data;
        Node *left;
        Node *right;
        int height;
    };
    std::size_t size = 0;

    Node *root = NULL;

    int height(Node *node);
    int getBalanceFactor(Node *node);
    Node *rightRotate(Node *y);
    Node *leftRotate(Node *x);
    Node *insert(Node *node, int data);
    Node *minValueNode(Node *node);
    Node *deleteNode(Node *root, int key);
    void inorderTraversal(Node *root);
    void preorderTraversal(Node *root);
    void postorderTraversal(Node *root);
    void levelOrderTraversal(Node *root);
    bool depthFirstSearch(Node *root, int key);
    bool breadthFirstSearch(Node *root, int key);
    int treeHeight(Node *root);
    Node *findMin(Node *root);
    Node *findMax(Node *root);
    void clear(Node *root);
    int countNodes(Node *root);
    bool isBalanced(Node *root);
    Node *findSuccessor(Node *root, int key);
    Node *findPredecessor(Node *root, int key);
    void rangeSearch(Node *root, int k1, int k2);
    Node *updateKey(Node *root, int oldKey, int newKey);

public:
    std::vector<int> *result = new std::vector<int>();
    AVLTree();
    ~AVLTree();
    void insert(int data);
    void remove(int data);
    int getRoot();
    std::size_t getsize();
    void inorderTraversal();
    void preorderTraversal();
    void postorderTraversal();
    void levelOrderTraversal();
    bool depthFirstSearch(int key);
    bool breadthFirstSearch(int key);
    int height();
    int minimum();
    int maximum();
    void clear();
    int count();
    bool isBalanced();
    int successor(int key);
    int predecessor(int key);
    void rangeSearch(int k1, int k2);
    void updateKey(int oldKey, int newKey);
};

#endif // AVLTREE_H
