#include <iostream>
#include "BST.h"
#include "AVL.h"
#include "RB.h"
#include "Data.h"
#include "Traversal.cpp"

const int MAX_VAL = 70;
const int SIZE = 10;


void printTraversals() {

	srand(time(NULL));
	BST::Node* BSTtree = new BST::Node(rand() % MAX_VAL);
	for (int i = 0; i < SIZE; i++) {
		int val = rand() % MAX_VAL;
		while (BST::search(BSTtree, val)) {
			val = rand() % MAX_VAL;
		}
		BSTtree = BST::insert(BSTtree, val);
	}
	AVL::Node* AVLtree = new AVL::Node(rand() % MAX_VAL);
	for (int i = 0; i < SIZE; i++) {
		int val = rand() % MAX_VAL;
		while (AVL::search(AVLtree, val)) {
			val = rand() % MAX_VAL;
		}
		AVLtree = AVL::insert(AVLtree, val);
	}
	RB::Node* RBtree = new RB::Node(rand() % MAX_VAL);
	for (int i = 0; i < SIZE; i++) {
		int val = rand() % MAX_VAL;
		while (RB::search(RBtree, val)) {
			val = rand() % MAX_VAL;
		}
		RBtree = RB::insert(RBtree, val);
		
	}
	



	std::cout << "Binary search tree:\n";
	std::cout << "DFS IN ORDER:\n";
	inOrder(BSTtree);
	std::cout << "\nDFS PRE ORDER:\n";
	preOrder(BSTtree);
	std::cout << "\nDFS POST ORDER:\n";
	postOrder(BSTtree);
	std::cout << "\nBFS:\n";
	breadth(BSTtree);
	std::cout << "\n==========================\nAVL tree:\n";
	std::cout << "DFS IN ORDER:\n";
	inOrder(AVLtree);
	std::cout << "\nDFS PRE ORDER:\n";
	preOrder(AVLtree);
	std::cout << "\nDFS POST ORDER:\n";
	postOrder(AVLtree);
	std::cout << "\nBFS:\n";
	breadth(AVLtree);
	std::cout << "\n==========================\nRed Black tree:\n";
	std::cout << "DFS IN ORDER:\n";
	inOrder(RBtree);
	std::cout << "\nDFS PRE ORDER:\n";
	preOrder(RBtree);
	std::cout << "\nDFS POST ORDER:\n";
	postOrder(RBtree);
	std::cout << "\nBFS:\n";
	breadth(RBtree);


}

int main() {

	fillDataFile("DATA.csv");
	printTraversals();


	
	return 0;
}