// GoSubStatement.cpp
#include "GoSubStatement.h"
using namespace std;

GoSubStatement::GoSubStatement(int lineNum) //constructor
    : m_lineNum(lineNum) 
{}

void GoSubStatement::execute(ProgramState* state, std::ostream& outf) {
    state->pushToStack(state->getProgramCounter()); //pushes current line to stack
    if (m_lineNum > state->getM_numLines() || m_lineNum < 1) {  // for out of bounds jumps
        outf << "Illegal Jump Instruction";
        exit(EXIT_FAILURE);
    }
    state->setProgramCounter(m_lineNum); //jumps to new line
    return;
}
