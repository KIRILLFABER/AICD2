#include <queue>
#include <stack>
#include <iostream>

template <class T> void inOrder(T node)
{
	if (node == nullptr) return;
	inOrder(node->left);
	std::cout << node->key << " ";
	inOrder(node->right);
}

template <class T> void preOrder(T node) {
	if (node == nullptr) return;
	std::cout << node->key << " ";
	preOrder(node->left);
	preOrder(node->right);
}

template <class T> void postOrder(T node) {
	if (node == nullptr) return;
	postOrder(node->left);
	postOrder(node->right);
	std::cout << node->key << " ";
}
template <class T> void breadth(T root) {
    if (root == nullptr)
        return;

    std::queue<T> q;
    q.push(root);

    while (!q.empty()) {
        T current = q.front();
        q.pop();

        std::cout << current->key << " ";

        if (current->left)
            q.push(current->left);
        if (current->right)
            q.push(current->right);
    }
}


