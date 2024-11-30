#include "BST.h"
#include <iostream>

using namespace BST;

int Node::cnt = 0;
Node::Node(int key) {
	this->key = key;
	this->left = nullptr;
	this->right = nullptr;
	this->cnt++;
}
Node::~Node() {
	this->cnt--;
}

void BST::insert(Node* root, int key) {
	Node* newNode = new Node(key);
	Node* x = root;
	Node* parent = nullptr;
	while (x != nullptr) {
		parent = x;
		if (key < x->key) {
			x = x->left;
		}
		else {
			x = x->right;
		}
	}
	if (key > parent->key) {
		parent->right = newNode;
	}
	else {
		parent->left = newNode;
	}
}

void BST::erase(Node* root, int key) { // не работает при удалении узла где один из детей - лист
	Node* curr = root;
	Node* parent = nullptr;
	while (curr && curr->key != key) {
		parent = curr;
		if (key > curr->key) {
			curr = curr->right;
		}
		else {
			curr = curr->left;
		}
	}
	if (!curr) return;
	// Если узел имеет не больше одного ребенка
	if (curr->left == nullptr) {
		if (parent && parent->left == curr) parent->left = curr->right;
		else if (parent && parent->right == curr) parent->right = curr->right;
		delete curr;
		return;
	}
	if (curr->right == nullptr) {
		if (parent && parent->left == curr) parent->left = curr->left;
		else if (parent && parent->right == curr) parent->right = curr->left;
		delete curr;
		return;
	}
	// Если у узла есть 2 ребенка
	if (curr->left != nullptr && curr->right != nullptr) {
		Node* newCurr = curr->right;
		while (newCurr->left != nullptr) newCurr = newCurr->left;
		curr->key = newCurr->key;
		erase(curr->right, newCurr->key);
		
	
	}

}



void BST::inOrder(Node* node)
{
	if (node == nullptr) return;
	inOrder(node->left);
	std::cout << node->key << " ";
	inOrder(node->right);
}

Node* BST::search(Node* root, int key) {
	Node* curr = root;
	while (curr && key != curr->key) {
		if (key > curr->key) {
			curr = curr->right;
		}
		else if (key < curr->key) {
			curr = curr->left;
		}
		
	}
	return curr;
}
