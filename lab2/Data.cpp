#include "Data.h"
#include <random>

const int MAX_VAL = 100;
const int SIZE = 1e3;



void fillDataFile(std::string filename) {
    std::ofstream data_file;
    data_file.open(filename);
    // Проверка файла на открытие
    if (!data_file.is_open()) {
        std::cout << "ERROR\n";
        return;
    }

    data_file << "Tree;n;h(n)\n";


    srand(time(0));
    // BST
    BST::Node* BSTroot = new BST::Node(rand() % MAX_VAL);
    for (int i = 0; i < SIZE; i++) {
            
            BSTroot = BST::insert(BSTroot, rand() % MAX_VAL);
            data_file << "BST;" << BST::Node::cnt << ";" << BST::height(BSTroot) << "\n";

    }
    BST::Node::cnt = 0;

    // BST (Возрастающие ключи)
    BST::Node* BSTWroot = new BST::Node(-1);
    for (int i = 0; i < SIZE; i++) {

        BSTWroot = BST::insert(BSTWroot, i);
        data_file << "BSTW;" << BST::Node::cnt << ";" << BST::height(BSTWroot) << "\n";

    }
        
    // AVL
    AVL::Node* AVLroot = new AVL::Node(rand() % MAX_VAL);
    for (int i = 0; i < SIZE; i++) {
        AVLroot = AVL::insert(AVLroot, rand() % MAX_VAL);
        data_file << "AVL;" << AVL::Node::cnt << ";" << AVL::height(AVLroot) << "\n";

    }
    // RB
    
    RB::Node* RBroot = new RB::Node(rand() % MAX_VAL);
    for (int i = 0; i < SIZE; i++) {
        RBroot = RB::insert(RBroot, rand() % MAX_VAL);
        data_file << "RB;" << RB::Node::cnt << ";" << RB::height(RBroot) << "\n";

    }






    data_file.close();
}
