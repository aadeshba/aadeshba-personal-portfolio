//ProgramState.cpp
#include "ProgramState.h"
#include <string>
#include <iterator>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include <ctype.h>
#include <climits>
using namespace std;

ProgramState::ProgramState(int numLines) 
    : m_numLines(numLines), programCounter(1)
{}


void ProgramState::addToMap(string variableName, int value) { 
    map<string, int>::iterator it; //iterates through map to find variable and update its value if it already exists
    it = stateValues.find(variableName);
    if (it != stateValues.end()) {
        stateValues.find(variableName)->second = value;
        return;
    } 
    else {
        stateValues.insert(pair<string, int>(variableName, value));//otherwise, creates new pair in the map
        return;
    }
    
}

int ProgramState::getFromMap(string variableName) { 
    int val = 0;
    
    map<string, int>::iterator it; //iterates through map to find value from given variable
    it = stateValues.find(variableName);
    if (it != stateValues.end()) {
        val = it->second;
        return val;
    } 
    else { //if not, return this obscure value 
        return INT_MIN;
    }
}

void ProgramState::pushToStack(int lineNum) { //pushes linenum to stack
    lineNumsOfCaller.push(lineNum);
    return; 
}

int ProgramState::popFromStack() { //pops most recent gosub call from stack
    int value;
    value = lineNumsOfCaller.top();
    lineNumsOfCaller.pop();
    return value;
}


void ProgramState::printAllVariables(ostream& outf) { 
    map<string, int>::iterator it;
    for (it = stateValues.begin(); it != stateValues.end(); ++it) {
        outf << it->first << " " << it->second << endl;
    }
    return;
}

int ProgramState::parseStringToInt(string input) { 
    int num = 0;
    if (isdigit(input[0])) { //if string is already a digit, stoi it to a digit and return
        num = stoi(input);
        return num;
    } 
    if ((!isdigit(input[0]))) {//otherwise, iterate through map and find its corresponding digit val and return
        map<string, int>::iterator it;
        it = stateValues.find(input);    
        if (it != stateValues.end()) {
            num = it->second;
            return num;
        } 
    }
    return 0;
}

int ProgramState::performOperation(string operationType, string var, int val) {
    int total = 0;
    int val1 = 0;
    map<string, int>::iterator it;
        if (operationType == "ADD") {
            it = stateValues.find(var); //finds variable of interest, var, and returns its value onto val1 
            if (it != stateValues.end()) {
                val1 = it->second;
            }

            total = val1 + val; //performs desired operations with val1 and val
        }
        if (operationType == "SUB") {
            it = stateValues.find(var);
            if (it != stateValues.end()) {
                val1 = it->second;
            }
            total = val1 - val;
        }
        if (operationType == "MULT") {
            it = stateValues.find(var);
            if (it != stateValues.end()) {
                val1 = it->second;
            }

            total = val1 * val;
        }
        if (operationType == "DIV") {
            it = stateValues.find(var);
            if (it != stateValues.end()) {
                val1 = it->second;
            }
            total = val1 / val;
        }
return total;
}


int ProgramState::getM_numLines() { 
    return m_numLines; 
}

void ProgramState::setProgramCounter(int num) {
    programCounter = num;
    return;
}

int ProgramState::getProgramCounter() { 
    return programCounter;
}




