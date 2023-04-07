#include <iostream>
#include "BinarySearchTree.h"

int main()
{
	BinarySearchTree<int> one;
    std::cout << "How many elements the tree: " << one.getCount() << std::endl;

    std::cout << "Adding elements in the tree..." << std::endl;
    one.insert(6);
    one.insert(8);
    one.insert(10);
    one.insert(4);
    one.insert(5);
    one.insert(6);
    one.insert(15);

    one.print(std::cout);

    std::cout << std::endl << "Checking 13 in the tree: " << one.iterativeSearch(13) << std::endl;
    std::cout << "Checking 10 in the tree: " << one.iterativeSearch(10) << std::endl;

    one.deleteKey(6);
    one.deleteKey(8);
    one.deleteKey(15);

    one.print(std::cout);

    std::cout << std::endl << "Tree height: " << one.getHeight() << std::endl;

    one.inorderWalk();
    std::cout << std::endl;
    one.iterativeInorderWalk();
    std::cout << std::endl;
    one.walkByLevels();
    std::cout << std::endl;

    std::cout << "Creating a copy of first tree... " << std::endl;
    BinarySearchTree<int> two;
    two.insert(10);
    two.insert(4);
    two.insert(5);

    std::cout << "First and second tree are similar: " << one.isSimilar(two) << std::endl;
    std::cout << "First and second tree have identical key: " << one.isIdenticalKey(two) << std::endl;

    std::cout << "Adding 9 to the second tree..." << std::endl;
    two.insert(9);

    std::cout << "First and second tree are similar: " << one.isSimilar(two) << std::endl;
    std::cout << "First and second tree have identical key: " << one.isIdenticalKey(two) << std::endl;

	return 0;
}