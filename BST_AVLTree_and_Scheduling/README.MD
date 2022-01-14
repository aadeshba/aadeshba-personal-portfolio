# Aadesh Bajaj - BST and AVLTree with Scheduler Implementation
This assignment was completed for my Data Structures Class. It was written in C++ and required me to implement classes for a Binary Search Tree, an AVL Tree, and a course Scheduler for students. The AVL Tree inherits from the Binary Search Tree. Implementing these data structures from scratch was very intensive and not something usually required in a professional environment. However, it did help me to gain a better understanding of the data structures and practice my Object-Oriented Programming in C++.
## Binary Search Tree
* The implementation for the Binary Search Tree (BST) can be found in the 'bst' directory.
* This implementation just needs to be included in another file and then the BST class can be easily used in one's own program.
* The main functions provided in the interface of the BST for a user to use it in their own program are insert(), clear(), and print(). Everything else is used internally to help manage the data of the BST and becomes very important in the AVL and Splay trees.
## AVL tree
* This implementation can be found in the 'avl' directory.
* This class inherits from the BST class written above and overrides the necessary functions. It also uses a special AVLNode that stores height information to help when balancing the AVL tree. A number of functions such as fixHeights are used to maintain this balance.
* The main methods that were overridden are insert() and remove(). These are done in very specific ways in AVL Trees. Both of these functions utilize a number of internal functions that were written to make operations such as rotations in the tree easier to organize within those insert and remove functions.
## Scheduling
* This class utilizes backtracking in C++. It utilizes an adjacency list graph that is recursively ran through as well as my own AVL Tree implementation to map courses to time slots.
* Given an input file with the right parameters, the program should run using make followed by the file name. It outputs an exam scnedule that fits all students' needs given their own exams and time slots available. If there are schedule conflicts, the program will print "No valid solution."
