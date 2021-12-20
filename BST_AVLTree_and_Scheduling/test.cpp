#include <iostream>
#include <string>
#include <vector>
#include "avlbst.h"
#include "bst.h"

using namespace std;

int main() { 
    AVLTree<int, int>* avl = new AVLTree<int, int>();
    pair<int, int> foo;

    foo = make_pair(20, 10);
    avl->insert(foo);

    foo = make_pair(10, 10);
    avl->insert(foo);

    foo = make_pair(30, 10); 
    avl->insert(foo);

    foo = make_pair(40, 10);
    avl->insert(foo);

    avl->print();

    avl->remove(20);

    avl->print();

   /* foo = make_pair(10, 4);
    avl->insert(foo);

    avl->print();

    foo = make_pair(9, 40);
    avl->insert(foo);

    
    avl->print();


    foo = make_pair(8, 100);
    avl->insert(foo);

    
    avl->print();


    foo = make_pair(7, 5);
    avl->insert(foo);

    
    avl->print();


    foo = make_pair(6, 445);
    avl->insert(foo);

    avl->print();


    foo = make_pair(1, 25);
    avl->insert(foo);

    foo = make_pair(45, 40);
    avl->insert(foo);
    
    avl->print();

    foo = make_pair(1610, 40);
    avl->insert(foo);

    foo = make_pair(100320, 40);
    avl->insert(foo);

    avl->print();


    foo = make_pair(16, 40);
    avl->insert(foo);

    avl->print();

    foo = make_pair(11, 40);
    avl->insert(foo);

    avl->print();

    foo = make_pair(12, 40);
    avl->insert(foo);

    avl->print();

    avl->remove(9);
    avl->print();*/
    /**
    b->remove(10);
    b->remove(20);
    bool is = b->isBalanced();
    cout << is << endl;
    b->remove(120);
    b->print();

    b->remove(50);

    is = b->isBalanced();
    cout << is << endl;
    b->print();
    b->remove(1);
    b->print();
    b->remove(16);
    b->print();

    return -1;
}