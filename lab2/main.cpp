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

	//fillDataFile("DATA.csv");
	//printTraversals();

	AVL::Node* root = new AVL::Node(25);
	root = AVL::insert(root, 1);
	root = AVL::insert(root, 3);
	root = AVL::insert(root, 8);
	root = AVL::insert(root, 0);
	root = AVL::insert(root, 13);
	root = AVL::insert(root, 40);


	//													3 
	//						1	h = 2												  13 h = 3
	//				0	h = 1												8 h = 1				25 h = 2
	//																								40 h = 1
	//															
	//
	//
	//
	//
	//

	inOrder(root);
	printf("left h = %d, right h = %d\n", AVL::height(root->left), AVL::height(root->right));
	printf("root h = %d\n", AVL::height(root));
	printf("PRE ORDER:\n"); 
	preOrder(root);
	printf("\nPOST ORDER:\n");
	postOrder(root);



	// AVL
	AVL::Node* a = new AVL::Node(15);
	a = AVL::insert(a, 30);
	a = AVL::insert(a, 10);
	a = AVL::insert(a, 12);
	a = AVL::insert(a, 11);
	inOrder(a);




	// RBT

	RB::Node* rbt = new RB::Node(15);
	rbt = RB::insert(rbt, 12);
	rbt = RB::insert(rbt, 14);
	rbt = RB::insert(rbt, 40);
	rbt = RB::insert(rbt, 32);
	rbt = RB::insert(rbt, 1);

	std::cout << "\n\n\n\nRBT:\n";
	inOrder(rbt);
	// 1 12 14 15 32 40






	
	return 0;
}