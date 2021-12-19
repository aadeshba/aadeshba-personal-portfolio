// ReturnStatement.cpp
#include "ReturnStatement.h"
using namespace std;

ReturnStatement::ReturnStatement() {}

void ReturnStatement::execute(ProgramState* state, ostream& outf) { 
    
    
    int temp = state->popFromStack() + 1; //pops GoSub line, then adds one to proceed to the next line in program
    state->setProgramCounter(temp);// sets this new line as the programCounter line

    return; 
}