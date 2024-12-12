#pragma once
enum Color { RED, BLACK };
namespace RB {

	class Node {
	public:
		static int cnt;
		static Node* nil;
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



	Color getColor(Node* node);

	void setColor(Node* node, Color color);

	size_t height(Node* node);

	void fixHeight(Node* node);

	void fixAllHeights(Node* root);

	Node* rotateRight(Node* root, Node* a);

	Node* rotateLeft(Node* root, Node* a);

	Node* fixInsert(Node* root, Node* node);


	Node* insert(Node* node, int key);

	Node* search(Node* root, int key);

	Node* minimum(Node* node);

	void fixDelete(Node* root, Node* node);

	Node* deleteNode(Node* root, int key);

	

}

