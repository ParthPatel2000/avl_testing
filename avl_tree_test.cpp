#include <deepstate/DeepState.hpp>
#include "AVLTree.h"

using namespace deepstate;

TEST(AVLTree, InsertionAndTraversal)
{
    AVLTree avlTree;
    const int numValues = DeepState_IntInRange(10, 100);

    // std::cout<<"numValues: "<<numValues<<std::endl;

    // Insert random values into the AVL tree
    for (int i = 0; i < numValues; ++i)
    {
        // randomly generate values
        int value = DeepState_Int();
        // std::cout<<value<<" ";
        avlTree.insert(value);
    }
    // std::cout<<std::endl;

    // Perform inorder traversal and check if the elements are in ascending order
    avlTree.inorderTraversal();
    std::vector<int> inorderResult = *avlTree.result;
    ASSERT(std::is_sorted(inorderResult.begin(), inorderResult.end())) << "Inorder traversal failed";
    avlTree.result->clear();

    // Perform preorder traversal and check if the root is the first element
    avlTree.preorderTraversal();
    std::vector<int> preorderResult = *avlTree.result;
    ASSERT(!preorderResult.empty() && preorderResult[0] == avlTree.getRoot()) << "Preorder traversal failed";
    avlTree.result->clear();

    // Perform postorder traversal and check if the root is the last element
    avlTree.postorderTraversal();
    std::vector<int> postorderResult = *avlTree.result;
    ASSERT(!postorderResult.empty() && postorderResult.back() == avlTree.getRoot()) << "Postorder traversal failed";
    avlTree.result->clear();

    // Perform level order traversal and check if all levels are correctly traversed
    avlTree.levelOrderTraversal();
    std::vector<int> levelOrderResult = *avlTree.result;
    ASSERT(levelOrderResult.size() == avlTree.getsize()) << "Level order traversal failed";
    avlTree.result->clear();

    // delete &avlTree;
}

TEST(AVLTree, Deletion)
{
    // std::cout<<"Testing Deletion"<<std::endl;

    AVLTree avlTree;
    const int numValues = DeepState_IntInRange(10, 100);

    for (int i = 0; i < numValues; ++i)
    {
        int value = DeepState_Int();
        avlTree.insert(value);
    }

    int valueToDelete = DeepState_Int();
    avlTree.remove(valueToDelete);

    avlTree.inorderTraversal();
    std::vector<int> inorderResult = *avlTree.result;
    for (int i = 0; i < inorderResult.size(); i++)
    {
        ASSERT(inorderResult[i] != valueToDelete) << "Deletion failed";
    }

    avlTree.result->clear();


    // delete &avlTree;
}

TEST(AVLTree, HeightAndMinMax)
{
    AVLTree avlTree;
    const int numValues = DeepState_IntInRange(10, 100);

    // Insert random values into the AVL tree
    for (int i = 0; i < numValues; ++i)
    {
        int value = DeepState_Int();
        avlTree.insert(value);
    }

    // Calculate tree height and assert that it's correct
    int treeHeight = avlTree.height();
    ASSERT(treeHeight >= 0) << "Tree height should be non-negative";

    // Calculate minimum value and assert that it's correct
    int minValue = avlTree.minimum();
    avlTree.inorderTraversal();
    std::vector<int> inorderResult = *avlTree.result;
    ASSERT(minValue == *std::min_element(inorderResult.begin(), inorderResult.end()))
        << "Minimum value is incorrect";

    // Calculate maximum value and assert that it's correct
    int maxValue = avlTree.maximum();
    ASSERT(maxValue == *std::max_element(inorderResult.begin(), inorderResult.end()))
        << "Maximum value is incorrect";
    avlTree.result->clear();


    // delete &avlTree;
}

TEST(AVLTree, RangeSearch)
{

    // std::cout<<"Testing Range Search"<<std::endl;

    AVLTree avlTree;
    const int numValues = DeepState_IntInRange(20, 100);
    // std::cout<<"numValues: "<<numValues<<std::endl;
    std::vector<int> inputValues;
    for (int i = 0; i < numValues; ++i)
    {
        int value = DeepState_Int();
        inputValues.push_back(value);
        avlTree.insert(value);
    }

    int rangeStart = DeepState_Int();
    int rangeEnd = DeepState_Int();
    avlTree.rangeSearch(rangeStart, rangeEnd);
    std::vector<int> rangeSearchResult = *avlTree.result;
    for (int i = 0; i < inputValues.size(); i++)
    {
        if (inputValues[i] >= rangeStart && inputValues[i] <= rangeEnd)
        {
            ASSERT(std::find(rangeSearchResult.begin(), rangeSearchResult.end(), inputValues[i]) != rangeSearchResult.end()) << "Range search failed";
        }
    }

    for (auto val : rangeSearchResult)
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    for (auto val : inputValues)
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    avlTree.result->clear();

    // delete &avlTree;
}

TEST(AVLTree, SuccessorAndPredecessor)
{
    AVLTree avlTree;
    const int numValues = DeepState_IntInRange(10, 100);

    // Insert random values into the AVL tree
    for (int i = 0; i < numValues; ++i)
    {
        int value = DeepState_Int();
        avlTree.insert(value);
    }

    // Generate a random key
    int key = DeepState_Int();

    // Find the successor and predecessor for the generated key
    int successor = avlTree.successor(key);
    int predecessor = avlTree.predecessor(key);

    // Assert that the successor and predecessor are correct
    if (avlTree.breadthFirstSearch(key))
    {
        // If the key is in the AVL tree, its successor and predecessor should also be in the tree
        ASSERT(avlTree.breadthFirstSearch(successor)) << "Successor not found in AVL tree";
        ASSERT(avlTree.breadthFirstSearch(predecessor)) << "Predecessor not found in AVL tree";
    }
    else
    {
        // If the key is not in the AVL tree, its successor and predecessor should be -1
        ASSERT(successor == -1) << "Successor should be -1 for a key not in AVL tree";
        ASSERT(predecessor == -1) << "Predecessor should be -1 for a key not in AVL tree";
    }
    LOG(TRACE) << "Successor of " << key << ": " << successor;
    LOG(TRACE) << "Predecessor of " << key << ": " << predecessor;

delete avlTree.result;
delete &avlTree;
}
