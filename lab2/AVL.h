#pragma once
namespace AVL {
	class Node
	{
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
	int bFactor(Node* node);
	void fixHeight(Node* node);
	Node* rotateRight(Node* a);
	Node* rotateLeft(Node* a);
	Node* balance(Node* node);
	Node* insert(Node* root, int key);
	Node* erase(Node* node, int key);
	Node* findMin(Node* node);
	Node* eraseMin(Node* node);
	Node* search(Node* root, int key);
	void inOrder(Node* node);
}


