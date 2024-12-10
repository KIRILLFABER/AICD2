#pragma once
enum Color { RED, BLACK };
namespace RB {

	class Node {
	public:
		static int cnt;
		int key;
		Node* left;
		Node* right;
		Node* parent;
		Color color;
		size_t h;
		size_t bh;

		Node(int key);
		~Node();


	};



	size_t height(Node* node);

	void fixHeight(Node* node);

	Node* rotateRight(Node* a);

	Node* rotateLeft(Node* a);

	void fixInsert(Node* root, Node* node);

	Node* insert(Node* node, int key);

	Node* search(Node* root, int key);

	Node* minimum(Node* node);

	void fixDelete(Node* root, Node* node);

	Node* deleteNode(Node* root, int key);

	

}

