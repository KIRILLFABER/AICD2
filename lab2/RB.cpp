#include "RB.h"
#include <iostream>


using namespace RB;

int Node::cnt = 0;
Node::Node(int key) {
	this->key = key;
	this->left = nullptr;
	this->right = nullptr;
	this->parent = nullptr;
	this->cnt++;
	this->color = RED;
	this->h = 1;
}


Node::~Node() {
	this->cnt--;
}


void RB::fixInsert(Node* node) {
    
}


Node* RB::insert(Node* node, int key){
	if (node == nullptr) return new Node(key);
	if (key < node->key) {
		node->left = insert(node->left, key);
	}
	else {
		node->right = insert(node->right, key);
	}
	fixInsert(node);

}

Node* RB::search(Node* root, int key) {
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




void RB::inOrder(Node* node) {
	if (node == nullptr) return;
	inOrder(node->left);
	std::cout << node->key << " ";
	inOrder(node->right);
}

