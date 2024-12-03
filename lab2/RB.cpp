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

size_t RB::height(Node* node) {
    return node ? node->h : 0;
}

void RB::fixHeight(Node* node) {
    size_t h_left = height(node->left);
    size_t h_right = height(node->right);
    node->h = std::max(h_left, h_right) + 1;  
}

void RB::rotateLeft(Node* root, Node* node) {
    Node* rightChild = node->right;
    node->right = rightChild->left;
    if (rightChild->left != nullptr) {
        rightChild->left->parent = node;
    }
    rightChild->parent = node->parent;
    if (node->parent == nullptr) {
        root = rightChild;
    }
    else if (node == node->parent->left) {
        node->parent->left = rightChild;
    }
    else {
        node->parent->right = rightChild;
    }
    rightChild->left = node;
    node->parent = rightChild;

    // Обновляем высоты
    fixHeight(node);
    fixHeight(rightChild);
}

void RB::rotateRight(Node* root, Node* node) {
    Node* leftChild = node->left;
    node->left = leftChild->right;
    if (leftChild->right != nullptr) {
        leftChild->right->parent = node;
    }
    leftChild->parent = node->parent;
    if (node->parent == nullptr) {
        root = leftChild;
    }
    else if (node == node->parent->right) {
        node->parent->right = leftChild;
    }
    else {
        node->parent->left = leftChild;
    }
    leftChild->right = node;
    node->parent = leftChild;

    
    fixHeight(node);
    fixHeight(leftChild);
}

void RB::fixInsert(Node* root, Node* node) {
    
    while (node != root && node->parent != nullptr && node->parent->parent != nullptr && node->parent->color == RED) {
        
        if (node->parent == node->parent->parent->left) {
            Node* uncle = node->parent->parent->right;

            if (uncle != nullptr && uncle->color == RED) {
                
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent; 
            }
            else {
                
                if (node == node->parent->right) {
                    node = node->parent;  
                    rotateLeft(root, node);
                }
                
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rotateRight(root, node->parent->parent);
            }
        }
        else {
            Node* uncle = node->parent->parent->left;

            if (uncle != nullptr && uncle->color == RED) {
                
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent; 
            }
            else {
                if (node == node->parent->left) {
                    node = node->parent; 
                    rotateRight(root, node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rotateLeft(root, node->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

Node* RB::insert(Node* root, int key) {
    Node* node = new Node(key);
    Node* parent = nullptr;
    Node* current = root;

    while (current != nullptr) {
        parent = current;
        if (key < current->key) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    node->parent = parent;
    if (parent == nullptr) {
        root = node;
    }
    else if (key < parent->key) {
        parent->left = node;
    }
    else {
        parent->right = node;
    }

    fixInsert(root, node);
    return root;
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

Node* RB::minimum(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

void RB::fixDelete(Node* root, Node* node) {
    while (node != root && node->color == BLACK) {
        if (node == node->parent->left) {
            Node* sibling = node->parent->right;
            if (sibling->color == RED) {
                sibling->color = BLACK;
                node->parent->color = RED;
                rotateLeft(root, node->parent);
                sibling = node->parent->right;
            }
            if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
                (sibling->right == nullptr || sibling->right->color == BLACK)) {
                sibling->color = RED;
                node = node->parent;
            }
            else {
                if (sibling->right == nullptr || sibling->right->color == BLACK) {
                    sibling->left->color = BLACK;
                    sibling->color = RED;
                    rotateRight(root, sibling);
                    sibling = node->parent->right;
                }
                sibling->color = node->parent->color;
                node->parent->color = BLACK;
                if (sibling->right != nullptr) {
                    sibling->right->color = BLACK;
                }
                rotateLeft(root, node->parent);
                node = root;
            }
        }
        else {
            Node* sibling = node->parent->left;
            if (sibling->color == RED) {
                sibling->color = BLACK;
                node->parent->color = RED;
                rotateRight(root, node->parent);
                sibling = node->parent->left;
            }
            if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
                (sibling->right == nullptr || sibling->right->color == BLACK)) {
                sibling->color = RED;
                node = node->parent;
            }
            else {
                if (sibling->left == nullptr || sibling->left->color == BLACK) {
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    rotateLeft(root, sibling);
                    sibling = node->parent->left;
                }
                sibling->color = node->parent->color;
                node->parent->color = BLACK;
                if (sibling->left != nullptr) {
                    sibling->left->color = BLACK;
                }
                rotateRight(root, node->parent);
                node = root;
            }
        }
    }
    node->color = BLACK;
}

Node* RB::deleteNode(Node* root, int key) {
    Node* nodeToDelete = search(root, key);
    if (nodeToDelete == nullptr) {
        return root;
    }

    Node* y = nodeToDelete;
    Node* x;
    Node* xParent;
    if (nodeToDelete->left == nullptr || nodeToDelete->right == nullptr) {
        y = nodeToDelete;
    }
    else {
        y = minimum(nodeToDelete->right);
    }

    if (y->left != nullptr) {
        x = y->left;
    }
    else {
        x = y->right;
    }

    if (x != nullptr) {
        x->parent = y->parent;
    }

    if (y->parent == nullptr) {
        root = x;
    }
    else if (y == y->parent->left) {
        y->parent->left = x;
    }
    else {
        y->parent->right = x;
    }

    if (y != nodeToDelete) {
        nodeToDelete->key = y->key;
    }

    if (y->color == BLACK) {
        fixDelete(root, x);
    }

    delete y;
    return root;
}
