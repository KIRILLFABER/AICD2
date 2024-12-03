#include "BST.h"
#include <iostream>

using namespace BST;

int Node::cnt = 0;
Node::Node(int key) {
	this->key = key;
	this->left = nullptr;
	this->right = nullptr;
	this->cnt++;
	this->h = 1;
}
Node::~Node() {
	Node::cnt--;
}

void BST::fixHeight(Node* node) {
	size_t h_left = height(node->left);
	size_t h_right = height(node->right);
	node->h = (h_left > h_right ? h_left : h_right) + 1;
}

size_t BST::height(Node* node) {
	return node ? node->h : 0;
}

Node* BST::insert(Node* node, int key) {
	if (node == nullptr) return new Node(key);
	if (key < node->key) {
		node->left = insert(node->left, key);
	}
	else {
		node->right = insert(node->right, key);
	}
	fixHeight(node);
	return node;
}

void BST::erase(Node* root, int key) { // íå ðàáîòàåò ïðè óäàëåíèè óçëà ãäå îäèí èç äåòåé - ëèñò
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
	// Åñëè óçåë èìååò íå áîëüøå îäíîãî ðåáåíêà
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
	// Åñëè ó óçëà åñòü 2 ðåáåíêà
	if (curr->left != nullptr && curr->right != nullptr) {
		Node* newCurr = curr->right;
		while (newCurr->left != nullptr) newCurr = newCurr->left;
		curr->key = newCurr->key;
		erase(curr->right, newCurr->key);


	}

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