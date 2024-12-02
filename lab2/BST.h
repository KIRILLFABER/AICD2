#pragma once

namespace BST {
	class Node {
	public:
		static int cnt;
		size_t h;
		int key;
		Node* left;
		Node* right;
		Node(int key);
		~Node();

	};

	size_t height(Node* node);
	void fixHeight(Node* node);

	Node* insert(Node* node, int key);

	void erase(Node* root, int key);

	void inOrder(Node* node);

	Node* search(Node* root, int key);

}