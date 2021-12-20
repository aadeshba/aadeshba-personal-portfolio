#ifndef RBBST_H
#define RBBST_H

#include "bst.h"
#include <algorithm>
#include <cstdlib>
#include <exception>
#include <iostream>

struct KeyError {};

/**
 * A special kind of node for an AVL tree, which adds the height as a data member, plus
 * other additional helper functions. You do NOT need to implement any functionality or
 * add additional data members or helper functions.
 */
template<typename Key, typename Value>
class AVLNode : public Node<Key, Value> {
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int getHeight() const;
    void setHeight(int height);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int height_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
 * An explicit constructor to initialize the elements by calling the base class constructor and setting
 * the color to red since every new node will be red when it is first inserted.
 */
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent)
        : Node<Key, Value>(key, value, parent), height_(1) {}

/**
 * A destructor which does nothing.
 */
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode() {}

/**
 * A getter for the height of a AVLNode.
 */
template<class Key, class Value>
int AVLNode<Key, Value>::getHeight() const {
    return height_;
}

/**
 * A setter for the height of a AVLNode.
 */
template<class Key, class Value>
void AVLNode<Key, Value>::setHeight(int height) {
    height_ = height;
}

/**
 * An overridden function for getting the parent since a static_cast is necessary to make sure
 * that our node is a AVLNode.
 */
template<class Key, class Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getParent() const {
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
 * Overridden for the same reasons as above.
 */
template<class Key, class Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getLeft() const {
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
 * Overridden for the same reasons as above.
 */
template<class Key, class Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getRight() const {
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}

/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/

template<class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value> {
public:
    virtual void insert(const std::pair<const Key, Value>& new_item);  // TODO
    virtual void remove(const Key& key);                               // TODO
protected:
    virtual void nodeSwap(AVLNode<Key, Value>* n1, AVLNode<Key, Value>* n2);

    // Add helper functions here
    void updateHeights(AVLNode<Key, Value>* curr);
    void left(AVLNode<Key, Value>* y, AVLNode<Key, Value>* z);
    void right(AVLNode<Key, Value>* y, AVLNode<Key, Value>* z);
    void leftRight(AVLNode<Key, Value>* x, AVLNode<Key, Value>* y, AVLNode<Key, Value>* z);
    void rightLeft(AVLNode<Key, Value>* x, AVLNode<Key, Value>* y, AVLNode<Key, Value>* z);
    int helpbalance(AVLNode<Key, Value>* curr);
    virtual AVLNode<Key, Value>* createNewNode(Key k, Value v, Node<Key, Value>* par);
    int maxChildHeight(AVLNode<Key, Value>* curr);
    int greaterChild(AVLNode<Key, Value>* curr);
};

template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value>& new_item) {
    // TODO
    AVLNode<Key, Value>* z = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::insertHelper(new_item));

    if (z == nullptr) {
        return;
    }
    if (this->isBalanced()) {
        while (z->getParent() != nullptr) {
            z = z->getParent();
            z->setHeight(maxChildHeight(z) + 1);
        }
        return;
    }
    while (z != nullptr) {
        z->setHeight(maxChildHeight(z) + 1);
        int balanceFactor = helpbalance(z);
        if (balanceFactor > 1) {
            if (z->getRight() != nullptr) {
                AVLNode<Key, Value>* y = z->getRight();
                int heightDif = greaterChild(y);
                if (heightDif == 1 || heightDif == -1) {
                    left(y, z);
                    return;
                } else if (heightDif == 0) {
                    if (y->getLeft() != nullptr) {
                        AVLNode<Key, Value>* x = y->getLeft();
                        rightLeft(x, y, z);
                        return;
                    }
                }
            }
        }
        if (balanceFactor < -1) {
            if (z->getLeft() != nullptr) {
                AVLNode<Key, Value>* y = z->getLeft();
                int heightDif = greaterChild(y);
                if (heightDif == 1) {
                    if (y->getRight() != nullptr) {
                        AVLNode<Key, Value>* x = y->getRight();
                        leftRight(x, y, z);
                        return;
                    }
                } else if (heightDif == 0 || heightDif == -1) {
                    right(y, z);
                    return;
                }
            }
        }
        z = z->getParent();
    }
    return;
}

template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key) {
    // TODO
    AVLNode<Key, Value>* z = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::removeHelper(key));
    if (z == nullptr) {
        return;
    }
    if (this->isBalanced()) {
        while (z->getParent() != nullptr) {
            z = z->getParent();
            z->setHeight(maxChildHeight(z) + 1);
        }
        return;
    }
    while (z != nullptr) {
        z->setHeight(maxChildHeight(z) + 1);
        int balanceFactor = helpbalance(z);
        if (balanceFactor > 1) {
            if (z->getRight() != nullptr) {
                AVLNode<Key, Value>* y = z->getRight();
                int heightDif = greaterChild(y);
                if (heightDif == 1 || heightDif == -1) {
                    left(y, z);
                } else if (heightDif == 0) {
                    if (y->getLeft() != nullptr) {
                        AVLNode<Key, Value>* x = y->getLeft();
                        rightLeft(x, y, z);
                    }
                }
            }
        }
        if (balanceFactor < -1) {
            if (z->getLeft() != nullptr) {
                AVLNode<Key, Value>* y = z->getLeft();
                int heightDif = greaterChild(y);
                if (heightDif == 1) {
                    if (y->getRight() != nullptr) {
                        AVLNode<Key, Value>* x = y->getRight();
                        leftRight(x, y, z);
                    }
                } else if (heightDif == 0 || heightDif == -1) {
                    right(y, z);
                }
            }
        }
        z = z->getParent();
    }
    return;
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap(AVLNode<Key, Value>* n1, AVLNode<Key, Value>* n2) {
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int tempH = n1->getHeight();
    n1->setHeight(n2->getHeight());
    n2->setHeight(tempH);
}

template<class Key, class Value>
int AVLTree<Key, Value>::helpbalance(AVLNode<Key, Value>* curr) {
    int lh, rh;
    if (curr->getRight() == nullptr && curr->getLeft() == nullptr) {
        return 0;
    }
    if (curr->getRight() != nullptr && curr->getLeft() == nullptr) {
        rh = curr->getRight()->getHeight();
        return rh;
    }
    if (curr->getLeft() != nullptr && curr->getRight() == nullptr) {
        lh = curr->getLeft()->getHeight();
        return (-lh);
    }
    if (curr->getLeft() != nullptr && curr->getRight() != nullptr) {
        rh = curr->getRight()->getHeight();
        lh = curr->getLeft()->getHeight();
        return (rh - lh);
    }
    return 0;
}

template<class Key, class Value>
int AVLTree<Key, Value>::maxChildHeight(AVLNode<Key, Value>* curr) {
    int lh, rh;
    if (curr->getLeft() == nullptr && curr->getRight() == nullptr) {
        return 0;
    }
    if (curr->getLeft() != nullptr && curr->getRight() == nullptr) {
        lh = curr->getLeft()->getHeight();
        rh = 0;
    }
    if (curr->getRight() != nullptr && curr->getLeft() == nullptr) {
        rh = curr->getRight()->getHeight();
        lh = 0;
    }
    if (curr->getRight() != nullptr && curr->getLeft() != nullptr) {
        rh = curr->getRight()->getHeight();
        lh = curr->getLeft()->getHeight();
    }
    if (lh > rh) {
        return lh;
    } else {
        return rh;
    }
    return 0;
}

template<class Key, class Value>
int AVLTree<Key, Value>::greaterChild(AVLNode<Key, Value>* curr) {
    int lh, rh;
    if (curr->getLeft() == nullptr && curr->getRight() == nullptr) {
        return 0;
    }
    if (curr->getLeft() != nullptr && curr->getRight() == nullptr) {
        lh = curr->getLeft()->getHeight();
        rh = 0;
    }
    if (curr->getRight() != nullptr && curr->getLeft() == nullptr) {
        rh = curr->getRight()->getHeight();
        lh = 0;
    }
    if (curr->getRight() != nullptr && curr->getLeft() != nullptr) {
        rh = curr->getRight()->getHeight();
        lh = curr->getLeft()->getHeight();
    }
    if (lh > rh) {
        return 0;
    } else if (rh > lh) {
        return 1;
    } else if (rh == lh) {
        return -1;
    }
    return 0;
}

template<class Key, class Value>
void AVLTree<Key, Value>::left(AVLNode<Key, Value>* y, AVLNode<Key, Value>* z) {
    if (this->root_ == z) {
        this->root_ = y;
    }
    z->setRight(y->getLeft());
    if (y->getLeft() != nullptr) {
        y->getLeft()->setParent(z);
    }
    if (y != this->root_) {
        if (z->getParent()->getLeft() == z) {
            z->getParent()->setLeft(y);
        } else if (z->getParent()->getRight() == z) {
            z->getParent()->setRight(y);
        }
    }
    y->setLeft(z);
    y->setParent(z->getParent());
    z->setParent(y);
    y->setHeight(maxChildHeight(y) + 1);
    z->setHeight(maxChildHeight(z) + 1);
    return;
}

template<class Key, class Value>
void AVLTree<Key, Value>::right(AVLNode<Key, Value>* y, AVLNode<Key, Value>* z) {
    if (this->root_ == z) {
        this->root_ = y;
    }
    z->setLeft(y->getRight());
    if (y->getRight() != nullptr) {
        y->getRight()->setParent(z);
    }
    if (y != this->root_) {
        if (z->getParent()->getRight() == z) {
            z->getParent()->setRight(y);
        } else if (z->getParent()->getLeft() == z) {
            z->getParent()->setLeft(y);
        }
    }
    y->setRight(z);
    y->setParent(z->getParent());
    z->setParent(y);
    y->setHeight(maxChildHeight(y) + 1);
    z->setHeight(maxChildHeight(z) + 1);
    return;
}

template<class Key, class Value>
void AVLTree<Key, Value>::leftRight(AVLNode<Key, Value>* x, AVLNode<Key, Value>* y, AVLNode<Key, Value>* z) {
    left(x, y);
    right(x, z);
    return;
}

template<class Key, class Value>
void AVLTree<Key, Value>::rightLeft(AVLNode<Key, Value>* x, AVLNode<Key, Value>* y, AVLNode<Key, Value>* z) {
    right(x, y);
    left(x, z);
    return;
}

template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::createNewNode(Key k, Value v, Node<Key, Value>* par) {
    AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(k, v, static_cast<AVLNode<Key, Value>*>(par));
    return newNode;
}

#endif