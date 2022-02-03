# Aadesh Bajaj - BST and AVLTree with Exam Scheduler Implementation
This assignment was completed for my Data Structures Class (CSCI 104). It was written in C++ and required me to implement classes for a Binary Search Tree, an AVL Tree, and a course Scheduler for students. The AVL Tree inherits from the Binary Search Tree. 
## Binary Search Tree
* Implements a Binary Search Tree, similar to one that might be inherited in the STL to implement things like HashMap or Set. 
* Implemented insert(), delete(), search(), and other functions with iterator.
* Found under 'bst' directory.
## AVL tree
* This class inherits from BST. It is used to fully implement a map ADT in one's own program (by using #include "avl.h")
* Overrides BST functions insert(), remove() and search() while adding many helper functions to perform rotations and traversal through the tree structure.
* Can be found in the 'avl' directory.
## Scheduling
* This class utilizes backtracking in C++. It utilizes an adjacency list graph that is recursively ran through as well as my own AVL Tree implementation to map courses to time slots.
* Given an input file with the right parameters, the program should run using make followed by the file name. It outputs an exam schedule that fits all students' needs given their own exams and time slots available. If there are schedule conflicts, the program will print "No valid solution."
