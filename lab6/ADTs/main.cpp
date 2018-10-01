#include <iostream>
#include <string>
#include <queue>
#include "sorting\Sorting.h"
#include "ADTs\BinarySearchTree.h"
#include "ADTs\TreeTraversal.h"
#include "ADTs\RandomNumberGenerator.h"

using namespace std;

int getHeight(BinaryNode<int>* node)
{
	if (node == nullptr)
	{
		return -1;
	}

	if (getHeight(node->getRightChild()) > getHeight(node->getLeftChild()))
	{
		return getHeight(node->getRightChild()) + 1;
	}
	else
	{
		return getHeight(node->getLeftChild()) + 1;
	}

}

bool IsAvlhelper(BinaryNode<int>* node)
{
	if(node == nullptr)
	{
		return true;
	}

	if ((getHeight(node->getRightChild()) - getHeight(node->getLeftChild())) > -2 && (getHeight(node->getRightChild()) - getHeight(node->getLeftChild()) < 2))
	{
		if (IsAvlhelper(node->getLeftChild()) && IsAvlhelper(node->getLeftChild()))
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}

bool isAvl(BinarySearchTree<int> *tree)
{
	if (tree == nullptr)
	{
		return true;
	}
	return IsAvlhelper(tree->getRoot());


}

BinaryNode<int>* rotateLeft(BinaryNode<int>* original_root)
{
    return original_root;
}

bool isFull(BinarySearchTree<int> *tree)
{
    return false;
}

void levelhelper(queue<BinaryNode<int>*> tree)
{

}

void levelOrderTraversal(BinarySearchTree<int> *tree)
{
	queue<BinaryNode<int>*> nodes;
}

bool isComplete(BinarySearchTree<int>* tree)
{
    return true;
}

int main(void)
{
    BinarySearchTree<int> tree{};
     
    cout << boolalpha << "Is Full: " << isFull(&tree) << " (expected: TRUE)" << endl;
    cout << boolalpha << "Is Complete: " << isComplete(&tree) << " (expected: TRUE)" << endl;
    cout << boolalpha << "Is AVL: " << isAvl(&tree) << " (expected: TRUE)" << endl;
	cout << boolalpha << "Height: " << getHeight(tree.getRoot()) << " (expected: -1)" << endl;

    tree.addElement(10);
    tree.addElement(5);

    cout << boolalpha << "Is Full: " << isFull(&tree) << " (expected: FALSE)" << endl;
    cout << boolalpha << "Is Complete: " << isComplete(&tree) << " (expected: TRUE)" << endl;
    cout << boolalpha << "Is AVL: " << isAvl(&tree) << " (expected: TRUE)" << endl;
	cout << boolalpha << "Height: " << getHeight(tree.getRoot()) << " (expected: 1)" << endl;

    tree.addElement(15);

    cout << boolalpha << "Is Full: " << isFull(&tree) << " (expected: TRUE)" << endl;
    cout << boolalpha << "Is Complete: " << isComplete(&tree) << " (expected: TRUE)" << endl;
    cout << boolalpha << "Is AVL: " << isAvl(&tree) << " (expected: TRUE)" << endl;
	cout << boolalpha << "Height: " << getHeight(tree.getRoot()) << " (expected: 1)" << endl;

    tree.addElement(12);
    tree.addElement(20);

    cout << boolalpha << "Is Full: " << isFull(&tree) << " (expected: TRUE)" << endl;
    cout << boolalpha << "Is Complete: " << isComplete(&tree) << " (expected: FALSE)" << endl;
    cout << boolalpha << "Is AVL: " << isAvl(&tree) << " (expected: TRUE)" << endl;
	cout << boolalpha << "Height: " << getHeight(tree.getRoot()) << " (expected: 2)" << endl;

    tree.addElement(11);

    cout << boolalpha << "Is Full: " << isFull(&tree) << " (expected: FALSE)" << endl;
    cout << boolalpha << "Is Complete: " << isComplete(&tree) << " (expected: FALSE)" << endl;
    cout << boolalpha << "Is AVL: " << isAvl(&tree) << " (expected: FALSE)" << endl;
	cout << boolalpha << "Height: " << getHeight(tree.getRoot()) << " (expected: 3)" << endl;

    tree.addElement(13);
    tree.addElement(1);
    tree.addElement(7);

    cout << boolalpha << "Is Full: " << isFull(&tree) << " (expected: TRUE)" << endl;
    cout << boolalpha << "Is Complete: " << isComplete(&tree) << " (expected: FALSE)" << endl;
    cout << boolalpha << "Is AVL: " << isAvl(&tree) << " (expected: TRUE)" << endl;
	cout << boolalpha << "Height: " << getHeight(tree.getRoot()) << " (expected: 3)" << endl;
	cout << "Level-order traversal: ";
	levelOrderTraversal(&tree);
	cout << "(expected: 10, 5, 15, 1, 12, 20, 11, 13)" << endl;

    //Note: this breaks the tree structure because our BST isn't informed of the new root.  Must be done last
	cout << endl;
	BinaryNode<int>* rotated = rotateLeft(tree.getRoot());
    RecursivePreOrderTraversal<int> traversal{};
    traversal.traverse(rotated);
	cout << endl;
    
    //rotate again just for fun
    rotated = rotateLeft(rotated);
    traversal.traverse(rotated);
    return 0;
}
