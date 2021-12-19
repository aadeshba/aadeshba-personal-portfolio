// Interpreter.cpp
#include "EndStatement.h"
#include "ArithmeticStatement.h"
#include "LetStatement.h"
#include "PrintAllStatement.h"
#include "PrintStatement.h"
#include "ReturnStatement.h"
#include "Statement.h"
#include "IfStatement.h"
#include "GoSubStatement.h"
#include "GoToStatement.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>
#include <vector>

using namespace std;

// parseProgram() takes a filename as a parameter, opens and reads the
// contents of the file, and returns an vector of pointers to Statement.
void parseProgram(istream& inf, vector<Statement*>& program);

// parseLine() takes a line from the input file and returns a Statement
// pointer of the appropriate type.  This will be a handy method to call
// within your parseProgram() method.
Statement* parseLine(string line);

// interpretProgram() reads a program from the given input stream
// and interprets it, writing any output to the given output stream.
// Note:  you are required to implement this function!
void interpretProgram(istream& inf, ostream& outf);

int main() {
    cout << "Enter BASIC program file name: ";
    string filename;
    getline(cin, filename);
    ifstream infile(filename.c_str());
    if (!infile) {
        cout << "Cannot open " << filename << "!" << endl;
        return 1;
    }
    interpretProgram(infile, cout);

}

void parseProgram(istream& inf, vector<Statement*>& program) {
    program.push_back(NULL);

    string line;
    while (!inf.eof()) {
        getline(inf, line);
        program.push_back(parseLine(line));
    }
}

Statement* parseLine(string line) {
    Statement* statement;
    stringstream ss;
    int lineNum;
    string type;
    string var;
    int val;

    ss << line;
    ss >> lineNum;
    ss >> type;

    if (type == "LET") {
        ss >> var;
        ss >> val;
        // Note:  Because the project spec states that we can assume the file
        //	  contains a syntactically legal program, we know that
        //	  any line that begins with "LET" will be followed by a space
        //	  and then a variable and then an integer value.
        statement = new LetStatement(var, val);
    }

    if (type == "END" || type == ".") {
        statement = new EndStatement();
    }

    if (type == "PRINT") {
        ss >> var;
        statement = new PrintStatement(var);
    }

    if (type == "PRINTALL") {
        statement = new PrintAllStatement();
    }

    if (type == "GOTO") {
        ss >> val;
        statement = new GoToStatement(val);
    }

    if (type == "GOSUB") {
        ss >> val;
        statement = new GoSubStatement(val);
    }

    if (type == "RETURN") {
        statement = new ReturnStatement;
    }


    if (type == "ADD" || type == "SUB" || type == "MULT" || type == "DIV") { //takes in type and also passes that through the arithmetic staement constructor-- more concise this way
        string secondVariable;
        ss >> var;
        ss >> secondVariable;
        statement = new ArithmeticStatement(type, var, secondVariable); 
    }

    if (type == "IF") { //takes in everything in line, excluding "THEN"
        string oper;
        int line;
        string then;
        ss >> var;
        ss >> oper;
        ss >> val;
        ss >> then;
        ss >> line;
        statement = new IfStatement(var, oper, val, line);
    }

    return statement;
}

void interpretProgram(istream& inf, ostream& outf) {
    vector<Statement*> program;
    parseProgram(inf, program);
    
    // Incomplete;  TODO:  Finish this function!

    // Instantiate the programstate here
    ProgramState* progState = new ProgramState(program.size()); 

    // main while loop to run each statement (until an end or . is reached)
    long unsigned int i = 1;
    while (i < (program.size())+1) { 
        program[progState->getProgramCounter()]->execute(progState, cout);
        i++;
    }


    for (int j = 0; j < program.size(); j++) {
        delete program[j];
    }
    delete progState;  // freein allocated memory (programstate, statements)
    
    return;
}
