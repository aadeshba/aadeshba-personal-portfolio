#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <set>
#include "bst.h"
#include "avlbst.h"

using namespace std;

void search(
        vector<vector<string>> exams,
        vector<vector<bool>> isAdded,
        AVLTree<string, int>* currTimeSlots,
        int currStudent,
        int numStudents,
        int numTimeSlots,
        int currClass, 
        char* isDone);//isDone flag lets us know when program has found a solution to come back to the first call on the stack
void print_result(AVLTree<string, int>* timeSlots);

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "Please Enter an input file along with the executable." << endl;
        return -1;
    }
    int numExams = 0;
    int numStudents = 0;
    int numTimeSlots = 0;

    string filename = argv[1];
    ifstream iFile;
    iFile.open(filename);  // opens file from cmd line to be read in


    iFile >> numExams >> numStudents >> numTimeSlots;


    vector<vector<string>> exams;//set data structures
    AVLTree<string, int>* currTimeSlots = new AVLTree<string, int>();
    vector<vector<bool>> isAdded;//graph to see which classes have been properly added for all students

    string myString;
    string str;
    string name = "";
    getline(iFile, str);

    for (int i = 0; i < numStudents; i++) {//get info from fstream and feed into sstream (iterates through students)
        getline(iFile, str);//feed line into string from file
        stringstream ss(str);//set stringstream
        ss >> name;//get name
        vector<string> temp;//to feed into currTimeSlots
        vector<bool> temp1;//to feed into isAdded
        while (ss >> myString) {//populate graph and adjacency list from the for each student
            temp.push_back(myString);
            temp1.push_back(false);
        }
        exams.push_back(temp);
        isAdded.push_back(temp1);
    }

    int currClass = 0;//for exam indexing
    int currStudent = 0;//for student indexing
    char isDone = 0;
    search(exams, isAdded, currTimeSlots, currStudent, numStudents, numTimeSlots, currClass, &isDone);
    return 1;
}

void search(
        vector<vector<string>> exams,
        vector<vector<bool>> isAdded,
        AVLTree<string, int>* currTimeSlots,
        int currStudent,
        int numStudents,
        int numTimeSlots,
        int currClass, 
        char *isDone) {
    if (currStudent >= numStudents) {
        print_result(currTimeSlots);
        *isDone = 1;
        return;
    }  
    else {
        for (int i = 0; i < numTimeSlots; i++) {
            if (currTimeSlots->find(exams[currStudent][currClass]) != currTimeSlots->end()) {//if class is already assigned a time slot
                AVLTree<string, int>::iterator it = currTimeSlots->find(exams[currStudent][currClass]);
                int val = it->second;//what the current timeslot is for that exam
                if (isAdded[currStudent][val] == false) {//if the graph is empty at this spot for the student's exam, we can populate it bc they have empty timeslot there
                    isAdded[currStudent][val] = true;
                    if (exams[currStudent].size() - 1 > currClass) {//if we are still on one student
                        search(exams, isAdded, currTimeSlots, currStudent, numStudents, numTimeSlots, currClass + 1, isDone);
                        if (*isDone == 1)//if isDone is correct, return all the way
                            return;
                    } else if (exams[currStudent].size() - 1 <= currClass) {//once gone through all a student's classes, go to next student
                        search(exams, isAdded, currTimeSlots, currStudent + 1, numStudents, numTimeSlots, 0, isDone);
                        if (*isDone == 1)//if isDone is correct, return all the way
                            return;
                    }
                    isAdded[currStudent][val] = false;//if we get here, we backtracked so we must remove the item from the graph
                } 
                else {
                    return;
                }
            }
            else {//if class hasn't been assigned a time slot yet
                if (isAdded[currStudent][i] == false) {
                    currTimeSlots->insert(make_pair(exams[currStudent][currClass], i));//insert the class to the avl tree
                    isAdded[currStudent][i] = true;//make it as true in graph
                    if (exams[currStudent].size() - 1 > currClass) {//if we are still on one student
                        search(exams, isAdded, currTimeSlots, currStudent, numStudents, numTimeSlots, currClass + 1, isDone);
                        if (*isDone == 1)//if isDone is correct, return all the way
                            return;
                    } else if (exams[currStudent].size() - 1 <= currClass) {//once gone through all a student's classes, go to next student
                        search(exams, isAdded, currTimeSlots, currStudent + 1, numStudents, numTimeSlots, 0, isDone);
                        if (*isDone == 1)//if isDone is correct, return all the way
                            return;
                    }
                    currTimeSlots->remove(exams[currStudent][currClass]);//if we get here, we backtracked so we must remove the item from the avl tree
                    isAdded[currStudent][i] = false;//if we get here, we backtracked so we must remove the item from the graph
                } else {
                    return;
                }
            }
        }
    }

    if (currStudent == 0 && currClass == 0) {//if we backtrack all the way to the first call on stack without isDone set to 1, we can assume we didn't find a solution
        cout << "No Valid Solution" << endl;
    }
    return;
}

//each recursive call is the rows: the students
//think about the individual row itself (place the thing 

void print_result(AVLTree<string, int>* timeSlots) { 
    BinarySearchTree<string, int>::iterator it(timeSlots->begin());
    while (it != timeSlots->end()) {//iterate through tree and print timeslots
        cout << it->first << " " << it->second + 1 << endl;
        ++it;
    }
    return;
}
