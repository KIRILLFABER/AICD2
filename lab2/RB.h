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


	void fixInsert(Node* node);

	Node* insert(Node* node, int key);

	Node* search(Node* root, int key);

	void inOrder(Node* node);

}

