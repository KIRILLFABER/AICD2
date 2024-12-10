#include "AVL.h"
#include <iostream>
using namespace AVL;

int Node::cnt = 0;
Node::Node(int key) {
	this->key = key;
	this->left = nullptr;
	this->right = nullptr;
	this->h = 1;
	this->cnt++;
}
Node::~Node() {
	this->cnt--;
}


size_t AVL::height(Node* node) {
	return node ? node->h : 0;
}
int AVL::bFactor(Node* node) {
	return node ? height(node->right) - height(node->left) : 0;
}

void AVL::fixHeight(Node* node) {
	size_t h_left = height(node->left);
	size_t h_right = height(node->right);
	node->h = (h_left > h_right ? h_left : h_right) + 1;


}

Node* AVL::rotateRight(Node* a) {
	Node* b = a->left;
	a->left = b->right;
	b->right = a;
	fixHeight(a);
	fixHeight(b);
	return b;

}

Node* AVL::rotateLeft(Node* a) {
	Node* b = a->right;
	a->right = b->left;
	b->left = a;
	fixHeight(a);
	fixHeight(b);
	return b;
}

Node* AVL::balance(Node* node) {
	fixHeight(node);
	if (bFactor(node) == 2) { // r > l
		if (bFactor(node->right) < 0) { // l > r
			node->right = rotateRight(node->right);
		}
		return rotateLeft(node);
	}
	if (bFactor(node) == -2) { // r < l
		if (bFactor(node->left) > 0) { // l < r
			node->left = rotateLeft(node->left);
		}
		return rotateRight(node);
	}
	return node;
	
}

Node* AVL::insert(Node* node, int key) {
	if (node == nullptr) return new Node(key);
	if (key < node->key) {
		node->left = insert(node->left, key);
	}
	else {
		node->right = insert(node->right, key);
	}
	return balance(node);


}

Node* AVL::findMin(Node* node) {
	return node->left ? findMin(node->left) : node;
}

Node* AVL::eraseMin(Node* node) 
{
	if (node->left == 0) {
		return node->right;
	}	
	node->left = eraseMin(node->left);
	return balance(node);
}

Node* AVL::erase(Node* node, int key) {
	if (node == nullptr) return nullptr;
	if (key < node->key) {
		node->left = erase(node->left, key);
	}
	else if (key > node->key) {
		node->right = erase(node->right, key);
	}
	else {
		Node* left = node->left;
		Node* right = node->right;
		delete node;
		if (right == nullptr) return left;
		Node* min = findMin(right);
		min->right = eraseMin(right);
		min->left = left;
		return balance(min);
	}
	return balance(node);
}

Node* AVL::search(Node* root, int key) {
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



