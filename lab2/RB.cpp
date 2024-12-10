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

Node* RB::rotateRight(Node* a) {
    Node* b = a->left;
    a->left = b->right;
    b->right = a;
    fixHeight(a);
    fixHeight(b);
    return b;

}

Node* RB::rotateLeft(Node* a) {
    Node* b = a->right;
    a->right = b->left;
    b->left = a;
    fixHeight(a);
    fixHeight(b);
    return b;
}

void RB::fixInsert(Node* root, Node* node) {

    // Поднимаемся вверх, пока не дойдем до корня
    while (node != root && node->parent != nullptr && node->parent->parent != nullptr && node->parent->color == RED) {
        // Если родитель ноды - левый сын своего родителя
        if (node->parent == node->parent->parent->left) {
            Node* uncle = node->parent->parent->right;
            Node* grand = node->parent->parent;
            // 1) Дядя красный - просто перекрашиваем
            if (uncle != nullptr && uncle->color == RED) {
                
                node->parent->color = BLACK;
                uncle->color = BLACK;
                grand->color = RED;
                node = grand; 
            }
            // 2) Дядя черный
            else {
                // 2.1) нода - левый сын своего родиетля - правый поворот относительно деда


                if (node == node->parent->right) { // 2.2) нода - правый сын своего родителя (сводится к 2.1) - левый поворот относительно родителя
                    rotateLeft(node->parent);
                    node = node->parent;
                }
                
                node->parent->color = BLACK;
                grand->color = RED;
                rotateRight(grand);
            }
        }
        // Если родитель ноды - правый сын своего родителя
        else {
            Node* uncle = node->parent->parent->left;
            Node* grand = node->parent->parent;
            // 1) Дядя красный
            if (uncle != nullptr && uncle->color == RED) {
                
                node->parent->color = BLACK;
                uncle->color = BLACK;
                grand->color = RED;
                node = grand; 
            }
            // 2) Дядя черный
            else {
                // 2.1) нода - левый сын своего родиетля

                if (node == node->parent->left) { // 2.2) нода - правый сын своего родителя (сводится к 2.1)
                    rotateRight(node->parent);
                    node = node->parent;
                }
                node->parent->color = BLACK;
                grand->color = RED;
                rotateLeft(grand);
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
                rotateLeft(node->parent);
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
                    rotateRight(sibling);
                    sibling = node->parent->right;
                }
                sibling->color = node->parent->color;
                node->parent->color = BLACK;
                if (sibling->right != nullptr) {
                    sibling->right->color = BLACK;
                }
                rotateLeft(node->parent);
                node = root;
            }
        }
        else {
            Node* sibling = node->parent->left;
            if (sibling->color == RED) {
                sibling->color = BLACK;
                node->parent->color = RED;
                rotateRight(node->parent);
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
                    rotateLeft(sibling);
                    sibling = node->parent->left;
                }
                sibling->color = node->parent->color;
                node->parent->color = BLACK;
                if (sibling->left != nullptr) {
                    sibling->left->color = BLACK;
                }
                rotateRight(node->parent);
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
