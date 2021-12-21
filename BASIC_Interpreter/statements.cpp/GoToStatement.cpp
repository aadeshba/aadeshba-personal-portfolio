//GoToStatement.cpp
#include "GoToStatement.h"
#include <cstdlib>
using namespace std;

GoToStatement::GoToStatement(int lineNum)  //constructor
    : m_lineNum(lineNum)
{}

void GoToStatement::execute(ProgramState* state, std::ostream& outf) {

    if (m_lineNum > state->getM_numLines() || m_lineNum < 1) { //for out of bounds jumps
        outf << "Illegal Jump Instruction";
        exit(EXIT_FAILURE); //terminates program
    }
    state->setProgramCounter(m_lineNum);//simply sets to proper line number
    return;
}
