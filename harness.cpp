#include <deepstate/DeepState.hpp>
#include <vector>
#include <algorithm> // for std::min_element, std::max_element
#include "AVLTree.h"

using namespace deepstate;

using std::cout;
using std::endl;

#define debug 0

#define mininum_int 1
#define maximum_int 10

TEST(AVLTree, ALL)
{
    AVLTree avlTree;
    const int numValues = DeepState_IntInRange(mininum_int, maximum_int);
    std::vector<int> inorderResult, preorderResult, postorderResult, levelOrderResult, inputValues, rangeSearchResult;

    // Insert random values into the AVL tree
    for (int i = 0; i < numValues; ++i)
    {
        int value = DeepState_Int();
        avlTree.insert(value);
        inputValues.push_back(value);
    }

    // Perform inorder traversal and check if the elements are in ascending order
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
    ASSERT(std::is_sorted(inorderResult.begin(), inorderResult.end())) << "Inorder traversal failed";
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

    // TESTING HEIGHT AND MINMAX
    // Calculate tree height and assert that it's correct
    int treeHeight = avlTree.height();
    ASSERT(treeHeight >= 0) << "Tree height should be non-negative";

    // Calculate minimum value and assert that it's correct
    int minValue = avlTree.minimum();
    ASSERT(minValue == *std::min_element(inorderResult.begin(), inorderResult.end()))
        << "Minimum value is incorrect";

    // Calculate maximum value and assert that it's correct
    int maxValue = avlTree.maximum();
    ASSERT(maxValue == *std::max_element(inorderResult.begin(), inorderResult.end()))
        << "Maximum value is incorrect";

    // TESTING RANGE SEARCH
    int rangeStart = DeepState_Int();
    int rangeEnd = DeepState_Int();
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
    int key = DeepState_Int();
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
        ASSERT(key > *std::max_element(inorderResult.begin(), inorderResult.end())) << "Successor is incorrect";
    }
    else
    {
        ASSERT(successor > key) << "Successor is incorrect";
    }

    if (predecessor == -1)
    {
        ASSERT(key < *std::min_element(inorderResult.begin(), inorderResult.end())) << "Predecessor is incorrect";
    }
    else
    {
        ASSERT(predecessor < key) << "Predecessor is incorrect";
    }

    LOG(TRACE) << "Successor of " << key << ": " << successor;
    LOG(TRACE) << "Predecessor of " << key << ": " << predecessor;

    // TESTING DELETION
    int valueToDelete = DeepState_Int();
    avlTree.remove(valueToDelete);

    avlTree.inorderTraversal();
    inorderResult = *avlTree.result;
    for (int i = 0; i < inorderResult.size(); i++)
    {
        ASSERT(inorderResult[i] != valueToDelete) << "Deletion failed";
    }
    avlTree.result->clear();
}
