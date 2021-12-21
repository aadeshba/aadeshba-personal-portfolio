// ProgramState.h
//
// CS 104 / Fall 2021
//
// The ProgramState class encapsulates the state of an executing Facile
// program.  The state of a BASIC program consists of three parts:
//
//    * The program counter, which specifies the line number of the
//      statement that will execute next.
//    * A map, as explained by the problem writeup.
//    * A stack of integers, which is used to hold return lines for GOSUB
//      statements.
//
// We've provided you a start on this class, but you'll need to add methods
// to it as you go along.  In particular, you'll need methods to access and
// modify the state; these methods will be called primarily by the various
// execute() methods in the Statement subclasses, to allow the execution of
// a statement to change the state of a program.  For example, executing a
// GOTO statement will cause the program counter to be changed.

#include <map>
#include <stack>
#include <string>
#include <iterator>

#ifndef PROGRAM_STATE_INCLUDED
#define PROGRAM_STATE_INCLUDED
using namespace std;

class ProgramState
{
public:
	ProgramState(int numLines); //constructor

    void addToMap(string variableName, int value);//sets given value for variable in map,
    //creating variable if it doesn't exist

    int getFromMap(string variableName); //returns value for given variable

    void pushToStack(int lineNum); //push to stack for goto or gosub statement

    int popFromStack(); //popstack for return statement

    void setProgramCounter(int num); //setter for programCounter member

    int getM_numLines();

    int getProgramCounter(); //getter for progamCounter member

    void printAllVariables(ostream& outf); //function called in printAllVariables to format and print all variables

    int parseStringToInt(string input); //called in 

    int performOperation(string operationType, string var, int val);


    

	// You'll need to add a variety of methods here.  Rather than trying to
	// think of what you'll need to add ahead of time, add them as you find
	// that you need them.


private:
    int m_numLines;
    map<string, int> stateValues;
    stack<int> lineNumsOfCaller;
    int programCounter;
};

#endif
