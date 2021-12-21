// PrintStatement.cpp:
#include "PrintStatement.h"
#include <iostream>
#include <climits>

PrintStatement::PrintStatement(std::string variableName)
	: m_variableName( variableName )
{}


void PrintStatement::execute(ProgramState * state, std::ostream &outf)
{  
    if (state->getFromMap(m_variableName) == INT_MIN) { //checks if variable exists -> if not, creates it with 0
        state->addToMap(m_variableName, 0);
    }
    
    outf << state->getFromMap(m_variableName) << endl;
    state->setProgramCounter(state->getProgramCounter() + 1);
    return;
}

PrintStatement::~PrintStatement() {

}
