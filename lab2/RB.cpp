#include "RB.h"
#include <iostream>


using namespace RB;

int Node::cnt = 0;
Node::Node(int key) {
	this->key = key;
	this->left = nullptr;
	this->right = nullptr;
	this->cnt++;
	//
}


Node::~Node() {
	this->cnt--;
}

