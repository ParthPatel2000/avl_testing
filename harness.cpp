#include <deepstate/DeepState.hpp>
#include <vector>
#include <algorithm> // for std::min_element, std::max_element
#include "AVLTree.h"

using namespace deepstate;

using std::cout;
using std::endl;

#define debug 1

#define mininum_int 1
#define maximum_int 10

#define int_gen DeepState_Int

TEST(AVLTree, ALL)
{
    AVLTree avlTree;
    const int numValues = DeepState_IntInRange(mininum_int, maximum_int);
    std::vector<int> inorderResult, preorderResult, postorderResult, levelOrderResult, inputValues, rangeSearchResult;

    if (debug)
    {
        cout << "\n*****************************************************************************\n";
        cout << "Number of Inputs: " << numValues << endl;
    }

    // Insert random values into the AVL tree
    for (int i = 0; i < numValues; ++i)
    {
        // Generate Positive numbers only
        int value = int_gen();
        avlTree.insert(value);
        inputValues.push_back(value);
    }

    // Test the number of nodes in the tree
    ASSERT(avlTree.getsize() == numValues) << "Number of nodes in the tree is incorrect";

    // Only check Traversals if the tree has something in it
    if (numValues)
    { // Perform inorder traversal and check if the elements are in ascending order
        avlTree.inorderTraversal();
        inorderResult = *avlTree.result;
        if (debug)
        {
            cout << "The sorted values are: ";
            for (int i = 0; i < inorderResult.size(); i++)
            {
                cout << inorderResult[i] << " ";
            }
            cout << endl;
        }
        ASSERT(!inorderResult.empty() && std::is_sorted(inorderResult.begin(), inorderResult.end())) << "Inorder traversal failed";
        avlTree.result->clear();

        // Perform preorder traversal and check if the root is the first element
        avlTree.preorderTraversal();
        preorderResult = *avlTree.result;
        ASSERT(!preorderResult.empty() && preorderResult[0] == avlTree.getRoot()) << "Preorder traversal failed";
        avlTree.result->clear();

        // Perform postorder traversal and check if the root is the last element
        avlTree.postorderTraversal();
        postorderResult = *avlTree.result;
        ASSERT(!postorderResult.empty() && postorderResult.back() == avlTree.getRoot()) << "Postorder traversal failed";
        avlTree.result->clear();

        // Perform level order traversal and check if all levels are correctly traversed
        avlTree.levelOrderTraversal();
        levelOrderResult = *avlTree.result;
        ASSERT(levelOrderResult.size() == avlTree.getsize()) << "Level order traversal failed";
        avlTree.result->clear();
    }

    // TESTING HEIGHT AND MINMAX
    // Calculate tree height and assert that it's correct
    int treeHeight = avlTree.height();
    ASSERT(treeHeight >= 0) << "Tree height should be non-negative";

    // Calculate minimum value and assert that it's correct
    int minValue = avlTree.minimum();
    if (minValue != -1)
    {
        ASSERT(minValue == *std::min_element(inorderResult.begin(), inorderResult.end()))
            << "Minimum value is incorrect";
    }
    // Calculate maximum value and assert that it's correct
    int maxValue = avlTree.maximum();
    if (maxValue != -1)
    {
        ASSERT(maxValue == *std::max_element(inorderResult.begin(), inorderResult.end()))
            << "Maximum value is incorrect";
    }
    avlTree.result->clear();

    // TESTING RANGE SEARCH
    int rangeStart = int_gen();
    int rangeEnd = int_gen();
    avlTree.rangeSearch(rangeStart, rangeEnd);
    rangeSearchResult = *avlTree.result;

    // debugging
    if (debug)
    {
        cout << "Range Start: " << rangeStart << endl;
        cout << "Range End: " << rangeEnd << endl;

        cout << "Range Search Result: ";
        for (int i = 0; i < rangeSearchResult.size(); i++)
        {
            cout << rangeSearchResult[i] << " ";
        }
        cout << endl;
    }

    // check if the range search result is correct
    for (int i = 0; i < inputValues.size(); i++)
    {
        if (inputValues[i] >= rangeStart && inputValues[i] <= rangeEnd)
        {
            ASSERT(std::find(rangeSearchResult.begin(), rangeSearchResult.end(), inputValues[i]) != rangeSearchResult.end()) << "Range search failed";
        }
    }

    // Testing Successor and Predecessor
    int key = int_gen();
    int successor = avlTree.successor(key);
    int predecessor = avlTree.predecessor(key);
    if (debug)
    {
        cout << "Key: " << key << endl;
        cout << "Successor: " << successor << endl;
        cout << "Predecessor: " << predecessor << endl;

        cout << "is predecessor in tree: " << avlTree.breadthFirstSearch(predecessor) << endl;
        cout << "is successor in tree: " << avlTree.breadthFirstSearch(successor) << endl;
    }

    if (successor == -1)
    {

        if (numValues)
        {
            ASSERT(key > *std::max_element(inorderResult.begin(), inorderResult.end())) << "Successor is incorrect";
        }
    }
    else
    {
        ASSERT(successor > key) << "Successor is incorrect";
    }

    if (predecessor == -1)
    {
        if (numValues)
        {
            ASSERT(key < *std::min_element(inorderResult.begin(), inorderResult.end())) << "Predecessor is incorrect";
        }
    }
    else
    {
        ASSERT(predecessor < key) << "Predecessor is incorrect";
    }

    LOG(TRACE) << "Successor of " << key << ": " << successor;
    LOG(TRACE) << "Predecessor of " << key << ": " << predecessor;

    // Test Update function
    int updateValue = int_gen();
    int valueToUpdate = inputValues[DeepState_IntInRange(0, inputValues.size() - 1)];

    if (numValues)
    {
        avlTree.updateKey(valueToUpdate, updateValue);
        ASSERT(avlTree.breadthFirstSearch(valueToUpdate) == false && avlTree.breadthFirstSearch(updateValue)) << "Update failed";
    }

    if (debug)
    {
        cout << "Value to update: " << valueToUpdate << endl;
    }

    // TESTING DELETION
    int valueToDelete = int_gen();
    avlTree.remove(valueToDelete);
    if (numValues)
    {
        avlTree.inorderTraversal();
        inorderResult = *avlTree.result;
        for (int i = 0; i < inorderResult.size(); i++)
        {
            ASSERT(inorderResult[i] != valueToDelete) << "Deletion failed";
        }
        avlTree.result->clear();
    }
}
