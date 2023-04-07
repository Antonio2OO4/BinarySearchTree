#include <iostream>
#include "BinarySearchTree.h"

int main()
{
	BinarySearchTree<int> one;
	one.insert(5);
	one.insert(3);
	one.insert(4);
	one.insert(12);

	one.deleteKey(5);
	one.deleteKey(12);
	one.deleteKey(4);
	one.deleteKey(3);

	return 0;
}