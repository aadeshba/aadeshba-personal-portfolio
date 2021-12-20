// PrintAllStatement.cpp:
#include "PrintAllStatement.h"
#include <map>
#include <iterator>
using namespace std;

PrintAllStatement::PrintAllStatement() 
{}

void PrintAllStatement::execute(ProgramState* state, ostream& outf) {  
    state->printAllVariables( outf);                         //calls programstate.cpp printallvariables function that iterates through map
    state->setProgramCounter(state->getProgramCounter() + 1);//increments programCounter
    return;
}

PrintAllStatement::~PrintAllStatement() {}