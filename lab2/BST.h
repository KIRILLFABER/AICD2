#pragma once

namespace BST {
	class Node {
	public:
		static int cnt;
		int key;
		Node* left;
		Node* right;
		Node(int key);
		~Node();
		
	};
	
	void insert(Node* root, int key);

	void erase(Node* root, int key);

	void inOrder(Node* node);

	Node* search(Node* root, int key);
	
}


