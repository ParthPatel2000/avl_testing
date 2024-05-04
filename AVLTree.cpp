#include "AVLTree.h"

AVLTree::AVLTree()
{
    root = nullptr;
}

int AVLTree::height(Node *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return node->height;
}

int AVLTree::getBalanceFactor(Node *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return height(node->left) - height(node->right);
}

AVLTree::Node *AVLTree::rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = 1 + std::max(height(y->left), height(y->right));
    x->height = 1 + std::max(height(x->left), height(x->right));

    return x;
}

AVLTree::Node *AVLTree::leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = 1 + std::max(height(x->left), height(x->right));
    y->height = 1 + std::max(height(y->left), height(y->right));

    return y;
}

AVLTree::Node *AVLTree::insert(Node *node, int data)
{
    if (node == nullptr)
    {
        size++;
        Node *newNode = new Node();
        newNode->data = data;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->height = 1;
        return newNode;
    }

    if (data < node->data)
    {
        node->left = insert(node->left, data);
    }
    else if (data > node->data)
    {
        node->right = insert(node->right, data);
    }
    else
    {
        return node; // Duplicate keys not allowed
    }

    // Update height of this ancestor node
    node->height = 1 + std::max(height(node->left), height(node->right));

    // Get the balance factor of this ancestor node to check whether this node became unbalanced
    int balance = getBalanceFactor(node);

    // Left Left Case
    if (balance > 1 && data < node->left->data)
    {
        return rightRotate(node);
    }

    // Right Right Case
    if (balance < -1 && data > node->right->data)
    {
        return leftRotate(node);
    }

    // Left Right Case
    if (balance > 1 && data > node->left->data)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && data < node->right->data)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}



AVLTree::Node *AVLTree::deleteNode(Node *root, int key)
{
    if (root == nullptr)
    {
        return root;
    }

    if (key < root->data)
    {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->data)
    {
        root->right = deleteNode(root->right, key);
    }
    

    if (root == nullptr)
    {
        return root;
    }

    root->height = 1 + std::max(height(root->left), height(root->right));

    int balance = getBalanceFactor(root);

    if (balance > 1 && getBalanceFactor(root->left) >= 0)
    {
        return rightRotate(root);
    }

    if (balance > 1 && getBalanceFactor(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalanceFactor(root->right) <= 0)
    {
        return leftRotate(root);
    }

    if (balance < -1 && getBalanceFactor(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void AVLTree::inorderTraversal(Node *root)
{

    if (root != nullptr)
    {
        inorderTraversal(root->left);
        result->push_back(root->data);

        inorderTraversal(root->right);
    }
}

void AVLTree::preorderTraversal(Node *root)
{

    if (root != nullptr)
    {
        result->push_back(root->data);

        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

void AVLTree::postorderTraversal(Node *root)
{

    if (root != nullptr)
    {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        result->push_back(root->data);
    }
}

void AVLTree::levelOrderTraversal(Node *root)
{
    // return;

    if (root == nullptr)
    {
        return;
    }

    std::queue<Node *> q;
    q.push(root);

    while (!q.empty())
    {
        Node *temp = q.front();
        result->push_back(temp->data);

        q.pop();

        if (temp->left != nullptr)
        {
            q.push(temp->left);
        }
        if (temp->right != nullptr)
        {
            q.push(temp->right);
        }
    }
    return;
}


AVLTree::Node *AVLTree::findMin(Node *root)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    while (root->left != nullptr)
    {
        root = root->left;
    }
    return root;
}

AVLTree::Node *AVLTree::findMax(Node *root)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    while (root->right != nullptr)
    {
        root = root->right;
    }
    return root;
}

void AVLTree::clear(Node *root)
{
    if (root == nullptr)
    {
        return;
    }
    clear(root->left);
    clear(root->right);
    delete root;
}

int AVLTree::countNodes(Node *root)
{
    if (root == nullptr)
    {
        return 0;
    }
    return 1 + countNodes(root->left) + countNodes(root->right);
}

bool AVLTree::isBalanced(Node *root)
{
    if (root == nullptr)
    {
        return true;
    }
    int balance = getBalanceFactor(root);
    return (balance >= -1 && balance <= 1) && isBalanced(root->left) && isBalanced(root->right);
}

AVLTree::Node *AVLTree::findSuccessor(Node *root, int key)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    Node *successor = nullptr;
    while (root != nullptr)
    {
        if (root->data > key)
        {
            successor = root;
            root = root->left;
        }
        else
        {
            root = root->right;
        }
    }
    return successor;
}

AVLTree::Node *AVLTree::findPredecessor(Node *root, int key)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    Node *predecessor = nullptr;
    while (root != nullptr)
    {
        if (root->data < key)
        {
            predecessor = root;
            root = root->right;
        }
        else
        {
            root = root->left;
        }
    }
    return predecessor;
}

void AVLTree::rangeSearch(Node *root, int k1, int k2)
{
    if (root == nullptr)
    {
        return;
    }
    if (root->data > k1)
    {
        rangeSearch(root->left, k1, k2);
    }
    if (root->data >= k1 && root->data <= k2)
    {
        result->push_back(root->data);
    }
    if (root->data < k2)
    {
        rangeSearch(root->right, k1, k2);
    }
}

AVLTree::Node *AVLTree::updateKey(Node *root, int oldKey, int newKey)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    root->left = updateKey(root->left, oldKey, newKey);
    root->right = updateKey(root->right, oldKey, newKey);
    if (root->data == oldKey)
    {
        root->data = newKey;
    }
    return root;
}


bool AVLTree::breadthFirstSearch(Node *root, int key)
{
    if (root == nullptr)
    {
        return false;
    }

    std::queue<Node *> q;
    q.push(root);

    while (!q.empty())
    {
        Node *current = q.front();
        q.pop();

        if (current->data == key)
        {
            return true;
        }

        if (current->left != nullptr)
        {
            q.push(current->left);
        }

        if (current->right != nullptr)
        {
            q.push(current->right);
        }
    }

    return false;
}

bool AVLTree::depthFirstSearch(Node *root, int key)
{
    if (root == nullptr)
    {
        return false;
    }

    if (root->data == key)
    {
        return true;
    }
    bool leftSearch = depthFirstSearch(root->left, key);
    bool rightSearch = depthFirstSearch(root->right, key);

    return leftSearch || rightSearch;
}

std::size_t AVLTree::getsize()
{
    return size;
}

int AVLTree::getRoot()
{
    return root->data;
}

bool AVLTree::depthFirstSearch(int key)
{
    return depthFirstSearch(root, key);
}

bool AVLTree::breadthFirstSearch(int key)
{
    if (root)
    {
        return breadthFirstSearch(root, key);
    }
    return 0;
}

void AVLTree::insert(int data)
{
    root = insert(root, data);
}

void AVLTree::remove(int data)
{
    if (root)
    {
        root = deleteNode(root, data);
        return;
    }
    return;
}

void AVLTree::inorderTraversal()
{
    return inorderTraversal(root);
}

void AVLTree::preorderTraversal()
{
    return preorderTraversal(root);
}

void AVLTree::postorderTraversal()
{
    return postorderTraversal(root);
}

void AVLTree::levelOrderTraversal()
{
    return levelOrderTraversal(root);
}

int AVLTree::height()
{
    return height(root);
}

int AVLTree::minimum()
{
    Node *minNode = findMin(root);
    return (minNode != nullptr) ? minNode->data : -1;
}

int AVLTree::maximum()
{
    Node *maxNode = findMax(root);
    return (maxNode != nullptr) ? maxNode->data : -1;
}

void AVLTree::clear()
{
    clear(root);
    root = nullptr;
}

int AVLTree::count()
{
    return countNodes(root);
}

bool AVLTree::isBalanced()
{
    return isBalanced(root);
}

int AVLTree::successor(int key)
{
    Node *successorNode = findSuccessor(root, key);
    return (successorNode != nullptr) ? successorNode->data : -1;
}

int AVLTree::predecessor(int key)
{
    Node *predecessorNode = findPredecessor(root, key);
    return (predecessorNode != nullptr) ? predecessorNode->data : -1;
}

void AVLTree::rangeSearch(int k1, int k2)
{
    rangeSearch(root, k1, k2);
}

void AVLTree::updateKey(int oldKey, int newKey)
{
    if (root)
    {
        root = updateKey(root, oldKey, newKey);
        return;
    }
    return;
}


// destructors
AVLTree::~AVLTree()
{
    delete result;
    clear();
}