#include <iostream>
#include "BST.h"
#include "AVL.h"








int main() {

	BST::Node* root = new BST::Node(25);
	BST::insert(root, 10);
	BST::insert(root, 15);
	BST::insert(root, 12);
	BST::insert(root, 1);
	BST::insert(root, 3); 
	BST::insert(root, 300);
	BST::insert(root, 16);
	BST::erase(root,300); 
	BST::erase(root, 3);
	BST::inOrder(root);
	printf("\n\n\nNodes = %d\n", BST::Node::cnt);



	AVL::Node* AVLroot = new AVL::Node(25);
	AVL::insert(AVLroot, 10);
	AVL::insert(AVLroot, 40);
	
	std::cout << AVL::findMin(AVLroot)->key << std::endl;

	AVL::inOrder(AVLroot);



	delete root;


	return 0;
}