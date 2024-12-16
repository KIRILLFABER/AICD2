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


Color RB::getColor(Node* node){
    return node ? node->color : BLACK;
}

void RB::setColor(Node* node, Color color) {
    if (node) node->color = color;
}

size_t RB::height(Node* node) {
    return node ? node->h : 0;
}
size_t RB::blackHeight(Node* node) {
    return node ? node->bh : 1;
}

void RB::fixHeight(Node* node) {
    size_t h_left = height(node->left);
    size_t h_right = height(node->right);
    node->h = std::max(h_left, h_right) + 1;  
}



void RB::fixBlackHeight(Node* node) {
    size_t bh_left = blackHeight(node->left);
    size_t bh_right = blackHeight(node->right);
    node->h = std::max(bh_left, bh_right) + 1;
}

void RB::fixAllHeights(Node* node) {
    if (node == nullptr) return;
    fixAllHeights(node->left);
    fixAllHeights(node->right);
    fixHeight(node);
}

Node* RB::rotateRight(Node* root, Node* a) {
    Node* a_parent = a->parent;
    Node* b = a->left;
    Node* b_right_child = b->right;
    a->left = b_right_child;
    if (b_right_child) b_right_child->parent = a;
    if (a->parent && a->parent->left == a) { // Если а - был левым ребенком своего родителя
        a->parent->left = b;
    }
    else if (a->parent && a->parent->right == a) { // Если а - был правым ребенком своего родителя
        a->parent->right = b;
    }
    else { // Если а - был корнем
        root = b;
    }
    b->parent = a->parent;
    a->parent = b;
    b->right = a;
    fixHeight(a);
    fixHeight(b);
    return root;

}

Node* RB::rotateLeft(Node* root, Node* a) {
    Node* a_parent = a->parent;
    Node* b = a->right;
    Node* b_left_child = b->left;
    a->right = b_left_child;
    if (b_left_child) b_left_child->parent = a;
    if (a->parent && a->parent->left == a) { // Если а - был левым ребенком своего родителя
        a->parent->left = b;
    }
    else if (a->parent && a->parent->right == a) { // Если а - был правым ребенком своего родителя
        a->parent->right = b;
    }
    else { // Если а - был корнем
        root = b;
    }
    b->parent = a->parent;
    a->parent = b;
    b->left = a;
    fixHeight(a);
    fixHeight(b);
    return root;
}

Node* RB::fixInsert(Node* root, Node* node) { 

    // Поднимаемся вверх, пока не дойдем до корня
    while (node != root && node->parent != nullptr && node->parent->parent != nullptr && node->parent->color == RED) {
        // Если родитель ноды - левый сын своего родителя
        if (node->parent == node->parent->parent->left) {
            Node* uncle = node->parent->parent->right;
            Node* grand = node->parent->parent;
            // 1) Дядя красный - просто перекрашиваем
            if (getColor(uncle) == RED) {
                setColor(node->parent, BLACK);
                setColor(uncle, BLACK);
                setColor(grand, RED);
                node = grand; 
            }
            // 2) Дядя черный
            else {
                // 2.1) нода - левый сын своего родиетля - правый поворот относительно деда


                if (node == node->parent->right) { // 2.2) нода - правый сын своего родителя (сводится к 2.1) - левый поворот относительно родителя
                    node = node->parent;
                    root = rotateLeft(root, node);
                }
                
                setColor(node->parent, BLACK);
                setColor(grand, RED);
                root = rotateRight(root, grand);
            }
           
        }
        // Если родитель ноды - правый сын своего родителя
        else {
            Node* uncle = node->parent->parent->left;
            Node* grand = node->parent->parent;
            // 1) Дядя красный
            if (getColor(uncle) == RED) {
                
                setColor(node->parent, BLACK);
                setColor(uncle, BLACK);
                setColor(grand, RED);
                node = grand;
            }
            // 2) Дядя черный
            else {
                // 2.1) нода - левый сын своего родиетля

                if (node == node->parent->left) { // 2.2) нода - правый сын своего родителя (сводится к 2.1)
                    node = node->parent;
                    root = rotateRight(root, node);
                    
                }
                setColor(node->parent, BLACK);
                setColor(grand, RED);
                root = rotateLeft(root, grand);
            }
           
        }
    }
    setColor(root, BLACK);
    fixAllHeights(root);
    return root;
}

Node* RB::insert(Node* root, int key) {
    Node* node = new Node(key);
    Node* parent = nullptr;
    Node* curr = root;

    while (curr != nullptr) {
        parent = curr;
        if (key < curr->key) {
            curr = curr->left;
        }
        else {
            curr = curr->right;
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
    fixAllHeights(root);
    root = fixInsert(root, node);

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

void RB::fixErase(Node* root, Node* node) {
    while (node && node != root && getColor(node) == BLACK) {
        if (node == node->parent->left) { // Если нода - левый ребенок своего родителя
            Node* sibling = node->parent->right;
            // 1) Если брат черный
            if (getColor(sibling) == RED) { // 2) Если брат красный - делаем левый поворот относительно родителя и перекрашиваем (родителя - в красный, брата - в черный) - пришли к случаю 1
                setColor(sibling, BLACK);
                setColor(node->parent, RED);
                rotateLeft(root, node->parent);
                sibling = node->parent->right; // Приходим к случаю, когда брат - черный (1)
            }
            if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) { // 1.1) Если у брата все дети черные - перекрашиваем брата в красный и поднимаемся от родителя
                setColor(sibling, RED);
                node = node->parent;
            }
            else { // 1.2) Если хотя бы один ребенок брата - красный
                // 1.2.1) Если правый ребенок - красный, а левый - любой - красим брата в родительский цвет, родителя - в черный, красного ребенка брата - в черный и делаем левый поворот относительно родителя
                if (getColor(sibling->right) == BLACK) { // 1.2.2) Если левый ребенок - красный - свапаем цвета брата и его левого ребенка и делаем правый поворот относительно брата и приходим к случаю 1.2.1
                    setColor(sibling->left, BLACK);
                    setColor(sibling, RED);
                    rotateRight(root, sibling);
                    sibling = node->parent->right; // Приходим к случаю, когда правый ребенок - красный, а левый - любой (1.2.1)
                }
                setColor(sibling, getColor(node->parent));
                setColor(node->parent, BLACK);
                setColor(sibling->right, BLACK);
                rotateLeft(root, node->parent);
                node = root;
            }
        }
        else { // Если нода - правый ребенок своего родителя - симметрично
            Node* sibling = node->parent->left;
            if (getColor(sibling) == RED) {
                setColor(sibling, BLACK);
                setColor(node->parent, RED);
                rotateRight(root, node->parent);
                sibling = node->parent->left;
            }
            if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                setColor(sibling, RED);
                node = node->parent;
            }
            else {
                if (getColor(sibling->left) == BLACK) {
                    setColor(sibling->right, BLACK);
                    setColor(sibling, RED);
                    rotateLeft(root, sibling);
                    sibling = node->parent->left;
                }
                setColor(sibling, getColor(node->parent));
                setColor(node->parent, BLACK);
                setColor(sibling->left, BLACK);
                rotateRight(root, node->parent);
                node = root;
            }
        }
    }
    setColor(node, BLACK);
}



Node* RB::erase(Node* root, int key) {
    Node* nodeToDelete = search(root, key);
    if (nodeToDelete == nullptr) {
        return root;
    }

    Node* y = nodeToDelete;
    Node* x;
    if (nodeToDelete->left == nullptr || nodeToDelete->right == nullptr) { // Если у удаляемой ноды до одного ребенка
        y = nodeToDelete;
    }
    else { // Если 2 ребенка
        y = minimum(nodeToDelete->right);
    }

    // Переподвешиваем потомка удаляемой ноды
    if (y->left != nullptr) {
        x = y->left;
    }
    else {
        x = y->right;
    }

    // Переподвешиваем родителя удаляемой ноды
    if (x != nullptr) {
        x->parent = y->parent;
    }

    if (y->parent == nullptr) {
        root = x;
    }

    // Меняем указатели на потомока у родителя удаляемой ноды
    else if (y == y->parent->left) {
        y->parent->left = x;
    }
    else {
        y->parent->right = x;
    }

    // В случае если нода имела двух потомков, меняем ключ удаляемый ноды на минимальный ключ из правого поддерева и удаляем этот ключ из правого поддерева
    if (y != nodeToDelete) {
        nodeToDelete->key = y->key;
    }

    if (y->color == BLACK) { // Если удаляемая нода имеет черный цвет
        fixErase(root, x);
    }
    delete y;
    fixAllHeights(root);
    return root;
}
