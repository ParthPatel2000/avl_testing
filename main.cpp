#include "AVLTree.h"
#include <iostream>

int main()
{
    // Create an AVL tree instance
    AVLTree avlTree;

    // Test insertion
    std::cout << "Inserting values into AVL tree..." << std::endl;
    avlTree.insert(10);
    avlTree.insert(5);
    avlTree.insert(15);
    avlTree.insert(3);
    avlTree.insert(8);
    avlTree.insert(12);
    avlTree.insert(18);

    // Test inorder traversal
    std::cout << "Inorder traversal: ";

    avlTree.inorderTraversal();
    for (int i = 0; i < avlTree.result->size(); i++)
    {
        std::cout << avlTree.result->at(i) << " ";
    }
    std::cout << std::endl;
    std::cout << "size of inorderResult: " << avlTree.result->size() << std::endl;
    std::cout << "size of avlTree: " << avlTree.getsize() << std::endl;
    avlTree.result->clear();
    std::cout << std::endl;

    // Test preorder traversal
    std::cout << "Preorder traversal: ";
    avlTree.preorderTraversal();
    for (int i = 0; i < avlTree.result->size(); i++)
    {
        std::cout << avlTree.result->at(i) << " ";
    }
    avlTree.result->clear();
    std::cout << std::endl;

    // Test postorder traversal
    std::cout << "Postorder traversal: ";
    avlTree.postorderTraversal();
    for (int i = 0; i < avlTree.result->size(); i++)
    {
        std::cout << avlTree.result->at(i) << " ";
    }
    avlTree.result->clear();
    std::cout << std::endl;

    // Test level order traversal
    std::cout << "Level order traversal: ";
    avlTree.levelOrderTraversal();
    for (int i = 0; i < avlTree.result->size(); i++)
    {
        std::cout << avlTree.result->at(i) << " ";
    }
    std::cout << std::endl;
    std::cout << "size of levelOrderResult: " << avlTree.result->size() << std::endl;
    std::cout << "size of avlTree: " << avlTree.getsize() << std::endl;
    avlTree.result->clear();
    std::cout << std::endl;

    // Test height calculation
    std::cout << "Height of the AVL tree: " << avlTree.height() << std::endl;

    // Test minimum value finding
    std::cout << "Minimum value: " << avlTree.minimum() << std::endl;

    // Test maximum value finding
    std::cout << "Maximum value: " << avlTree.maximum() << std::endl;

    // Test range search
    std::cout << "Range search [5, 15]: ";
    avlTree.rangeSearch(5, 15);
    std::cout << std::endl;

    // Test successor finding
    std::cout << "Successor of 8: " << avlTree.successor(8) << std::endl;

    // Test predecessor finding
    std::cout << "Predecessor of 12: " << avlTree.predecessor(12) << std::endl;

    // Test breadth-first search
    int keyBFS = 12;
    std::cout << "Breadth-first search for key " << keyBFS << ": " << (avlTree.breadthFirstSearch(keyBFS) ? "Found" : "Not found") << std::endl;

    // Test depth-first search
    int keyDFS = 15;
    std::cout << "Depth-first search for key " << keyDFS << ": " << (avlTree.depthFirstSearch(keyDFS) ? "Found" : "Not found") << std::endl;

    // Test clearing the AVL tree
    std::cout << "Clearing the AVL tree..." << std::endl;
    avlTree.clear();

    // // Test count nodes after clearing
    // std::cout << "Number of nodes after clearing: " << avlTree.count() << std::endl;

    // // Test isBalanced after clearing
    // std::cout << "Is AVL tree balanced after clearing: " << std::boolalpha << avlTree.isBalanced() << std::endl;

    // Test serialization and deserialization
    // std::cout << "Serializing AVL tree..." << std::endl;
    // std::stringstream serializedTree;
    // avlTree.serialize(serializedTree);
    // std::cout << "Serialized AVL tree: " << serializedTree.str() << std::endl;

    // std::cout << "Deserializing AVL tree..." << std::endl;
    // AVLTree deserializedTree;
    // deserializedTree.deserialize_in(serializedTree);
    // std::cout << "Inorder traversal of deserialized AVL tree: ";
    // deserializedTree.inorderTraversal();
    // std::cout << std::endl;

    return 0;
}
