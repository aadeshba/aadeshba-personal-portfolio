#include "MinHeap.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <string>
#include <fstream>

using namespace std;


int main(int argc, char** argv) { 
    if (argc != 4) {//if not right amount of args passed through
        return -1;
    }
    
    string start = argv[1];//second arg with start word
    string end = argv[2];//third arg with end word

    for (long unsigned int i = 0; i < start.length(); i++) {
        start[i] = toupper(start[i]);//converts to uppercase only
        end[i] = toupper(end[i]);//converts to uppercase only
    }


    set<string> allWords;//set of all words in input file

    string currWord = "";//initializing this string that will read in words one by one
    
    //read in words from file
    string fileName = argv[3]; // third arg is file name
    ifstream iFile;
    iFile.open(fileName); 
    while (iFile >> currWord) {//takes in each word line by line in file
        if (currWord.length() == start.length()) {
            for (long unsigned int i = 0; i < currWord.length(); i++) {
                currWord[i] = toupper(currWord[i]);  // converts all letters of each word to upper case
            }
            allWords.insert(currWord);  // inserts the word into allWords Set
        }
    }

    map<string, vector<string>> m;//actual adjacency list (graph)
    map<string, int> hVal;//maps all strings to their heuristics
    map<string, int> gVal;//maps all strings to their distances
    
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";//string of all letters
    
    set<string>::iterator it = allWords.begin();

    while (it != allWords.end()) {
        vector<string> edges;//vector to be added to map
        m[*it] = edges;//vector added to map
        int diffLetters;//int for heuristic map
        for (long unsigned int i = 0; i < it->length(); i++) {  // each letter of the word 
            for (int j = 0; j < 26; j++) {//iterate through each letter of alphabet
                string temp = *it;//temp variable so we don't change the actual set of words
                temp[i] = alphabet[j];
                if (allWords.find(temp) != allWords.end()) {//if that variation of the word is in the set
                    if (temp != *it) {//if the temp is not just the initial word
                        m[*it].push_back(temp);//push to vector
                    }
                }
            }
            if ((*it)[i] == end[i]) { //if the corresponding letters are different, add one to diffLetters
                diffLetters++;//increments each different letter between current word and end word
            }
        }
        hVal[*it] = diffLetters;//associates this int (heuristic) with current wod
        ++it;
    }
    

    map<string, int> mapOfIDs;//ids to connect with minheap ids
    MinHeap<string> myHeap(2); //minheap
    

    set<string> visited;//set of visited words
    map<string, string> predecessors;//predecessors
   
    

    myHeap.add(start, 0);
    gVal[start] = 0;
    mapOfIDs[start] = 0;
    int id = 1;
    int expansions = 0;
    int steps = 0;
    


    while (!myHeap.isEmpty()) {
        string v = myHeap.peek();
        myHeap.remove();
        id--;
        if (v == end) {
            steps = gVal[v];
            break;
        }
        expansions++;

        string temp = v;
        
        for (long unsigned int i = 0; i < m[v].size(); i++) {
            string w = m[v][i];//for ease
            if (predecessors[w] != v && w != start) {//to check for backtracing
                if (visited.find(w) == visited.end() || gVal[v] + 1 < gVal[w]) {//if visited or if better path
                    gVal[w] = gVal[v] + 1;//increment distance by 1
                    predecessors[w] = v;
                    if (visited.find(w) == visited.end()) {
                        myHeap.add(w, ((hVal[w] + gVal[w]) * (m[v].size() + 1) + hVal[w]));
                        mapOfIDs[w] = id;
                        id++;
                        visited.insert(w);
                    } 
                    else {
                        myHeap.updatePriority(mapOfIDs[w], (hVal[w] + gVal[w]) * (m[v].size() + 1) + hVal[w]);
                    }
                }                
            }
        }
    }



    
    if (steps > 0) {//checks if transformation found
        cout << steps << endl;
    } 
    else {
        cout << "No transformation" << endl;
    }
    cout << expansions << endl;
    iFile.close();
}



