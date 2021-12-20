#ifndef BST_H
#define BST_H

#include <cstdlib>
#include <exception>
#include <iostream>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template<typename Key, typename Value>
class Node {
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value& value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
 * Explicit constructor for a node.
 */
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent)
        : item_(key, value), parent_(parent), left_(NULL), right_(NULL) {}

/**
 * Destructor, which does not need to do anything since the pointers inside of a node
 * are only used as references to existing nodes. The nodes pointed to by parent/left/right
 * are freed within the deleteAll() helper method in the BinarySearchTree.
 */
template<typename Key, typename Value>
Node<Key, Value>::~Node() {}

/**
 * A const getter for the item.
 */
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const {
    return item_;
}

/**
 * A non-const getter for the item.
 */
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem() {
    return item_;
}

/**
 * A const getter for the key.
 */
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const {
    return item_.first;
}

/**
 * A const getter for the value.
 */
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const {
    return item_.second;
}

/**
 * A non-const getter for the value.
 */
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue() {
    return item_.second;
}

/**
 * An implementation of the virtual function for retreiving the parent.
 */
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const {
    return parent_;
}

/**
 * An implementation of the virtual function for retreiving the left child.
 */
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const {
    return left_;
}

/**
 * An implementation of the virtual function for retreiving the right child.
 */
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const {
    return right_;
}

/**
 * A setter for setting the parent of a node.
 */
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent) {
    parent_ = parent;
}

/**
 * A setter for setting the left child of a node.
 */
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left) {
    left_ = left;
}

/**
 * A setter for setting the right child of a node.
 */
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right) {
    right_ = right;
}

/**
 * A setter for the value of a node.
 */
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value) {
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
 * A templated unbalanced binary search tree.
 */
template<typename Key, typename Value>
class BinarySearchTree {
public:
    BinarySearchTree();                                                    // TODO
    virtual ~BinarySearchTree();                                           // TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair);  // TODO
    virtual void remove(const Key& key);                                   // TODO
    void clear();                                                          // TODO
    bool isBalanced() const;                                               // TODO
    void print() const;
    bool empty() const;

public:
    /**
     * An internal iterator class for traversing the contents of the BST.
     */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key, Value>& operator*() const;
        std::pair<const Key, Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key, Value>* ptr);
        Node<Key, Value>* current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const;               // TODO
    Node<Key, Value>* getSmallestNode() const;                        // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current);  // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot(Node<Key, Value>* r) const;
    virtual void nodeSwap(Node<Key, Value>* n1, Node<Key, Value>* n2);

    // Add helper functions here

    bool helpbalance(Node<Key, Value>* r) const;
    int height(Node<Key, Value>* r) const;
    Node<Key, Value>* insertHelper(const std::pair<const Key, Value>& keyValuePair);
    Node<Key, Value>* removeHelper(const Key& key);
    virtual Node<Key, Value>* createNewNode(Key k, Value v, Node<Key, Value>* par);
    virtual void clearHelper(Node<Key, Value>* curr);

protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
 * Explicit constructor that initializes an iterator with a given node pointer.
 */
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key, Value>* ptr) {
    // TODO
    current_ = ptr;
}

/**
 * A default constructor that initializes the iterator to NULL.
 */
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() : current_(nullptr) {
    // TODO
}

/**
 * Provides access to the item.
 */
template<class Key, class Value>
std::pair<const Key, Value>& BinarySearchTree<Key, Value>::iterator::operator*() const {
    return current_->getItem();
}

/**
 * Provides access to the address of the item.
 */
template<class Key, class Value>
std::pair<const Key, Value>* BinarySearchTree<Key, Value>::iterator::operator->() const {
    return &(current_->getItem());
}

/**
 * Checks if 'this' iterator's internals have the same value
 * as 'rhs'
 */
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::iterator::operator==(const BinarySearchTree<Key, Value>::iterator& rhs) const {
    // TODO
    if (this->current_ == rhs.current_) {
        return true;
    }
    return false;
}

/**
 * Checks if 'this' iterator's internals have a different value
 * as 'rhs'
 */
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::iterator::operator!=(const BinarySearchTree<Key, Value>::iterator& rhs) const {
    // TODO
    if (this->current_ != rhs.current_) {
        return true;
    }
    return false;
}

/**
 * Advances the iterator's location using an in-order sequencing
 */
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator& BinarySearchTree<Key, Value>::iterator::operator++() {
    // TODO
    // check if we are at the end() of the tree
    if (current_ == nullptr) {
        std::cout << "Error: already at end of the tree" << std::endl;
        return *this;
    } else if (current_->getRight() != nullptr) {  // finds smallest node (leftmost) on right subtree
        current_ = current_->getRight();
        while (current_->getLeft() != nullptr) {
            current_ = current_->getLeft();
        }
        return *this;
    } else {  // no right node and finished with right subtree-> traverse upwards until a left edge or root
        Node<Key, Value>* ptr;
        ptr = current_->getParent();
        while (ptr != nullptr && current_ == ptr->getRight()) {
            current_ = ptr;
            ptr = ptr->getParent();
        }
        current_ = ptr;
        return *this;
    }
}

/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
 * Default constructor for a BinarySearchTree, which sets the root to NULL.
 */
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() : root_(nullptr) {
    // TODO                                         WHAT ELSE HERE
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree() {
    // TODO
    clear();
}

/**
 * Returns true if tree is empty
 */
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const {
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const {
    printRoot(root_);
    std::cout << "\n";
}

/**
 * Returns an iterator to the "smallest" item in the tree
 */
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::begin() const {
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
 * Returns an iterator whose value means INVALID
 */
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::end() const {
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
 * Returns an iterator to the item with the given key, k
 * or the end iterator if k does not exist in the tree
 */
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::find(const Key& k) const {
    Node<Key, Value>* curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * An insert method to insert into a Binary Search Tree.
 * The tree will not remain balanced when inserting.
 */
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value>& keyValuePair) {
    // TODO
    Node<Key, Value>* temp = insertHelper(keyValuePair);
    return;
}

template<class Key, class Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::insertHelper(const std::pair<const Key, Value>& keyValuePair) {
    if (root_ == nullptr) {
        Node<Key, Value>* temp = createNewNode(keyValuePair.first, keyValuePair.second, nullptr);
        root_ = temp;
        temp->setLeft(nullptr);
        temp->setRight(nullptr);
        return temp;
    }
    Node<Key, Value>* curr = root_;
    while (1) {
        if (keyValuePair.first == curr->getKey()) {
            curr->setValue(keyValuePair.second);
            return curr;
        } else if (keyValuePair.first > curr->getKey()) {
            if (curr->getRight() == nullptr) {
                Node<Key, Value>* temp = createNewNode(keyValuePair.first, keyValuePair.second, curr);
                curr->setRight(temp);
                temp->setParent(curr);
                return temp;
            } else {
                curr = curr->getRight();
            }
        } else if (keyValuePair.first < curr->getKey()) {
            if (curr->getLeft() == nullptr) {
                Node<Key, Value>* temp = createNewNode(keyValuePair.first, keyValuePair.second, curr);
                curr->setLeft(temp);
                temp->setParent(curr);
                return temp;
            } else {
                curr = curr->getLeft();
            }
        }
    }
}

/**
 * A remove method to remove a specific key from a Binary Search Tree.
 * The tree may not remain balanced after removal.
 */
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key) {
    // TODO
    Node<Key, Value>* temp = removeHelper(key);
    return;
}

template<class Key, class Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::removeHelper(const Key& key) {
    Node<Key, Value>* curr = this->internalFind(key);
    Node<Key, Value>* temp = nullptr;
    Node<Key, Value>* parent = nullptr;
    if (curr == nullptr) {
        return nullptr;
    }
    if (curr->getLeft() == nullptr && curr->getRight() == nullptr) {
        if (curr == root_) {
            root_ = nullptr;
            delete curr;
        } else {
            if (curr->getParent()->getLeft() == curr) {
                curr->getParent()->setLeft(nullptr);
            } else if (curr->getParent()->getRight() == curr) {
                curr->getParent()->setRight(nullptr);
            }
            parent = curr->getParent();
            delete curr;
        }
    } else if (curr->getRight() == nullptr && curr->getLeft() != nullptr) {
        temp = curr->getLeft();
        if (curr == root_) {
            root_ = temp;
            temp->setParent(nullptr);
            parent = nullptr;
            delete curr;
        } else if (curr->getParent()->getLeft() == curr) {
            curr->getParent()->setLeft(temp);
            temp->setParent(curr->getParent());
            parent = curr->getParent();
            delete curr;
        } else if (curr->getParent()->getRight() == curr) {
            curr->getParent()->setRight(temp);
            temp->setParent(curr->getParent());
            parent = curr->getParent();
            delete curr;
        }
    } else if (curr->getLeft() == nullptr && curr->getRight() != nullptr) {
        temp = curr->getRight();
        if (curr == root_) {
            root_ = temp;
            temp->setParent(nullptr);
            parent = nullptr;
            delete curr;
        } else if (curr->getParent()->getLeft() == curr) {
            curr->getParent()->setLeft(temp);
            temp->setParent(curr->getParent());
            parent = curr->getParent();
            delete curr;
        } else if (curr->getParent()->getRight() == curr) {
            curr->getParent()->setRight(temp);
            temp->setParent(curr->getParent());
            parent = curr->getParent();
            delete curr;
        }
    } else if (curr->getLeft() != nullptr && curr->getRight() != nullptr) {
        temp = predecessor(curr);
        bool change = false;
        if (curr == root_) {
            change = true;
        }
        nodeSwap(curr, temp);
        if (change) {
            root_ = temp;
        }
        if (curr->getParent()->getLeft() == curr) {
            curr->getParent()->setLeft(curr->getLeft());
            if (curr->getLeft() != nullptr) {
                curr->getLeft()->setParent(curr->getParent());
            }
            parent = curr->getParent();
            delete curr;
        } else if (curr->getParent()->getRight() == curr) {
            curr->getParent()->setRight(nullptr);
            if (curr->getRight() != nullptr) {
                curr->getRight()->setParent(curr->getParent());
            }
            parent = curr->getParent();
            delete curr;
        }
    }

    return parent;
}

template<class Key, class Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::createNewNode(Key k, Value v, Node<Key, Value>* par) {
    Node<Key, Value>* newNode = new Node<Key, Value>(k, v, par);
    return newNode;
}

template<class Key, class Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current) {
    // TODO
    Node<Key, Value>* ptr = current;
    Node<Key, Value>* parentptr;
    if (ptr->getLeft() != nullptr) {  // first checks if left subtree exists
        ptr = ptr->getLeft();
        while (ptr->getRight() != nullptr) {  // if so, iterate all the way down the right to find pre (or just stick w
                                              // first left child)
            ptr = ptr->getRight();
        }
    } else {
        parentptr = ptr->getParent();                                  // check parent pointers
        while (ptr == parentptr->getLeft() && parentptr != nullptr) {  // checks if ptr is in the left subtree of
                                                                       // parentptr and keeps iterating until untrue
            ptr = parentptr;
            parentptr = ptr->getParent();
        }
        ptr = parentptr;
    }
    if (ptr != nullptr) {
        return ptr;
    } else {
        return nullptr;
    }
}

/**
 * A method to remove all contents of the tree and
 * reset the values in the tree for use again.
 */
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear() {
    Node<Key, Value>* ptr = root_;
    clearHelper(ptr);
    return;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearHelper(Node<Key, Value>* curr) {
    if (curr == nullptr) {
        return;
    } else {
        clearHelper(curr->getLeft());
        clearHelper(curr->getRight());
        delete curr;
    }
    root_ = nullptr;
    return;
}

/**
 * A helper function to find the smallest node in the tree.
 */
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::getSmallestNode() const {
    // TODO
    if (root_ == nullptr) {
        return nullptr;
    }
    Node<Key, Value>* ptr = root_;
    while (ptr->getLeft() != nullptr) {
        ptr = ptr->getLeft();
    }
    return ptr;
}

/**
 * Helper function to find a node with given key, k and
 * return a pointer to it or NULL if no item with that key
 * exists
 */
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const {
    // TODO
    Node<Key, Value>* ptr;
    ptr = root_;
    while (ptr != nullptr) {
        if (ptr->getKey() == key) {
            return ptr;
        }
        if (ptr->getKey() > key) {
            ptr = ptr->getLeft();
        }
        if (ptr->getKey() < key) {
            ptr = ptr->getRight();
        }
    }
    return nullptr;
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const {
    // TODO
    bool bruh = helpbalance(root_);
    return bruh;
}

/**
 * Returns int value of heights in tree for help
 * in isBalanced function.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::helpbalance(Node<Key, Value>* r) const {
    int left, right;
    if (r == nullptr) {
        return true;
    }
    left = height(r->getLeft());
    right = height(r->getRight());
    if (std::abs(right - left) < 2 && helpbalance(r->getLeft()) && helpbalance(r->getRight())) {
        return true;
    } else {
        return false;
    }
}
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::height(Node<Key, Value>* r) const {
    if (r == nullptr) {
        return 0;
    }
    return (1 + std::max(height(r->getLeft()), height(r->getRight())));
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap(Node<Key, Value>* n1, Node<Key, Value>* n2) {
    if ((n1 == n2) || (n1 == NULL) || (n2 == NULL)) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if (n1p != NULL && (n1 == n1p->getLeft()))
        n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if (n2p != NULL && (n2 == n2p->getLeft()))
        n2isLeft = true;

    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if ((n1r != NULL && n1r == n2)) {
        n2->setRight(n1);
        n1->setParent(n2);
    } else if (n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    } else if (n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    } else if (n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);
    }

    if (n1p != NULL && n1p != n2) {
        if (n1isLeft)
            n1p->setLeft(n2);
        else
            n1p->setRight(n2);
    }
    if (n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if (n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if (n2p != NULL && n2p != n1) {
        if (n2isLeft)
            n2p->setLeft(n1);
        else
            n2p->setRight(n1);
    }
    if (n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if (n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }

    if (this->root_ == n1) {
        this->root_ = n2;
    } else if (this->root_ == n2) {
        this->root_ = n1;
    }
}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer
   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif