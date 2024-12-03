#include <iostream>
#include "BST.h"
#include "AVL.h"
#include "RB.h"
#include "Data.h"
#include "Traversal.cpp"




template <class T> void printTraversals(T root) {
	std::cout << "DFS IN ORDER:\n";
	inOrder(root);
	std::cout << "\nDFS PRE ORDER:\n";
	preOrder(root);
	std::cout << "\nDFS POST ORDER:\n";
	postOrder(root);
	std::cout << "\nBFS:\n";
	breadth(root);


}

int main() {

	fillDataFile("DATA.csv");
	srand(time(NULL));
	AVL::Node* root = new AVL::Node(25);
	for (int i = 0; i < 20; i++) {
		root = AVL::insert(root, rand() % 50);
	}
	printTraversals(root);


	
	return 0;
}